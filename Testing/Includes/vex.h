// Mock vex.h - C-style minimal stub of the VEX C++ API for tests
// Uses only standard C/C++ headers available in C++03/C99.
// Works with old toolchains (gcc 4.9.3, clang++).

#ifndef TESTING_INCLUDES_VEX_H
#define TESTING_INCLUDES_VEX_H

#include <stdint.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <time.h>

#ifdef __cplusplus
extern "C" {
#endif

    // enums
    typedef enum { FWD = 1, REV = -1 } directionType;
    typedef enum { COAST, BRAKE, HOLD } brakeType;
    typedef enum { PCT, RPM } velocityUnits;
    typedef enum { DEG, REV_U } rotationUnits; // renamed REV_U to avoid clash
    typedef enum { MM, IN } distanceUnits;

    // simple timer (milliseconds since program start)
    static inline uint64_t vex_timer(void) {
        static clock_t start = 0;
        if (!start) start = clock();
        clock_t now = clock();
        return (uint64_t)((now - start) * 1000 / CLOCKS_PER_SEC);
    }

    // minimal motor struct
    typedef struct {
        int port;
        int reversed;
        double rotation_deg;
        double velocity;
        brakeType brake;
        int spinning;
    } vex_motor;

    // motor API
    static inline void motor_init(vex_motor* m, int port, int reversed) {
        m->port = port;
        m->reversed = reversed;
        m->rotation_deg = 0.0;
        m->velocity = 0.0;
        m->brake = COAST;
        m->spinning = 0;
        fprintf(stderr, "[mock motor] port %d initialized\n", port);
    }

    static inline void motor_spin(vex_motor* m, directionType dir, double velocity, velocityUnits units) {
        m->spinning = 1;
        m->velocity = (dir == FWD ? 1.0 : -1.0) * velocity;
        fprintf(stderr, "[mock motor] port %d spin %s vel=%.2f%s\n", m->port,
            dir == FWD ? "fwd" : "rev", velocity, units == PCT ? "%" : "rpm");
    }

    static inline void motor_stop(vex_motor* m, brakeType bt) {
        m->spinning = 0;
        m->velocity = 0.0;
        m->brake = bt;
        const char* bstr = bt == COAST ? "coast" : bt == BRAKE ? "brake" : "hold";
        fprintf(stderr, "[mock motor] port %d stop (brake=%s)\n", m->port, bstr);
    }

    static inline void motor_reset_rotation(vex_motor* m) {
        m->rotation_deg = 0.0;
        fprintf(stderr, "[mock motor] port %d resetRotation\n", m->port);
    }

    static inline double motor_rotation(vex_motor* m, rotationUnits units) {
        if (units == DEG) return m->rotation_deg;
        return m->rotation_deg / 360.0;
    }

    // controller mock
    typedef struct {
        int ButtonA, ButtonB, ButtonX, ButtonY;
    } vex_controller;

    static inline void controller_print(const char* msg) {
        fprintf(stderr, "[mock controller screen] %s\n", msg);
    }

    // brain mock
    typedef struct {} vex_brain;
    static inline void brain_print(int row, const char* msg) {
        fprintf(stderr, "[mock brain lcd] row %d: %s\n", row, msg);
    }

    // competition mock
    typedef void (*vex_callback)(void);

    typedef struct {
        vex_callback auton;
        vex_callback driver;
    } vex_competition;

    static inline void competition_set_auton(vex_competition* c, vex_callback f) { c->auton = f; }
    static inline void competition_set_driver(vex_competition* c, vex_callback f) { c->driver = f; }
    static inline void competition_run(vex_competition* c) {
        if (c->auton) { fprintf(stderr, "[mock competition] running autonomous\n"); c->auton(); }
        if (c->driver) { fprintf(stderr, "[mock competition] running driver control\n"); c->driver(); }
    }

#ifdef __cplusplus
} // extern "C"
#endif

#endif // TESTING_INCLUDES_VEX_H
