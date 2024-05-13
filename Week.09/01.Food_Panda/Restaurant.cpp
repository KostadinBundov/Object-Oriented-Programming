#include "Restaurant.h"


static const unsigned TIME_TO_DELIVER_A_SINGLE_PRODUCT = 2;

Restaurant::Restaurant(const char* name, const ProductsList& productslist) : products(productslist)
{
	std::strcpy(this->name, name);
}

void Restaurant::addProduct(const char* product)
{
	products.addProduct(product);
}

int Restaurant::getOrder(const Order& order)
{
	ProductsList temp = order.getProducts();

	for (int i = 0; i < temp.getProductsCount(); i++)
	{
		if (!products.containsProduct(temp[i]))
		{
			throw std::invalid_argument("Restaurant doesn't have all products");
		}
	}

	products.removeProducts(temp);

	return temp.getProductsCount() * TIME_TO_DELIVER_A_SINGLE_PRODUCT;
}

const char* Restaurant::getName() const
{
	return name;
}