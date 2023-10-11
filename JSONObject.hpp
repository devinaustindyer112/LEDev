#ifndef JSONOBJECT_HPP
#define JSONOBJECT_HPP
#include "JSONValue.hpp"
#include "String.hpp"
#include "Map.hpp"

class JSONObject
{
public:
    Map<JFA::String, JSONValue> entries;
    JSONObject();
    JSONObject(const JSONObject &other);
    JSONObject(JFA::String key, JSONValue value);
    JSONObject &operator=(const JSONObject &other);
    JSONValue get(JFA::String key);
    bool operator==(const JSONObject &object) const;
};

#endif // JSONOBJECT_HPP