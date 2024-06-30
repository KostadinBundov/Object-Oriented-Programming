#include <iostream>
#include "MultiSet.h"

int main()
{
	{
		MultiSet a(7, 3);
		a.addNumber(2);
		a.addNumber(2);
		a.addNumber(3);
		a.addNumber(3);
		a.addNumber(3);
		a.addNumber(3);
		a.addNumber(3);
		a.addNumber(3);
		a.addNumber(3);
		a.addNumber(5);
		a.addNumber(5);
		a.printMultiSet();
		a.printMultiSetMemoryRepresentation();

		MultiSet b(9, 4);
		b.addNumber(2);
		b.addNumber(2);
		b.addNumber(2);
		b.addNumber(3);
		b.addNumber(4);
		b.addNumber(4);
		b.addNumber(5);
		b.addNumber(5);
		b.addNumber(9);
		b.printMultiSet();

		b.serialize("Demo.dat");

		MultiSet w;
		w.deserialize("Demo.dat");
		w.printMultiSet();

		MultiSet c = intersection(a, b);
		MultiSet d = difference(a, b);
		MultiSet k = complement(a);

		c.printMultiSet();
		d.printMultiSet();
		k.printMultiSet();
	}

	/*{
		MultiSet ms(0, 2);
		ms.addNumber(0);
		ms.printMultiSet();
		complement(ms).printMultiSet();
	}*/

	/*{

		MultiSet a(10, 3);
		a.addNumber(3);
		a.addNumber(3);
		a.addNumber(5);
		a.addNumber(6);
		a.addNumber(6);
		a.addNumber(6);
		a.addNumber(10);

		MultiSet b(15, 3);
		b.addNumber(3);
		b.addNumber(4);
		b.addNumber(4);
		b.addNumber(4);
		b.addNumber(5);
		b.addNumber(6);
		b.addNumber(8);
		b.addNumber(8);
		b.addNumber(9);

		a.printMultiSet();
		b.printMultiSet();
	}*/
}