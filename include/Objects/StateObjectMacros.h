#pragma once

#define TELEMETRY_ENUM(...) \
    enum class TelemetryTypes { __VA_ARGS__ };

// Generate common telemetry method implementations
#define TELEMETRY_METHODS_IMPL(ClassName, Count) \
    void ClassName::addTelemetryObject(TelemetryTypes type) { \
        int idx = static_cast<int>(type); \
        if (telemetryObjects[idx] != nullptr) { \
            delete telemetryObjects[idx]; \
        } \
        telemetryObjects[idx] = instantiateTelemetry(type); \
    } \
    \
    void ClassName::addTelemetryObject(TelemetryTypes type, unsigned int updateInterval) { \
        addTelemetryObject(type); \
        setInterval(type, updateInterval); \
    } \
    \
    void ClassName::setInterval(TelemetryTypes type, unsigned int interval) { \
        int idx = static_cast<int>(type); \
        setTelemetryInterval(idx, interval); \
    } \
    \
    void ClassName::setInterval(unsigned int(&intervals)[Count]) { \
        for (size_t i = 0; i < Count; i++) { \
            if (telemetryObjects[i] != nullptr) { \
                telemetryObjects[i]->setUpdateInterval(intervals[i]); \
            } \
        } \
    }

// Generate the switch statement for instantiateTelemetry
#define TELEMETRY_CASE(Type, Class) \
    case TelemetryTypes::Type: return new Class(object);

#define BEGIN_TELEMETRY_SWITCH() \
    TelemetryBase* instantiateTelemetry(TelemetryTypes type) { \
        switch (type) {

#define END_TELEMETRY_SWITCH() \
            default: return nullptr; \
        } \
    }