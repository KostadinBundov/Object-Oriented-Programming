#include "DefinedOutOfRange.h"

DefinedOutOfRange::DefinedOutOfRange(const int32_t* data, size_t size)
{
	for (int i = 0; i < size; i++)
	{
		arguments.push_back(data[i]);
	}
}

Pair<bool, int32_t> DefinedOutOfRange::operator()(int32_t x) const
{
	int index = getIndexOfElement(arguments, x);

	if (index == -1)
	{
		return Pair<bool, int32_t>(1, x);
	}

	return Pair<bool, int32_t>(0, arguments[index]);
}

bool DefinedOutOfRange::isDefined(int32_t x) const
{
	if (getIndexOfElement(arguments, x) == -1)
	{
		return true;
	}

	return false;
}