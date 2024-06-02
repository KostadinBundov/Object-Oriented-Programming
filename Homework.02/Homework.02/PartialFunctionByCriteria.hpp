#pragma once
#include "PartialFunction.h"
#include "Pair.hpp"
#include <iostream>

template<class T>
class PartialFunctionByCriteria : public PartialFunction
{
private:
	T function;

public:
	PartialFunctionByCriteria(const T& _function);
	int32_t operator()(int32_t x) const override;
	bool isDefined(int32_t x) const override;
	PartialFunction* clone() const override;
};

template<class T>
PartialFunctionByCriteria<T>::PartialFunctionByCriteria(const T& _function) : function(_function) { };

template<class T>
int32_t PartialFunctionByCriteria<T>::operator()(int32_t x) const
{
	if (!isDefined(x))
	{
		throw std::invalid_argument("Function isn't valid in this argument");
	}

	Pair<bool, int32_t> currentPair = function(x);
	return currentPair.getSecond();
}

template<class T>
inline bool PartialFunctionByCriteria<T>::isDefined(int32_t x) const
{
	Pair<bool, int32_t> currentPair = function(x);
	return currentPair.getFirst();
}

template<class T>
PartialFunction* PartialFunctionByCriteria<T>::clone() const
{
	return new PartialFunctionByCriteria(*this);
}