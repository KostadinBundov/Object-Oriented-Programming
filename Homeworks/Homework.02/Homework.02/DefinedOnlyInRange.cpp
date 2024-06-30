#include "DefinedOnlyInRange.h"

int DefinedOnlyInRange::getIndexOfArgument(int32_t x) const
{
	for (int i = 0; i < arguments.getSize(); i++)
	{
		if (arguments[i].getFirst() == x)
		{
			return i;
		}
	}

	return -1;
}

DefinedOnlyInRange::DefinedOnlyInRange(const int32_t* data, size_t size)
{
	for (int i = 0; i < size; i++)
	{
		arguments.pushBack(Pair<int32_t, int32_t>(data[i], data[i + size]));
		
	}
}

Pair<bool, int32_t> DefinedOnlyInRange::operator()(int32_t x) const
{
	int index = getIndexOfArgument(x);

	if (index == -1)
	{
		return Pair<bool, int32_t>(0, 0);
	}

	return Pair<bool, int32_t>(1, arguments[index].getSecond());
}

bool DefinedOnlyInRange::isDefined(int32_t x) const
{
	if (getIndexOfArgument(x) == -1)
	{
		return false;
	}

	return true;
}