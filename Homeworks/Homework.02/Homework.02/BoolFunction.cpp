#include "BoolFunction.h"

BoolFunction::BoolFunction(const int32_t* data, size_t size)
{
	for (int i = 0; i < size; i++)
	{
		arguments.push_back(data[i]);
	}
}

Pair<bool, int32_t> BoolFunction::operator()(int32_t x) const
{
	int index = getIndexOfElement(arguments, x);

	if (index == -1)
	{
		return Pair<bool, int32_t>(1, 0);
	}

	return Pair<bool, int32_t>(1, 1);
}

bool BoolFunction::isDefined(int32_t x) const
{
	return true;
}