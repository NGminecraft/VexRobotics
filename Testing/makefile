# Testing makefile: invoke root makefile but override include directory
# This reuses the same vex build rules while using Testing/Includes for headers

.PHONY: all clean

CXX_FLAGS := $(filter-out -I$(VEX_SDK_PATH)/$(PLATFORM)/gcc/include/c++/4.9.3%, $(CXX_FLAGS))

all:
	$(MAKE) -C .. INC_F="Testing/Includes include"

clean:
	$(MAKE) -C .. clean

LDLIBS = -lm
