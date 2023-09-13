#include "../Utilities/Utilities.hpp"
#include "String.hpp"
#include <iostream>

JFA::String::String()
{
    this->str = nullptr;
}

JFA::String::String(const char *str)
{
    char *newStr = new char[size(str)];
    for (int i = 0; i < size(str); i++)
    {
        newStr[i] = str[i];
    }
    this->str = newStr;
}

// Copy constructor (Deep copy)
JFA::String::String(const JFA::String &other)
{
    if (other.str != nullptr)
    {
        this->str = new char[other.length()];
        for (int i = 0; i < other.length(); i++)
        {
            this->str[i] = other[i];
        }
    }
    else
    {
        this->str = nullptr;
    }
}

// Deep copy assignment operator
JFA::String &JFA::String::operator=(const JFA::String &other)
{
    if (this == &other)
    {
        return *this; // Self-assignment, nothing to do
    }

    // Deallocate existing memory
    delete[] this->str;

    if (other.str != nullptr)
    {
        this->str = new char[other.length()];
        for (int i = 0; i < other.length(); i++)
        {
            this->str[i] = other[i];
        }
    }
    else
    {
        this->str = nullptr;
    }

    return *this;
}

// Destructor
JFA::String::~String()
{
    delete[] this->str;
}

JFA::String JFA::String::substring(int start, int end)
{
    int length = end - start;

    char sub[length];
    for (int i = start; i < end; i++)
    {
        sub[i] = this->str[i + start];
    }

    return String(sub);
}

int JFA::String::length()
{
    return size(this->str);
}

int JFA::String::length() const
{
    return size(this->str);
}

JFA::String JFA::String::operator+(JFA::String string)
{
    int len1 = size(this->str);
    int len2 = string.length();

    char *str = new char[len1 + len2];

    for (int i = 0; i < len1; i++)
    {
        str[i] = this->str[i];
    }
    for (int i = 0; i < len2; i++)
    {
        str[i + len1] = string[i];
    }

    return String(str);
}

JFA::String JFA::String::operator+(char character)
{
    int len1 = size(this->str);
    char *str = new char[len1 + 1];

    for (int i = 0; i < len1; i++)
    {
        str[i] = this->str[i];
    }

    str[len1] = character;
    return String(str);
}

char JFA::String::operator[](int index) const
{
    return this->str[index];
}

char JFA::String::operator[](int index)
{
    return this->str[index];
}

char JFA::String::operator==(const char *str)
{
    for (int i = 0; i < this->length(); i++)
    {
        if (this->str[i] != str[i])
        {
            return false;
        }
    }
    return true;
}

char JFA::String::operator==(JFA::String str)
{
    for (int i = 0; i < this->length(); i++)
    {
        if (this->str[i] != str[i])
        {
            return false;
        }
    }
    return true;
}

bool JFA::String::equals(JFA::String str)
{
    if (this->length() != str.length())
        return false;

    for (int i = 0; i < str.length(); i++)
    {
        if (this->str[i] != str[i])
        {
            return false;
        }
    }
    return true;
}

const char *JFA::String::toCharArray()
{
    const char *str = this->str;
    return str;
}

int JFA::String::indexOf(const char *search)
{
    for (int i = 0; i < this->length(); i++)
    {
        int index = 0;
        while (this->str[i] == search[index])
        {
            if (index == size(search) - 1)
            {
                return i - index;
            }
            index++;
            i++;
        }
    }
    return -1;
}

JFA::String JFA::String::replace(const char *search, const char *replace)
{
    int index = this->indexOf(search);
    int len = this->length();
    int lenSearch = size(search);
    int lenReplace = size(replace);

    char *str = new char[len + lenReplace - lenSearch];

    for (int i = 0; i < index; i++)
    {
        str[i] = this->str[i];
    }
    for (int i = 0; i < lenReplace; i++)
    {
        str[i + index] = replace[i];
    }
    for (int i = index + lenSearch; i < len; i++)
    {
        str[i + lenReplace - lenSearch] = this->str[i];
    }

    return JFA::String(str);
}

JFA::String JFA::String::replaceAll(const char *search, const char *replace)
{
    JFA::String str = JFA::String(this->str);
    while (str.indexOf(search) != -1)
    {
        str = str.replace(search, replace);
    }
    return str;
}

void JFA::String::print()
{
    for (int i = 0; i < this->length(); i++)
    {
        std::cout << this->str[i];
    }
}