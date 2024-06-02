#pragma once
#include "ExtremalPartialFunction.h"

class MinPartialFunction : public ExtremalPartialFunction
{
public:
	MinPartialFunction(const Container& other);
	int32_t operator()(int32_t x) const override;
	PartialFunction* clone() const override;
};