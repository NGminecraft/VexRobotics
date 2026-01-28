#pragma once
#include "vex.h"

// Forward declaration
template <typename T>
struct TelemetryDataPoint;

// Base class for any telemetry objects
template <typename T>
class Telemetry {
public:
	inline const TelemetryDataPoint<T> getData() const {
		return data;
	};

	inline const TelemetryDataPoint<T> getPreviousData() {
		return previousData;
	}

	inline void update(unsigned long tick) {
		previousData = data; // Store previous data point
		double time = vex::timer::system(); // Time to reference for this data point
		data = TelemetryDataPoint<T>::create(
			tick,
			time - previousData.time,
			time,
			newData()
		);
	};

protected:
	TelemetryDataPoint<T> data;
	TelemetryDataPoint<T> previousData; // This value needs to be sampled on instantiation

	virtual T newData() = 0; // virtual method to get a new data point

};

// Struct to hold a single data point for telemetry, as well as metadata about when it was recorded
template <typename T>
struct TelemetryDataPoint {

	// Factory method to create the data point
	static TelemetryDataPoint<T> create(unsigned long t, double time_since_last, double time, T val) {
		TelemetryDataPoint<T> point;
		point.tick = t;
		point.timeSinceLastUpdate = time_since_last;
		point.time = time;
		point.value = val;
		return point;
	}

	unsigned long tick;
	double timeSinceLastUpdate;
	double time;
	T value;
};