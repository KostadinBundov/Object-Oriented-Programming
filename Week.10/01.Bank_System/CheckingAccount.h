#pragma once
#include "BankAccount.h"

class CheckingAccount : public BankAccount
{
private:

public:
	CheckingAccount(int id, double amount);

	void withdraw(double amount);
};