#pragma once
#include <iostream>

class MyString
{
private:
	char* data;
	size_t size;
	size_t capacity;

	void resize(size_t newCapacity);
	MyString(size_t size);

	void copyFrom(const MyString& other);
	void moveFrom(MyString&& other);
	void free();

public:
	MyString();
	MyString(const char* str);
	MyString(const MyString& other);
	MyString(MyString&& other);

	MyString& operator=(const MyString& other);
	MyString& operator=(MyString&& other);

	~MyString();

	const char* c_str() const;
	size_t length() const;
	size_t getCapacity() const;

	const char& operator[](size_t index) const;
	char& operator[](size_t index);

	MyString& operator+=(const MyString& other);

	friend std::ostream& operator<<(std::ostream& os, const MyString& myString);
	friend std::istream& operator>>(std::istream& is, MyString& myString);
	friend MyString operator+(const MyString& lhs, const MyString& rhs);
};

bool operator==(const MyString& lhs, const MyString& rhs);
bool operator!=(const MyString& lhs, const MyString& rhs);
bool operator<(const MyString& lhs, const MyString& rhs);
bool operator<=(const MyString& lhs, const MyString& rhs);
bool operator>(const MyString& lhs, const MyString& rhs);
bool operator>=(const MyString& lhs, const MyString& rhs);