/**
 * VEX Robotics API Mock Implementation
 * This is a mock version of the VEX API for development/testing purposes
 */

#ifndef VEX_H
#define VEX_H

#include <cstdint>
#include <string>
#include <cmath>

namespace vex {

// ============================================================================
// Port Constants
// ============================================================================

constexpr int32_t PORT1 = 1;
constexpr int32_t PORT2 = 2;
constexpr int32_t PORT3 = 3;
constexpr int32_t PORT4 = 4;
constexpr int32_t PORT5 = 5;
constexpr int32_t PORT6 = 6;
constexpr int32_t PORT7 = 7;
constexpr int32_t PORT8 = 8;
constexpr int32_t PORT9 = 9;
constexpr int32_t PORT10 = 10;
constexpr int32_t PORT11 = 11;
constexpr int32_t PORT12 = 12;
constexpr int32_t PORT13 = 13;
constexpr int32_t PORT14 = 14;
constexpr int32_t PORT15 = 15;
constexpr int32_t PORT16 = 16;
constexpr int32_t PORT17 = 17;
constexpr int32_t PORT18 = 18;
constexpr int32_t PORT19 = 19;
constexpr int32_t PORT20 = 20;
constexpr int32_t PORT21 = 21;

// ============================================================================
// Enumerations
// ============================================================================

enum class directionType {
    fwd = 0,
    rev = 1
};

enum class rotationUnits {
    deg,
    rev,
    raw
};

enum class velocityUnits {
    pct,
    rpm,
    dps
};

enum class percentUnits {
    pct
};

enum class voltageUnits {
    volt,
    mV
};

enum class currentUnits {
    amp
};

enum class powerUnits {
    watt
};

enum class torqueUnits {
    Nm,
    InLb
};

enum class distanceUnits {
    mm,
    in,
    cm,
    m
};

enum class turnType {
    left,
    right
};

enum class brakeType {
    coast,
    brake,
    hold
};

enum class gearSetting {
    ratio36_1,  // Red - 100 RPM
    ratio18_1,  // Green - 200 RPM
    ratio6_1    // Blue - 600 RPM
};

enum class timeUnits {
    sec,
    msec
};

enum class temperatureUnits {
    celsius,
    fahrenheit
};

// ============================================================================
// Color Class
// ============================================================================

class color {
public:
    uint32_t rgb;
    
    color() : rgb(0) {}
    color(uint32_t value) : rgb(value) {}
    color(uint8_t r, uint8_t g, uint8_t b) : rgb((r << 16) | (g << 8) | b) {}
    
    static const color black;
    static const color white;
    static const color red;
    static const color green;
    static const color blue;
    static const color yellow;
    static const color orange;
    static const color purple;
    static const color cyan;
};

inline const color color::black = color(0x000000);
inline const color color::white = color(0xFFFFFF);
inline const color color::red = color(0xFF0000);
inline const color color::green = color(0x00FF00);
inline const color color::blue = color(0x0000FF);
inline const color color::yellow = color(0xFFFF00);
inline const color color::orange = color(0xFF8000);
inline const color color::purple = color(0x8000FF);
inline const color color::cyan = color(0x00FFFF);

// ============================================================================
// Motor Class
// ============================================================================

class motor {
private:
    [[maybe_unused]] int32_t port_num;
    bool reversed;
    double position_value;
    double velocity_value;
    brakeType brake_mode;
    
public:
    motor(int32_t port, bool reverse = false) 
        : port_num(port), reversed(reverse), position_value(0), 
          velocity_value(0), brake_mode(brakeType::coast) {}
    
    motor(int32_t port, gearSetting gears, bool reverse = false)
        : port_num(port), reversed(reverse), position_value(0),
          velocity_value(0), brake_mode(brakeType::coast) {}
    
    void setReversed(bool value) { reversed = value; }
    bool isReversed() const { return reversed; }
    
    void spin(directionType dir) { velocity_value = (dir == directionType::fwd) ? 100 : -100; }
    void spin(directionType dir, double vel, velocityUnits units) { 
        velocity_value = (dir == directionType::fwd) ? vel : -vel;
    }
    void spin(directionType dir, double vel, percentUnits units) {
        velocity_value = (dir == directionType::fwd) ? vel : -vel;
    }
    void spin(directionType dir, double vel, voltageUnits units) {
        velocity_value = (dir == directionType::fwd) ? vel : -vel;
    }
    
    void stop() { velocity_value = 0; }
    void stop(brakeType mode) { brake_mode = mode; velocity_value = 0; }
    void setStopping(brakeType mode) { brake_mode = mode; }
    
    void setVelocity(double vel, velocityUnits units) { velocity_value = vel; }
    void setVelocity(double vel, percentUnits units) { velocity_value = vel; }
    
