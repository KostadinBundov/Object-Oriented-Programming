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
	_capacity = newCapacity;
	char* newStr = new char[newCapacity];

	std::strcpy(newStr, _data);
	delete[] _data;
	_data = newStr;
}

MyString::MyString(size_t size)
{
	_size = 0;
	_capacity = dataToAllocByStringLen(size);
	_data = new char[_capacity] {'\0'};
}

void MyString::copyFrom(const MyString& other)
{
	_size = other._size;
	_capacity = other._capacity;
	_data = new char[_capacity];
	std::strcpy(_data, other._data);
}

void MyString::moveFrom(MyString&& other)
{
	_size = other._size;
	other._size = 0;

	_capacity = other._capacity;
	other._capacity = 0;

	_data = other._data;
	other._data = nullptr;
}

void MyString::free()
{
	delete[] _data;
	_size = 0;
	_capacity = 0;
}

MyString::MyString() : MyString("") {}

MyString::MyString(const char* str)
{
	_size = std::strlen(str);
	_capacity = dataToAllocByStringLen(_size);

	_data = new char[_capacity];
	std::strcpy(_data, str);
}

MyString::MyString(const MyString& other)
{
	copyFrom(other);
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

MyString::MyString(MyString&& other)
{
	moveFrom(std::move(other));
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

size_t MyString::length() const
{
	return _size;
}

const char* MyString::c_str() const
{
	return _data;
}

size_t MyString::capacity() const
{
	return _capacity - 1;
}

char MyString::operator[](unsigned index) const
{
	return _data[index];
}

char& MyString::operator[](unsigned index)
{
	return _data[index];
}

MyString& MyString::operator+=(const MyString& other)
{
	unsigned totalSize = _size + other._size;

	if (totalSize + 1 > _capacity)
	{
		resize(dataToAllocByStringLen(totalSize));
	}

	std::strcat(_data, other._data);
	_size = totalSize;

	return *this;
}

std::istream& operator>>(std::istream& is, MyString& str)
{
	char buff[1024];
	is >> buff;
	size_t buffSize = std::strlen(buff);

	if (buffSize + 1 > str._capacity)
	{
		str.resize(dataToAllocByStringLen(buffSize));
	}

	str._size = buffSize;
	std::strcpy(str._data, buff);
	return is;
}

std::ostream& operator<<(std::ostream& os, const MyString& str)
{
	return os << str._data;
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