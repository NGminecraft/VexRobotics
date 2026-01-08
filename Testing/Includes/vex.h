// Mock vex.h - minimal stub of the VEX C++ API for tests
// Place this file in your include path when building tests.
// Lightweight header-only mock for compilation and simple runtime tests.

#ifndef TESTING_INCLUDES_VEX_H
#define TESTING_INCLUDES_VEX_H

#include <stdint.h>     // fixed-width integers
#include <string>
#include <vector>
#include <cmath>
#include <cstdlib>
#include <chrono>

#if __cplusplus >= 201103L
#include <mutex>
#include <thread>
#endif

namespace vex {

    // Basic enums and units used in VEX API
    enum class directionType { fwd = 1, rev = -1 };
    enum class brakeType { coast, brake, hold };
    enum class velocityUnits { pct, rpm };
    enum class rotationUnits { deg, rev };
    enum class distanceUnits { mm, in };

    // Simple time utility
    typedef std::chrono::milliseconds msec;

    // Minimal motor mock
    class motor {
    public:
        motor(int port = 1, bool reversed = false)
            : m_port(port), m_reversed(reversed), m_rotation_deg(0.0),
            m_brake(brakeType::coast), m_spinning(false), m_velocity(0.0) {
        }

        void spin(directionType dir, double velocity, velocityUnits units = velocityUnits::pct) {
#if __cplusplus >= 201103L
            std::lock_guard<std::mutex> lk(m_mutex);
#endif
            m_spinning = true;
            m_velocity = (dir == directionType::fwd ? 1.0 : -1.0) * velocity;
            fprintf(stderr, "[mock motor] port %d spin %s vel=%.2f%s\n",
                m_port, (dir == directionType::fwd ? "fwd" : "rev"), velocity,
                units == velocityUnits::pct ? "%" : "rpm");
        }

        void stop(brakeType bt = brakeType::coast) {
#if __cplusplus >= 201103L
            std::lock_guard<std::mutex> lk(m_mutex);
#endif
            m_spinning = false;
            m_velocity = 0.0;
            m_brake = bt;
            const char* bstr = (bt == brakeType::coast ? "coast" : bt == brakeType::brake ? "brake" : "hold");
            fprintf(stderr, "[mock motor] port %d stop (brake=%s)\n", m_port, bstr);
        }

        void resetRotation() {
#if __cplusplus >= 201103L
            std::lock_guard<std::mutex> lk(m_mutex);
#endif
            m_rotation_deg = 0.0;
            fprintf(stderr, "[mock motor] port %d resetRotation\n", m_port);
        }

        double rotation(rotationUnits units = rotationUnits::deg) {
#if __cplusplus >= 201103L
            std::lock_guard<std::mutex> lk(m_mutex);
#endif
            if (units == rotationUnits::deg) return m_rotation_deg;
            return m_rotation_deg / 360.0;
        }

    private:
        int m_port;
        bool m_reversed;
        double m_rotation_deg;
        brakeType m_brake;
        bool m_spinning;
        double m_velocity;
#if __cplusplus >= 201103L
        std::mutex m_mutex;
#endif
    };

    // Simple motor_group mock
    class motor_group {
    public:
        motor_group() {}
        motor_group(std::initializer_list<motor*> motors) : m_motors(motors) {}
        void spin(directionType dir, double vel, velocityUnits units = velocityUnits::pct) {
            for (auto* m : m_motors) if (m) m->spin(dir, vel, units);
        }
        void stop(brakeType bt = brakeType::coast) {
            for (auto* m : m_motors) if (m) m->stop(bt);
        }
    private:
        std::vector<motor*> m_motors;
    };

    // Controller mock
    class controller {
    public:
        class button {
        public:
            button() : m_pressed(false) {}
            bool pressed() const { return m_pressed; }
            void setPressed(bool p) { m_pressed = p; }
        private:
            bool m_pressed;
        };

        button ButtonA, ButtonB, ButtonX, ButtonY;

        class screen {
        public:
            void print(int row, int col, const char* fmt) {
                fprintf(stderr, "[mock controller screen] (%d,%d) %s\n", row, col, fmt);
            }
            void clear() { fprintf(stderr, "[mock controller screen] clear\n"); }
        };

        screen Screen;
    };

    // Brain mock
    class brain {
    public:
        class lcd {
        public:
            void print(int row, const char* text) { fprintf(stderr, "[mock brain lcd] row %d: %s\n", row, text); }
            void clear_line(int row) { fprintf(stderr, "[mock brain lcd] clear line %d\n", row); }
        };
        lcd Screen;

        uint64_t timer(msec ms = msec(0)) {
            (void)ms;
            using namespace std::chrono;
            static steady_clock::time_point start = steady_clock::now();
            return static_cast<uint64_t>(duration_cast<milliseconds>(steady_clock::now() - start).count());
        }
    };

    // Competition mock
    class competition {
    public:
        competition() : _auton(nullptr), _driver(nullptr) {}
        void setAutonomous(void (*f)()) { _auton = f; }
        void setDriverControl(void (*f)()) { _driver = f; }
        void run() {
            if (_auton) { fprintf(stderr, "[mock competition] running autonomous\n"); _auton(); }
            if (_driver) { fprintf(stderr, "[mock competition] running driver control\n"); _driver(); }
        }
    private:
        void (*_auton)();
        void (*_driver)();
    };

    // Globals
    extern vex::brain Brain;
    extern vex::controller Controller;
    extern vex::competition Competition;

} // namespace vex

#endif // TESTING_INCLUDES_VEX_H
