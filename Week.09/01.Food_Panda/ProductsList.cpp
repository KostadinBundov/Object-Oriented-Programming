#include "ProductsList.h"



static unsigned roundToPowerOfTwo(unsigned v)
{
	v--;
	v |= v >> 1;
	v |= v >> 2;
	v |= v >> 4;
	v |= v >> 8;
	v |= v >> 16;
	v++;
	return v;
}

static unsigned dataToAllocByLen(unsigned stringLength)
{
	return std::max(roundToPowerOfTwo(stringLength), 16u);
}

// we accept that data is nullptr
void ProductsList::copyFrom(const ProductsList& other)
{
	data = new char* [other.capacity] {nullptr};

	for (int i = 0; i < other.capacity; i++)
	{
		if (other.data[i] != nullptr)
		{
			data[i] = new char[std::strlen(other.data[i]) + 1];
			std::strcpy(data[i], other.data[i]);
		}
	}

	size = other.size;
	capacity = other.capacity;
}

void ProductsList::moveFrom(ProductsList&& other)
{
	data = other.data;
	other.data = nullptr;

	size = other.size;
	other.size = 0;

	capacity = other.capacity;
	other.capacity = 0;
}

void ProductsList::free()
{
	for (int i = 0; i < capacity; i++)
	{
		delete[] data[i];
	}

	delete[] data;
}

void ProductsList::resize(size_t newCapacity)
{
	char** newData = new char* [newCapacity] {nullptr};

	for (int i = 0; i < capacity; i++)
	{
		newData[i] = data[i];
	}

	capacity = newCapacity;
	delete[] data;
	data = newData;
}

int ProductsList::findFirstFreeIndex() const
{
	for (int i = 0; i < capacity; i++)
	{
		if (!data[i])
		{
			return i;
		}
	}

	return -1;
}

ProductsList::ProductsList(const char** data, size_t size)
{
	capacity = dataToAllocByLen(size);
	this->data = new char* [capacity] {nullptr};

	for (int i = 0; i < size; i++)
	{
		if (data[i] == nullptr)
		{
			continue;
		}

		this->data[i] = new char[std::strlen(data[i]) + 1];
		std::strcpy(this->data[i], data[i]);
	}

	this->size = size;
}

ProductsList::ProductsList(const ProductsList& other)
{
	copyFrom(other);
}

ProductsList::ProductsList(ProductsList&& other)
{
	moveFrom(std::move(other));
}

ProductsList& ProductsList::operator=(const ProductsList& other)
{
	if (this != &other)
	{
		free();
		copyFrom(other);
	}

	return *this;
}

ProductsList& ProductsList::operator=(ProductsList&& other)
{
	if (this != &other)
	{
		free();
		moveFrom(std::move(other));
	}

	return *this;
}

ProductsList::~ProductsList()
{
	free();
}

void ProductsList::addProduct(const char* str)
{
	if (size >= capacity)
	{
		resize(dataToAllocByLen(std::strlen(str)));
	}

	int index = findFirstFreeIndex();

	if (index == -1)
	{
		return;
	}

	data[index] = new char[std::strlen(str) + 1];
	std::strcpy(data[index], str);

	size++;
}

void ProductsList::removeProducts(const ProductsList& list)
{
	size_t end = std::min(list.capacity, capacity);

	for (int i = 0; i < end; i++)
	{
		if (containsProduct(list[i]))
		{
			delete[] data[i];
			data[i] = nullptr;
		}
	}
}

size_t ProductsList::getProductsCount() const
{
	return size;
}

bool ProductsList::containsProduct(const char* product) const
{
	for (int i = 0; i < capacity; i++)
	{
		if (data[i] != nullptr && product != nullptr)
		{
			if (std::strcmp(product, data[i]) == 0)
			{
				return true;
			}
		}
	}

	return false;
}

const char* ProductsList::operator[](size_t index) const
{
	return data[index];
}
