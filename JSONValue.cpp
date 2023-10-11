#include "JSONValue.hpp"
#include "JSONObject.hpp"
#include "String.hpp"
#include "Array.hpp"

JSONValue::JSONValue()
{
    this->type = Type::NULL_VALUE;
    this->string = "";
    this->object = nullptr;
    this->array = nullptr;
}

// Copy constructor (Deep copy)
JSONValue::JSONValue(const JSONValue &other)
{
    this->type = other.type;
    this->string = other.string; // Assuming String has a proper copy constructor

    if (other.type == Type::OBJECT)
    {
        this->object = new JSONObject(*other.object); // Deep copy JSONObject
    }
    else if (other.type == Type::ARRAY)
    {
        this->array = new Array<JSONValue>(*other.array); // Deep copy Array<JSONValue>
    }
    else if (other.type == Type::NULL_VALUE)
    {
        this->type = Type::NULL_VALUE;
    }
}

// Deep copy assignment operator
JSONValue &JSONValue::operator=(const JSONValue &other)
{
    if (this != &other)
    {
        this->type = other.type;
        this->string = other.string;

        // Delete the existing memory (if applicable)
        if (this->type == Type::OBJECT)
        {
            delete this->object;
        }
        else if (this->type == Type::ARRAY)
        {
            delete this->array;
        }

        // Perform a deep copy of data members
        if (other.type == Type::OBJECT)
        {
            this->object = new JSONObject(*other.object);
        }
        else if (other.type == Type::ARRAY)
        {
            this->array = new Array<JSONValue>(*other.array); // Deep copy Array<JSONValue>
        }
    }
    return *this;
}

// Destructor
JSONValue::~JSONValue()
{
    if (this->type == Type::OBJECT)
    {
        delete this->object;
    }
    else if (this->type == Type::ARRAY)
    {
        delete this->array;
    }
}

JSONValue::JSONValue(JFA::String string)
{
    this->type = Type::STRING;
    this->string = string;
}

JSONValue::JSONValue(JSONObject object)
{
    this->type = Type::OBJECT;
    this->object = new JSONObject(object);
}

JSONValue::JSONValue(Array<JSONValue> *array)
{
    this->type = Type::ARRAY;
    this->array = new Array<JSONValue>(array);
}

JSONValue JSONValue::get(JFA::String key)
{
    if (this->type == JSONValue::Type::OBJECT)
    {
        return this->object->get(key);
    }
    else if (this->type == JSONValue::Type::ARRAY)
    {
        JSONValue value;
        int index = 0;
        do
        {
            value = this->array->get(index).get(key);
            index++;
        } while (!value.isNull() && index < this->array->length());
        return value;
    }
    else if (this->type == JSONValue::Type::STRING)
    {
        return this->string;
    }
    else
    {
        return JSONValue();
    }
}

JSONValue JSONValue::get(int index)
{
    if (this->type == JSONValue::Type::ARRAY)
    {
        return this->array->get(index);
    }
    else
    {
        return JSONValue();
    }
}

bool JSONValue::isNull()
{
    return this->type == JSONValue::Type::NULL_VALUE;
}

bool JSONValue::operator==(JSONValue other)
{
    if (this->type == JSONValue::Type::STRING && other.type == JSONValue::Type::STRING)
    {
        return this->string == other.string;
    }
    if (this->type == JSONValue::Type::ARRAY && other.type == JSONValue::Type::ARRAY)
    {
        return this->array == other.array;
    }
    if (this->type == JSONValue::Type::OBJECT && other.type == JSONValue::Type::OBJECT)
    {
        return this->object == other.object;
    }
    return false;
}