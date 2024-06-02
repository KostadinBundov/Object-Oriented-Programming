#pragma once
#include "MyString.h"

class StringViewer
{
protected:
	const char* start = nullptr;
	const char* end = nullptr;

public:
	StringViewer(const char* start, const char* end);
	StringViewer(const char* str);
	StringViewer(const char* str, size_t count);

	char operator[](size_t ind) const;

	size_t length() const;
	bool isEmpty() const;

	virtual void removeSuffix(size_t count);
	virtual void removePreffix(size_t count);

	virtual StringViewer* substr(size_t pos, size_t count) const = 0;
	virtual int indexOf(const StringViewer& other) const = 0;
	virtual void print() const = 0;

	virtual bool compare(const StringViewer& other) = 0;
	virtual bool comapreWithStraightString(const StringViewer& other) = 0;
	virtual bool compareWithReverseString(const StringViewer& other) = 0;
};