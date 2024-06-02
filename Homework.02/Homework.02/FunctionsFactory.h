#pragma once

#include "BoolFunction.h"
#include "DefinedOutOfRange.h"
#include "DefinedOnlyInRange.h"
#include "MaxPartialFunction.h"
#include "MinPartialFunction.h"
#include "PartialFunctionByCriteria.hpp"

#include "PartialFunction.h"
#include "MyVector.hpp"
#include <fstream>
#include "MyString.h"

PartialFunction* createFunction(const char* mainFailName);
void addFunctionToContainer(int16_t n, std::ifstream& ifs, Container& functions);