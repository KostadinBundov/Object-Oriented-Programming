#include "FoodPanda.h"
#include "ProductsList.h"
#include "Restaurant.h"
#include "Order.h"
#include <iostream>
#include <cstring>

int main() {
	ProductsList italianMenu;
	italianMenu.addProduct("Pizza");
	italianMenu.addProduct("Pasta");
	italianMenu.addProduct("Tiramisu");

	ProductsList burgerShopMenu;
	burgerShopMenu.addProduct("Burger");
	burgerShopMenu.addProduct("Fries");
	burgerShopMenu.addProduct("Shake");

	Restaurant italianRestaurant("Italian Cuisine", italianMenu);
	Restaurant burgerShop("Burger Shop", burgerShopMenu);

	FoodPanda foodPanda;
	foodPanda.addRestaurant(italianRestaurant);
	foodPanda.addRestaurant(burgerShop);

	ProductsList order1Products;
	order1Products.addProduct("Pizza");
	order1Products.addProduct("Pasta");

	ProductsList order2Products;
	order2Products.addProduct("Burger");
	order2Products.addProduct("Salad");

	Order order1("Italian Cuisine", order1Products);
	Order order2("Burger Shop", order2Products);

	foodPanda.acceptOrder(order1);

	foodPanda.acceptOrder(order2);
}
