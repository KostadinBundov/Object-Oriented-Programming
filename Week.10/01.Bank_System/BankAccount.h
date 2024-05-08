#pragma once
#include <iostream>

class BankAccount
{
protected:
	int id = -1;
	double balance = 0;

public:
	BankAccount() = default;
	BankAccount(int id, double startBalance);

	void deposit(double amount);
	void withdraw(double amount);
	double getBalance() const;
};