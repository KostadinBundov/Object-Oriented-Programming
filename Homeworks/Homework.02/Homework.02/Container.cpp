#include "Container.h"

void Container::copyFrom(const Container& other)
{
	data = new PartialFunction * [other.capacity] {nullptr};

	for (int i = 0; i < other.capacity; i++)
	{
		if (other.data[i] != nullptr)
		{
			data[i] = other.data[i]->clone();
		}
	}

	capacity = other.capacity;
	size = other.size;
}

void Container::free()
{
	for (int i = 0; i < capacity; i++)
	{
		delete data[i];
	}

	delete[] data;
}

void Container::moveFrom(Container&& other)
{
	data = other.data;
	capacity = other.capacity;
	size = other.size;

	other.data = nullptr;
	other.capacity = 0;
	other.size = 0;
}

void Container::resize(size_t newCapacity)
{
	PartialFunction** temp = new PartialFunction * [newCapacity] {nullptr};

	for (size_t i = 0; i < capacity; i++)
	{
		temp[i] = data[i];
	}

	delete[] data;
	data = temp;
	capacity = newCapacity;
}

Container::Container()
{
	capacity = 8;
	size = 0;
	data = new PartialFunction * [capacity] {nullptr};
}

Container::Container(const Container& other)
{
	copyFrom(other);
}

Container::Container(Container&& other)
{
	moveFrom(std::move(other));
}

Container& Container::operator=(Container& other)
{
	if (this != &other)
	{
		free();
		copyFrom(other);
	}

	return *this;
}

Container& Container::operator=(Container&& other)
{
	if (this != &other)
	{
		free();
		moveFrom(std::move(other));
	}

	return *this;
}

Container::~Container()
{
	free();
}

const PartialFunction* Container::operator[](size_t index) const
{
	if (index >= size)
	{
		throw std::invalid_argument("Index out of range exception!");
	}

	return data[index];
}

size_t Container::getSize() const
{
	return size;
}

void Container::pushBack(PartialFunction* other)
{
	if (size >= capacity)
	{
		resize(capacity * 2);
	}

	data[size] = other->clone();
	size++;
}