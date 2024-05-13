#include "FoodPanda.h"

static size_t closestPowerOfAwo(size_t n)
{
	n--;

	n |= n >> 1;
	n |= n >> 2;
	n |= n >> 4;
	n |= n >> 8;
	n |= n >> 16;
	n |= n >> 32;

	return n + 1;
};

void FoodPanda::copyFrom(const FoodPanda& other)
{
	restaurants = new Restaurant * [other.capacity] {nullptr};

	for (int i = 0; i < other.capacity; i++)
	{
		if (other.restaurants[i] != nullptr)
		{
			restaurants[i] = new Restaurant(*other.restaurants[i]);//!!!!!
		}
	}

	size = other.size;
	capacity = other.capacity;
}

void FoodPanda::moveFrom(FoodPanda&& other)
{
	restaurants = other.restaurants;
	other.restaurants = nullptr;

	size = other.size;
	other.size = 0;

	capacity = other.capacity;
	other.capacity = 0;
}

void FoodPanda::free()
{
	for (int i = 0; i < capacity; i++)
	{
		delete restaurants[i];
	}

	delete[] restaurants;
}

void FoodPanda::resize(size_t newCapacity)
{
	capacity = newCapacity;

	Restaurant** newRestaurants = new Restaurant * [newCapacity] {nullptr};

	for (int i = 0; i < capacity; i++)
	{
		newRestaurants[i] = restaurants[i];
	}

	delete[] restaurants;
	restaurants = newRestaurants;
}

int FoodPanda::getRestaurantIndex(const char* name) const
{
	for (int i = 0; i < size; i++)
	{
		if (std::strcmp(restaurants[i]->getName(), name) == 0)
		{
			return i;
		}
	}

	return -1;
}

FoodPanda::FoodPanda()
{
	capacity = 8;
	size = 0;
	restaurants = new Restaurant * [capacity] {nullptr};
}

FoodPanda::FoodPanda(Restaurant** restaurants, size_t size)
{
	this->size = size;
	this->capacity = closestPowerOfAwo(size);
	this->restaurants = new Restaurant * [capacity] {nullptr};

	for (int i = 0; i < capacity; i++)
	{
		if (restaurants[i] != nullptr)
		{
			this->restaurants[i] = restaurants[i];
		}
	}
}

FoodPanda::FoodPanda(const FoodPanda& other)
{
	copyFrom(other);
}

FoodPanda::FoodPanda(FoodPanda&& other)
{
	moveFrom(std::move(other));
}

FoodPanda& FoodPanda::operator=(const FoodPanda& other)
{
	if (this != &other)
	{
		free();
		copyFrom(other);
	}

	return *this;
}

FoodPanda& FoodPanda::operator=(FoodPanda&& other)
{
	if (this != &other)
	{
		free();
		moveFrom(std::move(other));
	}

	return *this;
}

FoodPanda::~FoodPanda()
{
	free();
}

void FoodPanda::acceptOrder(const Order& order)
{
	try
	{
		completeOrder(order);
		std::cout << "Order accepted and processed successfully." << std::endl;
	}
	catch (const std::invalid_argument& ex)
	{
		std::cout << ex.what() << std::endl;
	}
	catch (const std::exception& ex)
	{
		std::cout << ex.what() << std::endl;
	}
	catch (...)
	{
		std::cout << "Bug in the system!" << std::endl;
	}
}

void FoodPanda::addRestaurant(const Restaurant& restaurant)
{
	if (size >= capacity)
	{
		resize(closestPowerOfAwo(capacity * 2));
	}

	restaurants[size++] = new Restaurant(restaurant);
}

void FoodPanda::addRestaurant(Restaurant&& restaurant)
{
	if (size >= capacity)
	{
		resize(capacity * 2);
	}

	restaurants[size++] = new Restaurant(std::move(restaurant));
}

void FoodPanda::completeOrder(const Order& order)
{
	int index = getRestaurantIndex(order.getRestaurantName());

	if (index == -1)
	{
		throw std::invalid_argument("No restaurant with such name exists");
	}

	restaurants[index]->getOrder(order);
}