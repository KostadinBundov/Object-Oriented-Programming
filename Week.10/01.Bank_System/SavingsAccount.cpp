#include "SavingsAccount.h"

SavingsAccount::SavingsAccount(int id, double amount, double interestRate) : BankAccount(id, amount), interestRate(interestRate) {}

void SavingsAccount::calculateInterest()
{
	double tempInterest = getBalance() *  interestRate;
	deposit(tempInterest);
}