    void setMaxTorque(double value, percentUnits units) {}
    void setMaxTorque(double value, currentUnits units) {}
    void setMaxTorque(double value, torqueUnits units) {}
    
    void spinToPosition(double pos, rotationUnits units) { position_value = pos; }
    void spinToPosition(double pos, rotationUnits units, double vel, velocityUnits velUnits) {
        position_value = pos;
    }
    void spinToPosition(double pos, rotationUnits units, bool waitForCompletion) {
        position_value = pos;
    }
    void spinToPosition(double pos, rotationUnits units, double vel, velocityUnits velUnits, bool waitForCompletion) {
        position_value = pos;
    }
    
    void spinFor(double rotation, rotationUnits units) { position_value += rotation; }
    void spinFor(double rotation, rotationUnits units, double vel, velocityUnits velUnits) {
        position_value += rotation;
    }
    void spinFor(double rotation, rotationUnits units, bool waitForCompletion) {
        position_value += rotation;
    }
    void spinFor(double rotation, rotationUnits units, double vel, velocityUnits velUnits, bool waitForCompletion) {
        position_value += rotation;
    }
    void spinFor(directionType dir, double rotation, rotationUnits units) {
        position_value += (dir == directionType::fwd) ? rotation : -rotation;
    }
    void spinFor(directionType dir, double rotation, rotationUnits units, double vel, velocityUnits velUnits) {
        position_value += (dir == directionType::fwd) ? rotation : -rotation;
    }
    
    void resetPosition() { position_value = 0; }
    void setPosition(double pos, rotationUnits units) { position_value = pos; }
    
    double position(rotationUnits units) const { return position_value; }
    double velocity(velocityUnits units) const { return velocity_value; }
    double velocity(percentUnits units) const { return velocity_value; }
    
    double current() const { return 0.5; }
    double current(currentUnits units) const { return 0.5; }
    double voltage() const { return 12.0; }
    double voltage(voltageUnits units) const { return 12.0; }
    double power() const { return 6.0; }
    double power(powerUnits units) const { return 6.0; }
    double torque(torqueUnits units) const { return 1.0; }
    double efficiency() const { return 85.0; }
    double temperature(temperatureUnits units = temperatureUnits::celsius) const { return 25.0; }
    
    bool isSpinning() const { return std::abs(velocity_value) > 0.1; }
    bool isDone() const { return !isSpinning(); }
    
    void setTimeout(int32_t time, timeUnits units) {}
};

// ============================================================================
// Motor Group Class
// ============================================================================

class motor_group {
private:
    double velocity_value;
    double position_value;
    
public:
    motor_group(motor& m1) : velocity_value(0), position_value(0) {}
    motor_group(motor& m1, motor& m2) : velocity_value(0), position_value(0) {}
    motor_group(motor& m1, motor& m2, motor& m3) : velocity_value(0), position_value(0) {}
    motor_group(motor& m1, motor& m2, motor& m3, motor& m4) : velocity_value(0), position_value(0) {}
    
    void spin(directionType dir) { velocity_value = (dir == directionType::fwd) ? 100 : -100; }
    void spin(directionType dir, double vel, velocityUnits units) {
        velocity_value = (dir == directionType::fwd) ? vel : -vel;
    }
    void spin(directionType dir, double vel, percentUnits units) {
        velocity_value = (dir == directionType::fwd) ? vel : -vel;
    }
    
    void stop() { velocity_value = 0; }
    void stop(brakeType mode) { velocity_value = 0; }
    void setStopping(brakeType mode) {}
    
    void setVelocity(double vel, velocityUnits units) { velocity_value = vel; }
    void setVelocity(double vel, percentUnits units) { velocity_value = vel; }
    
    void spinFor(double rotation, rotationUnits units) { position_value += rotation; }
    void spinFor(double rotation, rotationUnits units, bool waitForCompletion) { position_value += rotation; }
    void spinFor(directionType dir, double rotation, rotationUnits units) {
        position_value += (dir == directionType::fwd) ? rotation : -rotation;
    }
    
    void resetPosition() { position_value = 0; }
    void setPosition(double pos, rotationUnits units) { position_value = pos; }
    
    double position(rotationUnits units) const { return position_value; }
    double velocity(velocityUnits units) const { return velocity_value; }
    
    bool isSpinning() const { return std::abs(velocity_value) > 0.1; }
    bool isDone() const { return !isSpinning(); }
};

// ============================================================================
// Controller Classes
// ============================================================================

class controller {
public:
    enum class controllerType {
        primary,
        partner
    };
    
    class axis {
    private:
        int32_t axis_value;
    public:
        axis() : axis_value(0) {}
        int32_t position() const { return axis_value; }
        int32_t value() const { return axis_value; }
        void setValue(int32_t v) { axis_value = v; }
    };
    
