#pragma once
#include "FunctionsFactory.h"

void addFunctionToContainer(int16_t n, std::ifstream& ifs, Container& functions)
{
	for (int i = 0; i < n; i++)
	{
		char buff[1024];
		char c;
		unsigned index = 0;

		while (ifs.read((char*)&c, sizeof(char)))
		{
			buff[index] = c;
			if (c == '\0')
			{
				break;
			}
			index++;
		}

		if (ifs.eof() && c != '\0')
		{
			break;
		}

		PartialFunction* temp = createFunction(buff);
		functions.pushBack(temp);
		delete temp;
	}
}

PartialFunction* createFunction(const char* mainFailName)
{
	std::ifstream ifs(mainFailName, std::ios::binary);

	if (!ifs.is_open())
	{
		throw std::runtime_error("Can't open file!");
	}

	int16_t n = 0;
	int16_t t = 0;

	ifs.read((char*)&n, sizeof(int16_t));
	ifs.read((char*)&t, sizeof(int16_t));

	int32_t* arr = nullptr;
	PartialFunction* result = nullptr;

	try
	{
		if (t == 0)
		{
			int32_t size = 2 * n;
			arr = new int32_t[size]{ 0 };
			ifs.read((char*)arr, sizeof(int32_t) * size);
			result = new PartialFunctionByCriteria<DefinedOnlyInRange>(DefinedOnlyInRange(arr, n));
		}
		else if (t == 1)
		{
			arr = new int32_t[n]{ 0 };
			ifs.read((char*)arr, sizeof(arr));
			result = new PartialFunctionByCriteria<DefinedOutOfRange>(DefinedOutOfRange(arr, n));
		}
		else if (t == 2)
		{
			arr = new int32_t[n]{ 0 };
			ifs.read((char*)arr, sizeof(int32_t) * n);
			result = new PartialFunctionByCriteria<BoolFunction>(BoolFunction(arr, n));
		}
		else if (t == 3)
		{
			Container functions;
			addFunctionToContainer(n, ifs, functions);
			result = new MaxPartialFunction(functions);
		}
		else if (t == 4)
		{
			Container functions;
			addFunctionToContainer(n, ifs, functions);
			result = new MinPartialFunction(functions);
		}
	}
	catch (const std::exception&)
	{
		delete[] arr;
		throw;
	}

	delete[] arr;
	return result;
}