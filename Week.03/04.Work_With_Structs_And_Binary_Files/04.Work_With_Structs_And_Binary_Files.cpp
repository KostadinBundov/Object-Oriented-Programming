#include <iostream>
#include <fstream>

namespace GlobalConstants {
	constexpr size_t NAME_MAX_SIZE = 23;
	constexpr char FILE_NAME[] = "people.dat";
}

namespace ErrorMessages {
	const char CANNOT_OPEN_FILE[] = "Cannot open file!";
}

struct Person {
	char name[GlobalConstants::NAME_MAX_SIZE] = "Unknown";
	unsigned salary = 0;
};

struct People {
	size_t peopleCount = 0;
	Person* people;
};

unsigned getFileSize(std::ifstream& source)
{
	unsigned startIndex = source.tellg();

	source.seekg(0, std::ios::end);

	unsigned result = source.tellg();

	source.seekg(startIndex);
	source.clear();

	return result;
}

void extractDataFromFile(std::ifstream& source, People& database)
{
	size_t fileSize = getFileSize(source);
	
	database.peopleCount = fileSize / sizeof(Person);
	
	database.people = new Person[database.peopleCount];

	source.read((char*)database.people, fileSize);
}

void extractDataFromFile(const char* fileName, People& database)
{
	std::ifstream ifs(fileName, std::ios::binary);

	if (!ifs.is_open())
	{
		std::cout << ErrorMessages::CANNOT_OPEN_FILE;
		return;
	}

	extractDataFromFile(ifs, database);
}

double calculateAverageSalary(const Person* people, size_t size)
{
	double result = 0;

	for (int i = 0; i < size; i++)
	{
		result += people[i].salary;
	}

	return result / size;
}

void printSinglePersonData(const Person& person)
{
	std::cout << person.name << ": " << person.salary << std::endl;
}

void printPeopleAboveAverageSalary(const Person* people, size_t size)
{
	double averageSalary = calculateAverageSalary(people, size);

	for (int i = 0; i < size; i++)
	{
		if (people[i].salary >= averageSalary)
		{
			printSinglePersonData(people[i]);
		}
	}
}

void addNewPersonToFile(std::ofstream& dest, const Person& person)
{
	dest.write((const char*)&person, sizeof(Person));
}

void addNewPersonToFile(const char* fileName, const Person& person)
{
	std::ofstream ofs(fileName, std::ios::app);

	if (!ofs.is_open())
	{
		std::cout << ErrorMessages::CANNOT_OPEN_FILE << std::endl;
		return;
	}

	addNewPersonToFile(ofs, person);
}

void InsertStartingDataIntoFile(const char* fileName)
{
	constexpr size_t PEOPLE_COUNT = 3;

	Person peopleArray[PEOPLE_COUNT] = {
		{"Ivan", 200},
		{"Boromir", 200},
		{"Petar", 500}
	};

	People database;
	database.peopleCount = PEOPLE_COUNT;
	database.people = peopleArray;

	std::ofstream ofs(fileName, std::ios::binary | std::ios::trunc); 

	if (!ofs.is_open())
	{
		std::cout << ErrorMessages::CANNOT_OPEN_FILE << std::endl;

		return;
	}

	ofs.write((const char*)database.people, database.peopleCount * sizeof(Person));
}

int main()
{
	InsertStartingDataIntoFile(GlobalConstants::FILE_NAME);

	People database;

	extractDataFromFile(GlobalConstants::FILE_NAME, database);

	printPeopleAboveAverageSalary(database.people, database.peopleCount);

	Person newPerson1{
		"Kostadin",
		600
	};

	Person newPerson2{
		"Ivayla",
		555
	};

	addNewPersonToFile(GlobalConstants::FILE_NAME, newPerson1);
	addNewPersonToFile(GlobalConstants::FILE_NAME, newPerson2);

	delete[] database.people;

	People updatedDatabase;

	extractDataFromFile(GlobalConstants::FILE_NAME, updatedDatabase);

	printPeopleAboveAverageSalary(updatedDatabase.people, updatedDatabase.peopleCount);

	delete[] updatedDatabase.people;
}