    class button {
    private:
        bool pressed;
    public:
        button() : pressed(false) {}
        bool pressing() const { return pressed; }
        void setPressed(bool p) { pressed = p; }
    };
    
    class lcd {
    public:
        void print(const char* format, ...) {}
        void print(int row, const char* format, ...) {}
        void setCursor(int row, int col) {}
        void clearScreen() {}
        void clearLine() {}
        void clearLine(int row) {}
    };
    
    axis Axis1;
    axis Axis2;
    axis Axis3;
    axis Axis4;
    
    button ButtonL1;
    button ButtonL2;
    button ButtonR1;
    button ButtonR2;
    button ButtonUp;
    button ButtonDown;
    button ButtonLeft;
    button ButtonRight;
    button ButtonX;
    button ButtonB;
    button ButtonY;
    button ButtonA;
    
    lcd Screen;
    
    controller(controllerType type = controllerType::primary) {}
    
    void rumble(const char* pattern) {}
};

// ============================================================================
// Brain Class
// ============================================================================

class brain {
public:
    class lcd {
    public:
        void print(const char* format, ...) {}
        void print(int row, const char* format, ...) {}
        void printAt(int x, int y, const char* format, ...) {}
        void setCursor(int row, int col) {}
        void clearScreen() {}
        void clearLine() {}
        void clearLine(int row) {}
        void drawPixel(int x, int y) {}
        void drawLine(int x1, int y1, int x2, int y2) {}
        void drawRectangle(int x, int y, int width, int height) {}
        void drawCircle(int x, int y, int radius) {}
        void setPenColor(color c) {}
        void setFillColor(color c) {}
        void setPenWidth(uint32_t width) {}
        int xPosition() const { return 0; }
        int yPosition() const { return 0; }
        bool pressing() const { return false; }
    };
    
    class battery {
    public:
        double voltage() const { return 12.5; }
        double current() const { return 1.0; }
        double capacity() const { return 80.0; }
        double temperature(temperatureUnits units = temperatureUnits::celsius) const { return 25.0; }
    };
    
    class timer {
    private:
        uint32_t start_time;
    public:
        timer() : start_time(0) {}
        double time() const { return 0.0; }
        double time(timeUnits units) const { return 0.0; }
        void reset() { start_time = 0; }
        void clear() { start_time = 0; }
    };
    
    lcd Screen;
    battery Battery;
    timer Timer;
    
    brain() {}
};

// ============================================================================
// Inertial Sensor Class
// ============================================================================

class inertial {
private:
    double heading_value;
    double rotation_value;
    bool calibrating;
    
public:
    inertial(int32_t port) : heading_value(0), rotation_value(0), calibrating(false) {}
    
    void calibrate() { calibrating = true; }
    void calibrate(int32_t value) { calibrating = true; }
    bool isCalibrating() const { return calibrating; }
    void finishCalibration() { calibrating = false; }
    
    double heading() const { return heading_value; }
    double heading(rotationUnits units) const { return heading_value; }
    double rotation() const { return rotation_value; }
    double rotation(rotationUnits units) const { return rotation_value; }
    
    void setHeading(double value, rotationUnits units) { heading_value = value; }
    void setRotation(double value, rotationUnits units) { rotation_value = value; }
    void resetHeading() { heading_value = 0; }
    void resetRotation() { rotation_value = 0; }
    
    double acceleration(double axisType) const { return 0.0; }
    double gyroRate(double axisType, velocityUnits units) const { return 0.0; }
    
    bool installed() const { return true; }
};

// ============================================================================
// Vision Sensor Class
// ============================================================================

class vision {
public:
    struct signature {
        int id;
        signature() : id(0) {}
        signature(int i) : id(i) {}
    };
    
    class object {
    public:
        int centerX;
        int centerY;
        int width;
        int height;
        int id;
        
        object() : centerX(0), centerY(0), width(0), height(0), id(0) {}
        
        bool exists() const { return false; }
    };
    
    vision(int32_t port) {}
    
    int takeSnapshot(signature sig) { return 0; }
    int takeSnapshot(int signatureId) { return 0; }
    int objectCount() { return 0; }
    object largestObject() { return object(); }
    object objects(int index) { return object(); }
    
    void setBrightness(int brightness) {}
    void setSignature(signature sig) {}
    void setWhiteBalance(int mode) {}
    void setLedColor(int r, int g, int b) {}
    void setLedBrightness(int brightness) {}
    
    bool installed() const { return true; }
};

// ============================================================================
// Distance Sensor Class
// ============================================================================

class distance {
private:
    double distance_value;
    
public:
    distance(int32_t port) : distance_value(100.0) {}
    
    double objectDistance(distanceUnits units) const { return distance_value; }
    double objectVelocity() const { return 0.0; }
    bool isObjectDetected() const { return true; }
    double objectSize() const { return 50.0; }
    
