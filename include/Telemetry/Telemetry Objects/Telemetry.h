// This will need to be changed. We want to track some tick idenifier for each instance of updateData being called, as well as time since last call. Probably should use a struct
// We also may want to remember the last value as well

template <typename T>
class Telemetry {
public:
	inline const T getData() {
		return data;
	};

	virtual void updateData() = 0;
protected:
	T data;
};