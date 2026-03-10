#pragma once
#include <initializer_list>

#define TELEMETRY_ENUM(...) \
    enum class TelemetryTypes { __VA_ARGS__ };

// Generate common telemetry method implementations
#define TELEMETRY_METHODS_IMPL(ClassName, Count) \
    void addTelemetryObject(TelemetryTypes type) { \
        int idx = static_cast<int>(type); \
        if (telemetryObjects[idx] != nullptr) { \
            delete telemetryObjects[idx]; \
        } \
        telemetryObjects[idx] = instantiateTelemetry(type); \
    } \
    \
    void addTelemetryObject(TelemetryTypes type, unsigned int updateInterval) { \
        addTelemetryObject(type); \
        setInterval(type, updateInterval); \
    } \
    \
    void setInterval(TelemetryTypes type, unsigned int interval) { \
        int idx = static_cast<int>(type); \
        setTelemetryInterval(idx, interval); \
    } \
    \
    void setInterval(std::initializer_list<unsigned int> intervals) { \
        if (intervals.size() != Count) { \
            return; \
        } \
        auto it = intervals.begin(); \
        for (size_t i = 0; i < Count; i++, ++it) { \
            if (telemetryObjects[i] == nullptr && *it != 0) { \
                addTelemetryObject(static_cast<TelemetryTypes>(i), *it); \
            } else if (telemetryObjects[i] != nullptr) {\
                telemetryObjects[i]->setUpdateInterval(*it); \
            } \
        } \
    } \
    \
    void initializeTelemetries(const unsigned int(&intervals)[Count]) { \
        for (size_t i = 0; i < Count; i++) { \
            if (intervals[i] != 0) { \
                addTelemetryObject(static_cast<TelemetryTypes>(i), intervals[i]); \
            }\
        } \
    } \
    TelemetryBase* getTelemetryBase(TelemetryTypes type) { \
        return telemetryObjects[static_cast<int>(type)]; \
    } \
    \
    template <TelemetryTypes T> \
    auto getTelemetry()  -> decltype(instantiateTelemetry(T)) { \
        return static_cast<decltype(instantiateTelemetry(T))>(getTelemetryBase(T)); \
    } \
// Generate the switch statement for instantiateTelemetry
#define TELEMETRY_CASE(Type, Class) \
    case TelemetryTypes::Type: return new Class(this->object);

#define BEGIN_TELEMETRY_SWITCH() \
    TelemetryBase* instantiateTelemetry(TelemetryTypes type) { \
        switch (type) {

#define END_TELEMETRY_SWITCH() \
            default: return nullptr; \
        } \
    }

// Unified X-Macro System for Telemetry
// Usage: Define TELEMETRY_LIST with X(EnumName, DataType, ClassName) entries
// Then use TELEMETRY_GENERATE_ALL to create everything

#define TELEMETRY_GENERATE_ENUM(LIST) \
    enum class TelemetryTypes { \
        LIST(TELEMETRY_ENUM_ENTRY) \
    };

#define TELEMETRY_ENUM_ENTRY(Name, DataType, Class) Name,

#define TELEMETRY_GENERATE_TYPE_TRAITS(LIST) \
    template<TelemetryTypes Type> \
    struct TelemetryTypeTraits; \
    \
    LIST(TELEMETRY_TYPE_TRAIT_ENTRY)

#define TELEMETRY_TYPE_TRAIT_ENTRY(Name, DataType, Class) \
    template<> \
    struct TelemetryTypeTraits<TelemetryTypes::Name> { \
        using type = DataType; \
    };

#define TELEMETRY_GENERATE_SWITCH(LIST) \
    TelemetryBase* instantiateTelemetry(TelemetryTypes type) { \
        switch (type) { \
            LIST(TELEMETRY_SWITCH_CASE) \
            default: return nullptr; \
        } \
    }

#define TELEMETRY_SWITCH_CASE(Name, DataType, Class) \
    case TelemetryTypes::Name: return new Class(this->object);

#define TELEMETRY_GENERATE_METHODS(Count) \
    void addTelemetryObject(TelemetryTypes type) { \
        int idx = static_cast<int>(type); \
        if (telemetryObjects[idx] != nullptr) { \
            delete telemetryObjects[idx]; \
        } \
        telemetryObjects[idx] = instantiateTelemetry(type); \
    } \
    \
    void addTelemetryObject(TelemetryTypes type, unsigned int updateInterval) { \
        addTelemetryObject(type); \
        setInterval(type, updateInterval); \
    } \
    \
    void setInterval(TelemetryTypes type, unsigned int interval) { \
        int idx = static_cast<int>(type); \
        setTelemetryInterval(idx, interval); \
    } \
    \
    void setInterval(unsigned int(&intervals)[Count]) { \
        for (size_t i = 0; i < Count; i++) { \
            if (telemetryObjects[i] != nullptr) { \
                telemetryObjects[i]->setUpdateInterval(intervals[i]); \
            } \
        } \
    } \
    \
    void setInterval(std::initializer_list<unsigned int> intervals) { \
        if (intervals.size() != Count) { \
            return; \
        } \
        auto it = intervals.begin(); \
        for (size_t i = 0; i < Count; i++, ++it) { \
            if (telemetryObjects[i] == nullptr && *it != 0) { \
                addTelemetryObject(static_cast<TelemetryTypes>(i), *it); \
            } else if (telemetryObjects[i] != nullptr) {\
                telemetryObjects[i]->setUpdateInterval(*it); \
            } \
        } \
    } \
    \
    TelemetryBase* getTelemetryBase(TelemetryTypes type) { \
        return telemetryObjects[static_cast<int>(type)]; \
    } \
    \
    template <TelemetryTypes T> \
    Telemetry<typename TelemetryTypeTraits<T>::type>* getTelemetry() { \
        return static_cast<Telemetry<typename TelemetryTypeTraits<T>::type>*>( \
            getTelemetryBase(T) \
        ); \
    }

#define TELEMETRY_GENERATE_ALL(LIST, Count) \
    TELEMETRY_GENERATE_ENUM(LIST) \
    TELEMETRY_GENERATE_TYPE_TRAITS(LIST) \
    TELEMETRY_GENERATE_METHODS(Count) \
private: \
    TELEMETRY_GENERATE_SWITCH(LIST) \
public: