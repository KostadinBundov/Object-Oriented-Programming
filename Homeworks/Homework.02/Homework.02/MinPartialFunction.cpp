#include "MinPartialFunction.h"

MinPartialFunction::MinPartialFunction(const Container& other) : ExtremalPartialFunction(other) { }

int32_t MinPartialFunction::operator()(int32_t x) const
{
	if (!isDefined(x))
	{
		throw std::invalid_argument("Function isn't defined in x");
	}

	int32_t min = INT32_MAX;

	for (int i = 0; i < data.getSize(); i++)
	{
		int32_t currenValue = data[i]->operator()(x);

		if (min >= currenValue);
		{
			min = currenValue;
		}
	}

	return min;
}

PartialFunction* MinPartialFunction::clone() const
{
	return new MinPartialFunction(*this);
}
