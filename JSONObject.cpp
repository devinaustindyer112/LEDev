#include "JSONObject.hpp"
#include "JSONValue.hpp"
#include "String.hpp"
#include "Map.hpp"

JSONObject::JSONObject()
{
    this->entries = Map<JFA::String, JSONValue>();
}

// Copy constructor (Deep copy)
JSONObject::JSONObject(const JSONObject &other)
{
    this->entries = other.entries;
}

// Deep copy assignment operator
JSONObject &JSONObject::operator=(const JSONObject &other)
{
    if (this != &other)
    {
        this->entries = other.entries;
    }
    return *this;
}

JSONObject::JSONObject(JFA::String key, JSONValue value)
{
    this->entries = Map<JFA::String, JSONValue>();
    this->entries.put(key, value);
}

JSONValue JSONObject::get(JFA::String key)
{
    return this->entries.get(key);
}

bool JSONObject::operator==(const JSONObject &other) const
{
    return this->entries == other.entries;
}