#include "MyString.h"
#pragma warning (disable : 4996)

static unsigned roundToPowerOfTwo(unsigned v) //static! -> will be discused in the next lecture
{
    v--;
    v |= v >> 1;
    v |= v >> 2;
    v |= v >> 4;
    v |= v >> 8;
    v |= v >> 16;
    v++;
    return v;
}

static unsigned dataToAllocByStringLen(unsigned stringLength)
{
    return std::max(roundToPowerOfTwo(stringLength + 1), 16u);
}

void MyString::resize(size_t newCapacity)
{
    char* result = new char[newCapacity];
    std::strcpy(result, data);
    delete[] data;
    data = result;
    capacity = newCapacity;
}

MyString::MyString(size_t size)
{
    this->size = size;
    capacity = dataToAllocByStringLen(size);
    data = new char[capacity];
}

void MyString::copyFrom(const MyString& other)
{
    data = new char[std::strlen(other.data) + 1];
    std::strcpy(data, other.data);

    capacity = other.capacity;
    size = other.size;
}

void MyString::moveFrom(MyString&& other)
{
    data = other.data;
    other.data = nullptr;

    size = other.size;
    other.size = 0;

    capacity = other.capacity;
    other.capacity = 0;
}

void MyString::free()
{
    delete[] data;
    size = 0;
    capacity = 0;
}

MyString::MyString() : MyString("") {}

MyString::MyString(const char* str)
{
    size = std::strlen(str);
    capacity = dataToAllocByStringLen(size);
    data = new char[capacity];
    std::strcpy(data, str);
}

MyString::MyString(const MyString& other)
{
    copyFrom(other);
}

MyString::MyString(MyString&& other)
{
    moveFrom(std::move(other));
}

MyString& MyString::operator=(const MyString& other)
{
    if (this != &other)
    {
        free();
        copyFrom(other);
    }
    
    return *this;
}

MyString& MyString::operator=(MyString&& other)
{
    if (this != &other)
    {
        free();
        moveFrom(std::move(other));
    }

    return *this;
}

MyString::~MyString()
{
    free();
}

const char* MyString::c_str() const
{
    return data;
}

size_t MyString::length() const
{
    return size;
}

size_t MyString::getCapacity() const
{
    return capacity - 1;
}

const char& MyString::operator[](size_t index) const
{
    return data[index];
}

char& MyString::operator[](size_t index)
{
    return data[index];
}

MyString& MyString::operator+=(const MyString& other)
{
    size_t totalLength = size + other.size;

    if (totalLength + 1 >= capacity)
    {
        resize(dataToAllocByStringLen(capacity));
    }

    std::strncat(data, other.data, other.size);
    size = totalLength;

    return *this;
}

std::ostream& operator<<(std::ostream& os, const MyString& myString)
{
    return os << myString.data;
}

std::istream& operator>>(std::istream& is, MyString& myString)
{
    char buff[1024];

    is >> buff;
    size_t buffLength = std::strlen(buff);

    if (buffLength + 1 >= myString.capacity)
    {
        myString.resize(dataToAllocByStringLen(buffLength));
    }

    std::strcpy(myString.data, buff);
    myString.size = buffLength;

    return is;
}

MyString operator+(const MyString& lhs, const MyString& rhs)
{
    MyString result(lhs.length() + rhs.length());
    result += lhs;
    result += rhs;
    return result;
}

bool operator==(const MyString& lhs, const MyString& rhs)
{
    return std::strcmp(lhs.c_str(), rhs.c_str()) == 0;
}

bool operator!=(const MyString& lhs, const MyString& rhs)
{
    return std::strcmp(lhs.c_str(), rhs.c_str()) != 0;
}

bool operator<(const MyString& lhs, const MyString& rhs)
{
    return std::strcmp(lhs.c_str(), rhs.c_str()) < 0;
}

bool operator<=(const MyString& lhs, const MyString& rhs)
{
    return std::strcmp(lhs.c_str(), rhs.c_str()) <= 0;
}

bool operator>(const MyString& lhs, const MyString& rhs)
{
    return std::strcmp(lhs.c_str(), rhs.c_str()) > 0;
}

bool operator>=(const MyString& lhs, const MyString& rhs)
{
    return std::strcmp(lhs.c_str(), rhs.c_str()) >= 0;
}