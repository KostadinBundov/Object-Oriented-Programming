#pragma once
#include <fstream>
#include <iostream>

class MyString
{
private:
	char* _data = nullptr;
	size_t _size = 0;
	size_t _capacity = 8;

	explicit MyString(size_t size);
	void resize(size_t newCapacity);

	void copyFrom(const MyString& other);
	void moveFrom(MyString&& other);
	void free();

public:
	MyString();
	MyString(const char* str);

	MyString(const MyString& other);
	MyString& operator=(const MyString& other);

	MyString(MyString&& other);
	MyString& operator=(MyString&& other);

	~MyString();

	size_t length() const;
	const char* c_str() const;
	size_t capacity() const;

	char operator[](unsigned index) const;
	char& operator[](unsigned index);

	MyString& operator+=(const MyString& other);

	friend MyString operator+(const MyString& lhs, const MyString& rhs);
	friend std::istream& operator>>(std::istream& is, MyString& str);
	friend std::ostream& operator<<(std::ostream& os, const MyString& str);

	friend std::ostream& operator<<(std::ostream& os, const MyString& obj);
	friend std::istream& operator>>(std::istream& is, MyString& ref);
};


bool operator==(const MyString& lhs, const MyString& rhs);
bool operator!=(const MyString& lhs, const MyString& rhs);
bool operator>(const MyString& lhs, const MyString& rhs);
bool operator>=(const MyString& lhs, const MyString& rhs);
bool operator<(const MyString& lhs, const MyString& rhs);
bool operator<=(const MyString& lhs, const MyString& rhs);