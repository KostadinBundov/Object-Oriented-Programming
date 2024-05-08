#include "CheckingAccount.h"

CheckingAccount::CheckingAccount(int id, double amount) : BankAccount(id, amount) {}

void CheckingAccount::withdraw(double amount)
{
	if (amount < 0)
	{
		throw std::invalid_argument("The amount must be a positive number!");
	}

	balance -= amount;
}
