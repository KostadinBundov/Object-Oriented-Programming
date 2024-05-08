#include "BankAccount.h"

BankAccount::BankAccount(int id, double startBalance)
{
	this->id = id;
	this->balance = startBalance;
}

void BankAccount::deposit(double amount)
{
	if (amount < 0)
	{
		throw std::invalid_argument("The amount must be a positive number!");
	}

	this->balance += amount;
}

void BankAccount::withdraw(double amount)
{
	if (amount < 0)
	{
		throw std::invalid_argument("The amount must be a positive number!");
	}

	if (balance < amount)
	{
		throw std::invalid_argument("Not enough money in bank account!");
	}

	this->balance -= amount;
}

double BankAccount::getBalance() const
{
	return this->balance;
}
