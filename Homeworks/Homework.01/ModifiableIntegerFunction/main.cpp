#include <iostream>
#include "ModifiableIntegerFunction.h";

short f(short x)
{
	return x;
}

int main()
{
	{
		ModifiableIntegerFunction g(f);

		std::cout << g.checkIsInjective() << std::endl;
		std::cout << g.checkIsBijective() << std::endl;

		g.serializeInFile("data.dat");

		ModifiableIntegerFunction l;
		l.deserializeFromFile("data.dat");

		std::cout << l.checkIsInjective() << std::endl;
		std::cout << l.checkIsBijective() << std::endl;

		ModifiableIntegerFunction k(f);

		std::cout << (l || k) << std::endl;

		l.printPointsInInterval(0, 0, 20, 20);
	}

	/*{
		ModifiableIntegerFunction g(f);
		ModifiableIntegerFunction k(f);

		std::cout << (g < k) << std::endl;
		std::cout << (g <= k) << std::endl;

		std::cout << (g > k) << std::endl;
		std::cout << (g >= k) << std::endl;

		std::cout << (g == k) << std::endl;
		std::cout << (g != k) << std::endl;
	}*/

	/*{
		ModifiableIntegerFunction g(f);
		ModifiableIntegerFunction k(g);
		ModifiableIntegerFunction n(g);

		ModifiableIntegerFunction compose = (g(k(n)));

		compose.printPointsInInterval(-10, 0, 10 , 20);
	}*/
}