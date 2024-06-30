#include <fstream>
#include "PartialFunction.h"
#include "FunctionsFactory.h"

void printValues(const PartialFunction*& func, int32_t start, int32_t end)
{
	for (int i = start; i <= end; i++)
	{
		try
		{
			std::cout << "f(" << i << ") = " << func->operator()(i) << std::endl;
		}
		catch (const std::invalid_argument&)
		{
			continue;
		}
		catch (const std::exception& ex)
		{
			std::cout << ex.what();
			return;
		}
	}
}

void printWhenUserWant(const PartialFunction*& func)
{
	std::cout << "Enter 'n' for showing next defined value or 'e' for exit:" << std::endl;

	// work significcantly slower than it must be, so for the test of the exercise can be change the current argument to start from 0 just for the example
	int32_t currentArgument = INT32_MIN;
	char wantSymbol = 'n';
	char endSymbol = 'e';

	char currentSymbol;

	while (true)
	{
		std::cin >> currentSymbol;

		if (currentSymbol == endSymbol)
		{
			break;
		}

		if (currentSymbol == wantSymbol)
		{
			while (true)
			{
				if (currentArgument == INT32_MAX)
				{
					std::cout << "No more defined arguments to show!" << std::endl;
					return;
				}

				try
				{
					std::cout << "f(" << currentArgument << ") = " << func->operator()(currentArgument) << std::endl;
					currentArgument++;
					break;
				}
				catch (const std::invalid_argument&)
				{
					currentArgument++;
					continue;
				}
				catch (const std::exception& ex)
				{
					std::cout << "Error: " << ex.what() << std::endl;
					return;
				}
			}
		}
	}
}

//use literature and code:
//https://github.com/GeorgiTerziev02/Object-oriented_programming_FMI/blob/main/Sem.%2013/Solutions/polymorphic/MyVector.hpp
//https://github.com/Angeld55/Object-oriented_programming_FMI/tree/master/Week%2009/MyString%20(with%20move)

int main()
{
	while(true)
	{
		const PartialFunction* myFunc = createFunction("func.dat");
		delete myFunc;
	}


	//const PartialFunction* myFunc = nullptr;
	//try
	//{
	//	// you can also try working with funcMin.dat where we find minFunction instead of a max
	//	myFunc = createFunction("func.dat");
	//}
	//catch (const std::invalid_argument& ex)
	//{
	//	std::cout << "InvalidArgument!";
	//	return 0;
	//}
	//catch (const std::overflow_error& ex)
	//{
	//	std::cout << "Overflow error!";
	//	return 0;
	//}
	//catch (const std::exception& ex)
	//{
	//	std::cout << "Error!";
	//	return 0;
	//}
	//catch (...)
	//{
	//	std::cout << "Unknown error!!!!";
	//	return 0;
	//}

	//std::cout << "Enter work mode:" << std::endl;
	//std::cout << "Choose between 1 and 2:" << std::endl;
	//int32_t workMode;
	//std::cin >> workMode;

	//if (workMode == 1)
	//{
	//	std::cout << "Enter start and end separated by space:" << std::endl;
	//	int32_t start;
	//	int32_t end;
	//	std::cin >> start >> end;

	//	printValues(myFunc, start, end);
	//}
	//else if (workMode == 2)
	//{
	//	printWhenUserWant(myFunc);
	//}

	//delete myFunc;
}