#pragma once
#include "ExtremalPartialFunction.h"

class MaxPartialFunction : public ExtremalPartialFunction
{
public:
	MaxPartialFunction(const Container& container);
	int32_t operator()(int32_t x) const override;
	PartialFunction* clone() const override;
};