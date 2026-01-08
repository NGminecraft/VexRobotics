// Mock vex.h - minimal stub of the VEX C++ API for tests
// Place this file in your include path when building tests.
// This is a lightweight, header-only mock: it implements minimal behavior
// and is intended only for compilation and simple runtime tests.
//
// Requires C++17 (for inline variables).

#pragma once

#include <cstdint>
#include <functional>
#include <iostream>
#include <mutex>
#include <string>
#include <thread>
#include <chrono>
#include <atomic>

namespace vex {

// Basic enums and units used in VEX API
enum class directionType { fwd = 1, rev = -1 };
enum class brakeType { coast, brake, hold };
enum class velocityUnits { pct, rpm };
enum class percentUnits { pct };
enum class rotationUnits { deg, rev };
enum class distanceUnits { mm, in };

// Simple time utilities (milliseconds)
using msec = std::chrono::milliseconds;

// Minimal motor mock
class motor {
public:
  motor(int port = 1, bool reversed = false)
    : m_port(port), m_reversed(reversed), m_rotation_deg(0.0),
      m_brake(brakeType::coast), m_spinning(false), m_velocity(0.0) {}

  // Basic control API
  void spin(directionType dir, double velocity, velocityUnits units = velocityUnits::pct) {
    std::lock_guard<std::mutex> lk(m_mutex);
    m_spinning = true;
    m_velocity = (dir == directionType::fwd ? 1.0 : -1.0) * velocity;
    // For mock: we won't start a background simulation thread. Rotation updates must be
    // driven explicitly by rotateFor / rotateTo / user test code if needed.
    std::cerr << "[mock motor] port " << m_port << " spin "
              << (dir == directionType::fwd ? "fwd" : "rev")
              << " vel=" << velocity << (units==velocityUnits::pct ? "%":"rpm") << "\n";
  }

  void stop(brakeType bt = brakeType::coast) {
    std::lock_guard<std::mutex> lk(m_mutex);
    m_spinning = false;
    m_velocity = 0.0;
    m_brake = bt;
    std::cerr << "[mock motor] port " << m_port << " stop (brake="
              << (bt==brakeType::coast ? "coast" : bt==brakeType::brake ? "brake":"hold") << ")\n";
  }

  // Rotate for a given angle or revolutions; if wait is true this will simulate time passing
  void spinFor(directionType dir, double value, rotationUnits units, velocityUnits vel_units = velocityUnits::pct, bool wait = true) {
    double deg = (units == rotationUnits::deg) ? value : value * 360.0;
    if (dir == directionType::rev) deg = -deg;
    {
      std::lock_guard<std::mutex> lk(m_mutex);
      // naive instantaneous: update position
      m_rotation_deg += deg;
    }
    std::cerr << "[mock motor] port " << m_port << " spinFor " << deg << "deg\n";
    if (wait) {
      // simulate a short delay proportional to amount moved (very coarse)
      auto delay = std::chrono::milliseconds(static_cast<int>(std::abs(deg) / 360.0 * 50));
      std::this_thread::sleep_for(delay);
    }
  }

  // rotateFor without explicit direction
  void rotateFor(double value, rotationUnits units, bool wait = true) {
    double deg = (units == rotationUnits::deg) ? value : value * 360.0;
    {
      std::lock_guard<std::mutex> lk(m_mutex);
      m_rotation_deg += deg;
    }
    std::cerr << "[mock motor] port " << m_port << " rotateFor " << deg << "deg\n";
    if (wait) {
      auto delay = std::chrono::milliseconds(static_cast<int>(std::abs(deg) / 360.0 * 50));
      std::this_thread::sleep_for(delay);
    }
  }

  // Reset encoder/rotation
  void resetRotation() {
    std::lock_guard<std::mutex> lk(m_mutex);
    m_rotation_deg = 0.0;
    std::cerr << "[mock motor] port " << m_port << " resetRotation\n";
  }

