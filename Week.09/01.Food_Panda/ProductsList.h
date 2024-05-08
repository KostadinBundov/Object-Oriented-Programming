#pragma once
#include <iostream>
#pragma warning (disable:4996)

class ProductsList
{
private:
	char** data = nullptr;
	size_t size = 0;
	size_t capacity = 0;

	void copyFrom(const ProductsList& other);
	void moveFrom(ProductsList&& other);
	void free();

	void resize(size_t newCapacity);

	int findFirstFreeIndex() const;

public:
	ProductsList() = default;
	ProductsList(const char** data, size_t size);
	ProductsList(const ProductsList& other);
	ProductsList(ProductsList&& other);

	ProductsList& operator=(const ProductsList& other);
	ProductsList& operator=(ProductsList&& other);

	~ProductsList();

	void addProduct(const char* str);
	void removeProducts(const ProductsList& list);

	size_t getProductsCount() const;

	bool containsProduct(const char* product) const;

	const char* operator[](size_t index) const;
};