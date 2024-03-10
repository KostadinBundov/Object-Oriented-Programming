#include <iostream>

int daysOfMonth[13] = { 0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };

struct Date {
	unsigned day;
	unsigned month;
	unsigned year;
};

bool checkIsLeapYear(unsigned year)
{
	return (year % 4 == 0 && year % 100 != 0) || (year % 400 == 0);
}

void increaseMonth(Date& date)
{
	date.day = 1;
	date.month += 1;
}

void printDate(const Date& date)
{
	std::cout << "Today is " << date.day << " of " << date.month << ", " << date.year << " year.";
}

void goToNextDay(Date& date)
{
	date.day += 1;

	if (date.day > daysOfMonth[date.month])
	{
		date.day = 1;

		if (date.month != 12)
		{
			date.month += 1;
		}
		else
		{
			date.month = 1;
			date.year += 1;
		}
	}
}

unsigned getCountOfLeapYears(const Date& date)
{
	unsigned years = date.year;

	if (date.month <= 2)
	{
		years -= 1;
	}

	return years / 4 - years / 100 + years / 400;
}
unsigned getCountOfDaysForMonths(const Date& date)
{
	unsigned totalDays = 0;

	for (int i = 1; i <= date.month - 1; i++)
	{
		totalDays += daysOfMonth[i];
	}

	return totalDays;
}

long calculateDaysInYear(const Date& date)
{
	return date.year * 365
		+ date.day
		+ getCountOfDaysForMonths(date)
		+ getCountOfLeapYears(date);
}

int getDaysBetweenTwoDates(const Date& firstDate, const Date& secondDate)
{
	long firstDateTotalDays = calculateDaysInYear(firstDate);
	long secondDateTotalDays = calculateDaysInYear(secondDate);

	return abs(firstDateTotalDays - secondDateTotalDays);
}

int main()
{
	/*Date today = { 31, 12, 2024 };

	if (checkIsLeapYear(today.year))
	{
		daysOfMonth[2] = 29;
	}

	goToNextDay(today);

	printDate(today);*/

	Date d1 = { 10, 2, 2000 };
	Date d2 = { 10, 3, 2000 };

	std::cout << getDaysBetweenTwoDates(d1, d2);
}