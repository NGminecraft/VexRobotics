#pragma once
// A abstract class representing a stateful object (e.g., motor, sensor)
template <typename T>
class StateObject {
public:
	StateObject(T& obj) : object(obj) {}

	virtual void update(unsigned long tick) = 0;

	T& getObject() { return object; }
protected:
	T& object;
};