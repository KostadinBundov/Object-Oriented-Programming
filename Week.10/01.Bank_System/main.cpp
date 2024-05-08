#include <iostream>
#include "CheckingAccount.h";
#include "LoanAccount.h";
#include "SavingsAccount.h";

int main()
{
    try {
        SavingsAccount sa(1, 1000, 0.03);
        sa.calculateInterest();
        std::cout << "Savings Account Balance after interest: $" << sa.getBalance() << std::endl;

        CheckingAccount ca(2, 500);
        ca.deposit(100);
        std::cout << "Checking Account Balance after deposit: $" << ca.getBalance() << std::endl;
        ca.withdraw(600);
        std::cout << "Checking Account Balance after withdrawal: $" << ca.getBalance() << std::endl;

        LoanAccount la(3, -5000, 0.07);
        la.applyInterest();
        std::cout << "Loan Account Balance after applying interest: $" << la.getBalance() << std::endl;

        ca.deposit(-50);
    }
    catch (const std::invalid_argument& e) {
        std::cout << "Error: " << e.what() << std::endl;
    }

    try {
        BankAccount ba(4, 200);
        ba.withdraw(300);
    }
    catch (const std::invalid_argument& e) {
        std::cout << "Error: " << e.what() << std::endl;
    }
}
