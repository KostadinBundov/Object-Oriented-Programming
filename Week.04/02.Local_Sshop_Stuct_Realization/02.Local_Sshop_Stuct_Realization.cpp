#include <iostream>
#include <fstream>

#pragma warning( disable : 4996)

namespace GlobalConstants {
	constexpr size_t SHOP_NAME_MAX_SIZE = 30;
	constexpr size_t ADDRESS_NAME_MAX_SIZE = 50;
	constexpr size_t PRODUCTS_LIST_MAX_SIZE = 100;
}

struct Product {
	int barcode = 0;
	char* name = nullptr;
	unsigned quantity = 0;
	double price = 0;

	void print() const
	{
		std::cout << this->barcode << " " << this->name << " " << this->quantity << " " << price << std::endl;
	}

	void increaseProductQuantity(const unsigned quantity)
	{
		this->quantity += quantity;
	}

	Product() = default;

	Product(uint8_t barcode, const char* name, const unsigned quantity, const double price)
	{
		this->barcode = barcode;
		this->name = new char[strlen(name) + 1];
		strcpy(this->name, name);
		this->quantity = quantity;
		this->price = price;
	}

	~Product()
	{
		delete[] name;
	}
};

struct Shop {
	char name[GlobalConstants::ADDRESS_NAME_MAX_SIZE] = "unknown";
	char address[GlobalConstants::ADDRESS_NAME_MAX_SIZE] = "unknown";
	Product products[GlobalConstants::PRODUCTS_LIST_MAX_SIZE];
	double income = 0;
	unsigned productsCount = 0;

	Shop() = default;

	void print() const
	{
		std::cout << this->name << ":" << std::endl;
		std::cout << this->address << std::endl;
		
		for (int i = 0; i < productsCount; i++)
		{
			this->products[i].print();
		}

		std::cout << this->income << std::endl;
	}

	int isProductAvailable(const char* name) const
	{
		for (int i = 0; i < this->productsCount; i++)
		{
			if (strcmp(name, this->products[i].name) == 0)
			{
				return i;
			}
		}

		return -1;
	}

	int sellProduct(const char* name)
	{
		int flag = this->isProductAvailable(name);

		if (flag != -1)
		{
			if (this->products[flag].quantity != 0)
			{
				this->products[flag].quantity -= 1;
				this->income -= this->products[flag].price;

				return 1;
			}
		}

		return -1;
	}

	int loadProduct(const Product& product)
	{
		if (this->productsCount >= GlobalConstants::PRODUCTS_LIST_MAX_SIZE)
		{
			return -1;
		}

		unsigned index = this->productsCount;
		this->productsCount += 1;
		this->products[index].barcode = product.barcode;
		this->products[index].price = product.price;
		this->products[index].quantity = product.quantity;
		this->products[index].name = new char[strlen(product.name) + 1];
		strcpy(this->products[index].name, product.name);
		this->products[index].name[strlen(product.name)] = '\0';
		this->income += product.price * product.quantity;
	}
};

int main()
{
	Product apple(1, "Apple", 50, 0.50);
	Product banana(2, "Banana", 100, 0.30);
	Product orange(3, "Orange", 75, 0.40);

	Shop shop;

	strcpy(shop.name, "Fruit Shop");
	strcpy(shop.address, "123 Main St, Fruitville");

	shop.loadProduct(apple);
	shop.loadProduct(banana);
	shop.loadProduct(orange);

	orange.print();

	shop.print();

	int saleResult = shop.sellProduct("Banana");

	if (saleResult != -1) {
		std::cout << "Successfully sold Banana." << std::endl;
	}
	else {
		std::cout << "Banana is not available." << std::endl;
	}

	shop.print();
}