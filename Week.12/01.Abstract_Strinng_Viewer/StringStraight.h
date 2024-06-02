#pragma once
#include "StringViewer.h"

class StringStraight : public StringViewer
{
public:
	StringStraight(const char* str);
	StringStraight(const char* start, const char* end);
	StringStraight(const char* str, size_t count);

	int indexOf(const StringViewer& other) const override;
	void print() const override;
	StringViewer* substr(size_t pos, size_t count) const override;
};