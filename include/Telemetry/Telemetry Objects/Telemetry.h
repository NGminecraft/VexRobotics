template <typename T>
class Telemetry {
public:
	inline const T getData() {
		return data;
	};

	virtual void updateData() = 0;
private:
	T data;
};