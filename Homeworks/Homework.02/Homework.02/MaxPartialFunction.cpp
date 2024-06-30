#include "MaxPartialFunction.h"

MaxPartialFunction::MaxPartialFunction(const Container& container) : ExtremalPartialFunction(container) { }

int32_t MaxPartialFunction::operator()(int32_t x) const
{
	if (!isDefined(x))
	{
		throw std::invalid_argument("Function isn't defined in x");
	}

	int32_t max = INT32_MIN;

	for (int i = 0; i < data.getSize(); i++)
	{
		int32_t currentValue = data[i]->operator()(x);

		if(max <= currentValue)
		{
			max = currentValue;
		}
	}

	return max;
}

PartialFunction* MaxPartialFunction::clone() const
{
	return new MaxPartialFunction(*this);
}