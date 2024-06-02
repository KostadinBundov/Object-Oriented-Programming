#pragma once
#include <iostream>
#include "Container.h"
#include "PartialFunction.h"
#include "MyVector.hpp"

class ExtremalPartialFunction : public PartialFunction
{
protected:
	Container data;

public:
	ExtremalPartialFunction(const Container& other);
	bool isDefined(int32_t x) const override;
	virtual ~ExtremalPartialFunction() = default;
};