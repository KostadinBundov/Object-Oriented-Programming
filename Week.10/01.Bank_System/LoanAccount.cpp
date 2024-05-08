#include "LoanAccount.h"

LoanAccount::LoanAccount(int id, double amount, double interestRate) : BankAccount(id, amount), interestRate(interestRate) {}

void LoanAccount::applyInterest()
{
	double tempInterest = balance * interestRate;
	balance += tempInterest;
}
