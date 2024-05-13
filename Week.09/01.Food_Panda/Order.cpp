#include "Order.h"


Order::Order(const char* restaurantName, const ProductsList& productsList) : products(productsList)
{
	std::strcpy(this->restaurantName, restaurantName);
}

size_t Order::getProductsCount() const
{
	return products.getProductsCount();
}

const ProductsList& Order::getProducts() const
{
	return products;
}

const char* Order::getRestaurantName() const
{
	return restaurantName;
}