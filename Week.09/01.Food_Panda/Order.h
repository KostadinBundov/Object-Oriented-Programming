#pragma once
#include "ProductsList.h"

class Order
{
private:
	char restaurantName[25];
	ProductsList products;

public:
	Order(const char* restaurantName, const ProductsList& productsList);
	size_t getProductsCount() const;

	const ProductsList& getProducts() const;
	const char* getRestaurantName() const;
};