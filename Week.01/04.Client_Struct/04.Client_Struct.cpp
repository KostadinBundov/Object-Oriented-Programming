#include <iostream>

constexpr size_t drinksCount = 8;

enum Drink {
	Whiskey,
	Vodka,
	Cola,
	Fanta,
	Water,
	Wine,
	Rum,
	Juice
};

void printDrink(const Drink& drink)
{
	switch (drink)
	{
	case Drink::Whiskey:
		std::cout << "Whiskey";
		break;
	case Drink::Vodka:
		std::cout << "Vodka";
		break;
	case Drink::Cola:
		std::cout << "Cola";
		break;
	case Drink::Fanta:
		std::cout << "Fanta";
		break;
	case Drink::Water:
		std::cout << "Water";
		break;
	case Drink::Wine:
		std::cout << "Wine";
		break;
	case Drink::Rum:
		std::cout << "Rum";
		break;
	case Drink::Juice:
		std::cout << "Juice";
		break;
	default:
		break;
	}
}

struct Client {
	char name[31] = { "Unknown" };
	bool favouriteDrinksList[drinksCount] = { false };
};

void removeDrinkFromVafourites(Client& client, const Drink& drink)
{
	client.favouriteDrinksList[drink] = false;
}

void addDrinkToFavourites(Client& client, const Drink& drink)
{
	client.favouriteDrinksList[drink] = true;
}

bool checkIfClientLikesDrink(const Client& client, const Drink& drink)
{
	return client.favouriteDrinksList[drink];
}
void printClientFavouriteList(const Client& client)
{
	std::cout << "Client " << client.name << "'s favourite drinks are:" << std::endl;

	for (int i = 0; i < drinksCount; i++)
	{
		if (client.favouriteDrinksList[i])
		{
			printDrink((Drink)i);
			std::cout << std::endl;
		}
	}
}

int main()
{
	Client client{ "John" };

	addDrinkToFavourites(client, Drink::Cola);
	addDrinkToFavourites(client, Drink::Whiskey);
	addDrinkToFavourites(client, Drink::Water);
	removeDrinkFromVafourites(client, Drink::Cola);
	std::cout << checkIfClientLikesDrink(client, Drink::Water) << std::endl;
	std::cout << checkIfClientLikesDrink(client, Drink::Fanta) << std::endl;
	printClientFavouriteList(client);
}