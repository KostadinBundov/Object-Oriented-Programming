#pragma once
#include <iostream>
#include "pair.hpp"
#include "MyVector.hpp";

class DefinedOnlyInRange
{
private:
	int getIndexOfArgument(int32_t x) const;
	Vector<Pair<int32_t, int32_t>> arguments;

public:
	DefinedOnlyInRange(const int32_t* data, size_t size);
	Pair<bool, int32_t> operator()(int32_t) const;
	bool isDefined(int32_t) const;
};