    bool installed() const { return true; }
};

// ============================================================================
// Optical Sensor Class
// ============================================================================

class optical {
private:
    double hue_value;
    
public:
    optical(int32_t port) : hue_value(0) {}
    
    double hue() const { return hue_value; }
    double saturation() const { return 50.0; }
    double brightness() const { return 50.0; }
    int color() const { return 0; }
    
    void setLight(int brightness) {}
    void setLightPower(int power, percentUnits units) {}
    
    bool isNearObject() const { return false; }
    
    bool installed() const { return true; }
};

// ============================================================================
// Rotation Sensor Class
// ============================================================================

class rotation {
private:
    double position_value;
    double velocity_value;
    
public:
    rotation(int32_t port, bool reverse = false) : position_value(0), velocity_value(0) {}
    
    double position(rotationUnits units) const { return position_value; }
    double velocity(velocityUnits units) const { return velocity_value; }
    double angle(rotationUnits units) const { return position_value; }
    
    void resetPosition() { position_value = 0; }
    void setPosition(double pos, rotationUnits units) { position_value = pos; }
    
    bool installed() const { return true; }
};

// ============================================================================
// Bumper/Limit Switch Class
// ============================================================================

class bumper {
private:
    bool pressed;
    
public:
    bumper(int32_t port) : pressed(false) {}
    
    bool pressing() const { return pressed; }
    void setPressed(bool p) { pressed = p; }
    
    bool installed() const { return true; }
};

class limit {
private:
    bool pressed;
    
public:
    limit(int32_t port) : pressed(false) {}
    
    bool pressing() const { return pressed; }
    void setPressed(bool p) { pressed = p; }
    
    bool installed() const { return true; }
};

// ============================================================================
// Pneumatics Class
// ============================================================================

class pneumatics {
private:
    bool open_state;
    
public:
    pneumatics(int32_t port) : open_state(false) {}
    
    void open() { open_state = true; }
    void close() { open_state = false; }
    bool value() const { return open_state; }
    
    bool installed() const { return true; }
};

// ============================================================================
// LED Class
// ============================================================================

class led {
private:
    bool on_state;
    
public:
    led(int32_t port) : on_state(false) {}
    
    void on() { on_state = true; }
    void on(int brightness) { on_state = true; }
    void off() { on_state = false; }
    bool value() const { return on_state; }
    
    bool installed() const { return true; }
};

// ============================================================================
// GPS Sensor Class
// ============================================================================

class gps {
private:
    double x_pos;
    double y_pos;
    double heading_value;
    
public:
    gps(int32_t port) : x_pos(0), y_pos(0), heading_value(0) {}
    
    double xPosition(distanceUnits units = distanceUnits::mm) const { return x_pos; }
    double yPosition(distanceUnits units = distanceUnits::mm) const { return y_pos; }
    double heading() const { return heading_value; }
    
    void calibrate() {}
    bool isCalibrating() const { return false; }
    
    bool installed() const { return true; }
};

// ============================================================================
// Competition Class
// ============================================================================

class competition {
public:
    competition() {}
    
    bool isEnabled() const { return true; }
    bool isAutonomous() const { return false; }
    bool isDriverControl() const { return true; }
    bool isCompetitionSwitch() const { return false; }
    bool isFieldControl() const { return false; }
};

// ============================================================================
// Utility Functions
// ============================================================================

inline void wait(double time, timeUnits units) {}
inline void sleep(double time) {}

inline int32_t abs(int32_t value) { return value < 0 ? -value : value; }
inline double fabs(double value) { return value < 0.0 ? -value : value; }

// ============================================================================
// Global Timer Class
// ============================================================================

class timer {
private:
    uint32_t start_time;
public:
    timer() : start_time(0) {}
    double time() const { return 0.0; }
    double time(timeUnits units) const { return 0.0; }
    void reset() { start_time = 0; }
    void clear() { start_time = 0; }
    static double system() { return 0.0; }
    static double systemHighResolution() { return 0.0; }
};

// ============================================================================
// Thread Class
// ============================================================================

class thread {
public:
    thread(int (*callback)(void)) {}
    thread(void (*callback)(void)) {}
};

// ============================================================================
// Mutex Class
// ============================================================================

class mutex {
public:
    mutex() {}
    void lock() {}
    void unlock() {}
};

// ============================================================================
// Triport Class
// ============================================================================

class triport {
public:
    triport(int32_t port) {}
};

} // namespace vex

// ============================================================================
// this_thread namespace for sleep functionality
// ============================================================================

namespace this_thread {
    inline void sleep_for(int32_t milliseconds) {}
    inline void sleep_until(int32_t time) {}
}

#endif // VEX_H
