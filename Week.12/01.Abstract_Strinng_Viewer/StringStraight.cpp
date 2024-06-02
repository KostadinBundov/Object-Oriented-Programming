#include "StringStraight.h"

StringStraight::StringStraight(const char* str) : StringViewer(str) { }

StringStraight::StringStraight(const char* start, const char* end) : StringViewer(start, end) { }

StringStraight::StringStraight(const char* str, size_t count) : StringViewer(str, count) { }

int StringStraight::indexOf(const StringViewer& other) const
{
	if (other.length() > length() || length() == 0)
	{
		return -1;
	}

	for (int i = 0; i < length() - other.length(); i++)
	{
		if (std::strncmp(start + i, other.start, other.length()) == 0)
		{

		}
	}
}

void StringStraight::print() const // abdsabc abc 
{
	const char* temp = start;

	while (&temp != &end)
	{
		std::cout << *temp;
		temp += 1;
	}

	std::cout << std::endl;
}

StringViewer* StringStraight::substr(size_t pos, size_t count) const
{
	if (start + pos + length() > end)
	{
		throw std::length_error("Error, Substr out of range!");
	}

	return &StringStraight(start + pos, start + pos + length());
}