  // Read (mock) rotation
  double rotation(rotationUnits units = rotationUnits::deg) {
    std::lock_guard<std::mutex> lk(m_mutex);
    if (units == rotationUnits::deg) return m_rotation_deg;
    return m_rotation_deg / 360.0;
  }

  int port() const { return m_port; }

  void setBrake(brakeType bt) { m_brake = bt; }

private:
  int m_port;
  bool m_reversed;
  double m_rotation_deg;
  brakeType m_brake;
  bool m_spinning;
  double m_velocity;
  std::mutex m_mutex;
};

// Simple motor_group mock (wraps up to a few motors)
class motor_group {
public:
  motor_group() = default;
  motor_group(std::initializer_list<motor*> motors) {
    for (auto m : motors) m_motors.push_back(m);
  }

  void spin(directionType dir, double vel, velocityUnits units = velocityUnits::pct) {
    for (auto m : m_motors) if (m) m->spin(dir, vel, units);
  }
  void stop(brakeType bt = brakeType::coast) {
    for (auto m : m_motors) if (m) m->stop(bt);
  }
private:
  std::vector<motor*> m_motors;
};

// Controller/button mock
class controller {
public:
  // Minimal nested button class
  class button {
  public:
    button() : m_pressed(false) {}
    bool pressed() const { return m_pressed.load(); }
    void setPressed(bool p) { m_pressed.store(p); }
  private:
    std::atomic<bool> m_pressed;
  };

  controller() {}

  // common buttons
  button ButtonA;
  button ButtonB;
  button ButtonX;
  button ButtonY;

  // Simple screen printing to stdout/stderr
  class screen {
  public:
    void print(int row, int col, const char* fmt) {
      // very small formatted output for testing
      std::cerr << "[mock controller screen] (" << row << "," << col << ") " << fmt << "\n";
    }
    void clear() { std::cerr << "[mock controller screen] clear\n"; }
  };

  screen Screen;
};

// Brain mock (LCD / timer)
class brain {
public:
  brain() {}

  class lcd {
  public:
    void print(int row, const char* text) {
      std::cerr << "[mock brain lcd] row " << row << ": " << text << "\n";
    }
    void clear_line(int row) {
      std::cerr << "[mock brain lcd] clear line " << row << "\n";
    }
  };

  lcd Screen;

  // simple timer: returns milliseconds since program start (mock)
  uint64_t timer(msec ms = msec(0)) {
    (void)ms;
    using namespace std::chrono;
    static auto start = steady_clock::now();
    auto now = steady_clock::now();
    return static_cast<uint64_t>(duration_cast<milliseconds>(now - start).count());
  }
};

// Competition mock: you can register callbacks; run() will call them in sequence.
// For tests, run() will call the previously-registered autonomous and driver control callbacks.
class competition {
public:
  competition() : _auton(nullptr), _driver(nullptr) {}

  void setAutonomous(std::function<void()> f) { _auton = f; }
  void setDriverControl(std::function<void()> f) { _driver = f; }

  // Call this to simulate the competition starting
  void run() {
    if (_auton) {
      std::cerr << "[mock competition] running autonomous\n";
      _auton();
    }
    if (_driver) {
      std::cerr << "[mock competition] running driver control\n";
      _driver();
    }
  }

private:
  std::function<void()> _auton;
  std::function<void()> _driver;
};

// A couple of utility mocks (sensors)
class limit {
public:
  limit() : _pressed(false) {}
  bool pressed() const { return _pressed.load(); }
  void setPressed(bool v) { _pressed.store(v); }
private:
  std::atomic<bool> _pressed;
};

class inertial {
public:
  inertial() : _angle_deg(0.0) {}
  double heading() const { return _angle_deg; }
  void set_heading(double deg) { _angle_deg = deg; }
private:
  double _angle_deg;
};

// Simple delay helper
inline void task::sleep(int ms) {} // (not a full task implementation)

// Inline global objects to mimic typical VEX programs
inline vex::brain Brain;
inline vex::controller Controller;
inline vex::competition Competition;

// Convenience typedefs and small helpers that appear in many VEX programs
using V5 = vex; // legacy alias

} // namespace vex