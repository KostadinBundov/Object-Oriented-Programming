#pragma once
#include <iostream>
#include "Pair.hpp"
#include "Utilis.h"
#include "MyVector.hpp";

class BoolFunction
{
private:
	Vector<int32_t> arguments;

public:
	BoolFunction(const int32_t* data, size_t size);
	Pair<bool, int32_t> operator()(int32_t) const;
	bool isDefined(int32_t) const;
};