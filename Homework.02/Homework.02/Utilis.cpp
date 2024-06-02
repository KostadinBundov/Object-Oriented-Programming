#include "Utilis.h"

int getIndexOfElement(const Vector<int32_t>& arr, int32_t x)
{
	for (int i = 0; i < arr.getSize(); i++)
	{
		if (arr[i] == x)
		{
			return i;
		}
	}

	return -1;
}