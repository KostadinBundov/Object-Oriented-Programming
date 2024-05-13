#pragma once
#include "Restaurant.h"

class FoodPanda
{
private:
	Restaurant** restaurants;
	size_t size;
	size_t capacity;

	void copyFrom(const FoodPanda& other);
	void moveFrom(FoodPanda&& other);
	void free();

	void resize(size_t newCapacity);

	int getRestaurantIndex(const char* name) const;

	void completeOrder(const Order& order);

public:
	FoodPanda();
	FoodPanda(Restaurant** restaurants, size_t size);

	FoodPanda(const FoodPanda& other);
	FoodPanda(FoodPanda&& other);

	FoodPanda& operator=(const FoodPanda& other);
	FoodPanda& operator=(FoodPanda&& other);

	~FoodPanda();

	void acceptOrder(const Order& order);

	void addRestaurant(const Restaurant& restaurant);
	void addRestaurant(Restaurant&& restaurant);
};