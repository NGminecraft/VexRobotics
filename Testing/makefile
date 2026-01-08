# Testing makefile: invoke root makefile but override include directory
# This reuses the same vex build rules while using Testing/Includes for headers

.PHONY: all clean

all:
	$(MAKE) -C .. INC_F=Testing/Includes

clean:
	$(MAKE) -C .. clean
