#ifndef TESTING_INCLUDES_VEX_H
#define TESTING_INCLUDES_VEX_H

#include <stdint.h>

namespace vex {

	enum directionType { fwd = 1, rev = -1 };
	enum brakeType { coast, brake, hold };
	enum velocityUnits { pct, rpm };
	enum rotationUnits { deg, rev_u };
	enum distanceUnits { mm, in };

	struct motor {
		motor(int port = 1, bool reversed = 0) {}
		void spin(directionType, double, velocityUnits = pct) {}
		void stop(brakeType = coast) {}
		void resetRotation() {}
		double rotation(rotationUnits = deg) { return 0; }
	};

	struct controller {
		struct button { int pressed() { return 0; } };
		button ButtonA, ButtonB, ButtonX, ButtonY;
		struct screen { void print(int, int, const char*) {}; void clear() {}; };
		screen Screen;
	};

	struct brain {
		struct lcd { void print(int, const char*) {}; void clear_line(int) {}; };
		lcd Screen;
	};

	struct competition {
		void setAutonomous(void (*)()) {}
		void setDriverControl(void (*)()) {}
		void run() {}
	};

	// globals
	extern brain Brain;
	extern controller Controller;
	extern competition Competition;

} // namespace vex

#endif // TESTING_INCLUDES_VEX_H
