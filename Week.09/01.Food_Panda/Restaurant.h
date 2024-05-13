#pragma once
#include "ProductsList.h"
#include "Order.h"

class Restaurant
{
private:
	char name[25] = "";
	ProductsList products;

public:
	Restaurant() = default;
	Restaurant(const char* name, const ProductsList& productslist);

	void addProduct(const char* product);
	int getOrder(const Order& order);

	const char* getName() const;
};