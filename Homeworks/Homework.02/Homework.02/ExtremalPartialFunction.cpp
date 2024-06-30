#include "ExtremalPartialFunction.h"

ExtremalPartialFunction::ExtremalPartialFunction(const Container& other) : data(other) {}

bool ExtremalPartialFunction::isDefined(int32_t x) const
{
	for (int i = 0; i < data.getSize(); i++)
	{
		if (!data[i]->isDefined(x))
		{
			return false;
		}
	}

	return true;
}