#pragma once
#include "BankAccount.h"

class SavingsAccount : public BankAccount
{
private:
	double interestRate = 0;

public:
	SavingsAccount() = default;
	SavingsAccount(int id, double amount, double interestRate);

	void calculateInterest();
};
