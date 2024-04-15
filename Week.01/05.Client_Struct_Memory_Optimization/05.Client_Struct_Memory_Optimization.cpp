#include <iostream>

constexpr size_t drinksCount = 8;

enum class Drink : uint8_t {
	Whiskey = 1 << 0,
	Vodka = 1 << 1,
	Cola = 1 << 2,
	Fanta = 1 << 3,
	Water = 1 << 4,
	Wine = 1 << 5,
	Rum = 1 << 6,
	Juice = 1 << 7,
	END = 1 << 8
};

struct Client {
	char name[50];
	uint8_t favouriteDrinks;
};

void printDrink(Drink drink)
{
	switch (drink)
	{
	case Drink::Whiskey:
		std::cout << "whiskey";
		break;
	case Drink::Vodka:
		std::cout << "vodka";
		break;
	case Drink::Cola:
		std::cout << "cola";
		break;
	case Drink::Fanta:
		std::cout << "fanta";
		break;
	case Drink::Water:
		std::cout << "water";
		break;
	case Drink::Wine:
		std::cout << "wine";
		break;
	case Drink::Rum:
		std::cout << "rum";
		break;
	case Drink::Juice:
		std::cout << "juice";
		break;
	default:
		break;
	}
}

Drink iterateDrink(Drink drink)
{
	return Drink((uint8_t)drink << 1);
}

Drink startDrink()
{
	return Drink::Whiskey;
}

Drink endDrink()
{
	return Drink::END;
}

void removeDrinkFromFafourites(Client& client, Drink drink)
{
	client.favouriteDrinks ^= (uint8_t)drink;
}

void addDrinkToFavourites(Client& client, Drink drink)
{
	client.favouriteDrinks |= (uint8_t)drink;
}

bool checkIfClientLikesDrink(const Client& client, Drink drink)
{
	return client.favouriteDrinks & (uint8_t)drink;
}
void printClientFavouriteList(const Client& client)
{
	std::cout << "Client " << client.name << "'s favourite drinks are:" << std::endl;

	for (Drink i = startDrink(); i != endDrink(); i = iterateDrink(i))
	{
		if (checkIfClientLikesDrink(client, i))
		{
			printDrink(i);
			std::cout << ", ";
		}
	}

	std::cout << std::endl;
}

int main()
{
	Client c{
		"Kostadin",
		24
	};

	printClientFavouriteList(c);

	removeDrinkFromFafourites(c, Drink::Water);

	printClientFavouriteList(c);

	addDrinkToFavourites(c, Drink::Whiskey);
	addDrinkToFavourites(c, Drink::Rum);
	addDrinkToFavourites(c, Drink::Juice);
	addDrinkToFavourites(c, Drink::Vodka);

	printClientFavouriteList(c);

	removeDrinkFromFafourites(c, Drink::Rum);

	printClientFavouriteList(c);

	std :: cout << checkIfClientLikesDrink(c, Drink::Rum) << std::endl;
	std :: cout << checkIfClientLikesDrink(c, Drink::Vodka);
}