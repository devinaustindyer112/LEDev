#include "Array.hpp"
#include "String.hpp"
#include "JSONValue.hpp"
#include "JSONObject.hpp"

template <typename T>
Array<T>::Array()
{
    this->elements = new T[0];
    this->size = 0;
}

template <typename T>
Array<T>::Array(Array<T> *other)
{
    this->elements = new T[other->size];
    this->size = other->size;

    for (int i = 0; i < this->size; i++)
    {
        this->elements[i] = other->elements[i];
    }
}

template <typename T>
Array<T>::Array(Array<T> &&other)
{
    this->elements = new T[other.size];
    this->size = other.size;

    for (int i = 0; i < this->size; i++)
    {
        this->elements[i] = other.elements[i];
    }
}

template <typename T>
Array<T>::Array(const Array<T> &other)
{
    this->elements = new T[other.size];
    this->size = other.size;

    for (int i = 0; i < this->size; i++)
    {
        this->elements[i] = other.elements[i];
    }
}

template <typename T>
Array<T>::~Array()
{
    delete[] this->elements;
}

template <typename T>
int Array<T>::length()
{
    return this->size;
}

template <typename T>
void Array<T>::push(T element)
{
    T *newElements = new T[this->size + 1];

    for (int i = 0; i < this->size; i++)
    {
        newElements[i] = this->elements[i];
    }

    newElements[this->size] = element;

    delete[] this->elements;
    this->elements = newElements;
    this->size++;
}

template <typename T>
void Array<T>::push(T *element)
{
    T *newElements = new T[this->size + 1];

    for (int i = 0; i < this->size; i++)
    {
        newElements[i] = this->elements[i];
    }

    newElements[this->size] = *element;

    delete[] this->elements;
    this->elements = newElements;
    this->size++;
}

template <typename T>
T Array<T>::pop()
{
    T *newElements = new T[this->size - 1];

    for (int i = 0; i < this->size - 1; i++)
    {
        newElements[i] = this->elements[i];
    }

    T element = this->elements[this->size - 1];

    delete[] this->elements;
    this->elements = newElements;
    this->size--;

    return element;
}

template <typename T>
T Array<T>::get(int index)
{
    return this->elements[index];
}

template <typename T>
bool Array<T>::operator==(const Array<T> &other) const
{
    if (this == &other)
        return true;

    if (this->size != other.size)
        return false;

    for (int i = 0; i < this->size; i++)
    {
        if (!(this->elements[i] == other.elements[i]))
            return false;
    }

    return true;
}

template class Array<JFA::String>;
template class Array<JSONValue>;
template class Array<JSONObject>;