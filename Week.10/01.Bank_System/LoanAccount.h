#pragma once
#include "BankAccount.h"

class LoanAccount : public BankAccount
{
private:
	double interestRate = 0;

public:
	LoanAccount() = default;
	LoanAccount(int id, double amount, double interestRate);

	void applyInterest();
};