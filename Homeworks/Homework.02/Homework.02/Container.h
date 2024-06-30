#pragma once
#include "PartialFunction.h"

class Container
{
private:
	PartialFunction** data;

	size_t size = 0;
	size_t capacity = 0;

	void copyFrom(const Container& other);
	void free();
	void moveFrom(Container&& other);

	void resize(size_t newCapacity);

public:
	Container();
	Container(const Container& other);
	Container(Container&& other);

	Container& operator=(Container& other);
	Container& operator= (Container && other);

	~Container();

	const PartialFunction* operator[](size_t index) const;
	size_t getSize() const;

	void pushBack(PartialFunction* other);
};