#include <iostream>
#include <fstream>
#include <sstream>

namespace globalVariables
{
	const size_t F_NUMBER_MAX_SIZE = 10;
	const size_t NAME_MAX_SIZE = 30;
	const size_t STUDENTS_MAX_COUNT = 100;
	const size_t BUFFER_MAX_SIZE = 1024;
	const char SEPARATOR = ';';
}

enum class Major {
	undefined,
	IS,
	SI,
	KN,
	IN
};

const char* getMajorToStr(Major m)
{
	switch (m)
	{
	case Major::IS: return "IS";
	case Major::SI: return "SI";
	case Major::KN: return "KN";
	case Major::IN: return "IN";
	}

	return "";
}

Major getMajorFromStr(const char* str)
{
	if (strcmp(str, "IS") == 0)
	{
		return Major::IS;
	}
	else if (strcmp(str, "SI") == 0)
	{
		return  Major::SI;
	}
	else if (strcmp(str, "KN") == 0)
	{
		return  Major::KN;
	}
	else if (strcmp(str, "IN") == 0)
	{
		return  Major::IN;
	}
	else
	{
		return Major::undefined;
	}
}

struct Student {
	char fNumber[globalVariables::F_NUMBER_MAX_SIZE] = "";
	char firstName[globalVariables::NAME_MAX_SIZE] = "";
	char lastName[globalVariables::NAME_MAX_SIZE] = "";
	Major major = Major::undefined;
	double success = 2.0;
};

struct UniversityDatabase {
	size_t studentsCount = 0;
	Student students[globalVariables::STUDENTS_MAX_COUNT];
};

void parseRow(const char* row, Student& studentToReturn)
{
	std::stringstream ss(row);

	char majorStr[globalVariables::NAME_MAX_SIZE];

	ss.getline(studentToReturn.fNumber, globalVariables::BUFFER_MAX_SIZE, globalVariables::SEPARATOR);
	ss.getline(studentToReturn.firstName, globalVariables::BUFFER_MAX_SIZE, globalVariables::SEPARATOR);
	ss.getline(studentToReturn.lastName, globalVariables::BUFFER_MAX_SIZE, globalVariables::SEPARATOR);
	ss.getline(majorStr, globalVariables::BUFFER_MAX_SIZE, globalVariables::SEPARATOR);


	studentToReturn.major = getMajorFromStr(majorStr);

	ss >> studentToReturn.success;
}

UniversityDatabase readFileData(std::ifstream& source)
{
	UniversityDatabase university;

	size_t studentsCount = 0;

	char buff[globalVariables::BUFFER_MAX_SIZE];

	while (!source.eof())
	{
		source.getline(buff, globalVariables::BUFFER_MAX_SIZE);

		parseRow(buff, university.students[studentsCount++]);
	}

	university.studentsCount = studentsCount;

	return university;
}

UniversityDatabase extractUniversityData(const char* fileName)
{
	std::ifstream source(fileName);

	if (!source.is_open())
	{
		return { };
	}

	return readFileData(source);
}

void sortStudents(Student students[globalVariables::STUDENTS_MAX_COUNT], size_t size, bool(*isLess)(double prev, double next))
{
	for (int i = 0; i < size; i++)
	{
		int index = i;

		for (int j = i + 1; j < size; j++)
		{
			if (isLess(students[index].success, students[j].success))
			{
				index = j;
			}
		}

		if (index != i)
		{
			std::swap(students[i], students[index]);
		}
	}
}

void printStudentInfoOnConsole(const Student student)
{
	std::cout << student.fNumber << ": " << student.firstName << " " << student.lastName << " " << getMajorToStr(student.major) << ", " << student.success << std::endl;
}

void printDatabaseInfoOnConsole(Student students[globalVariables::STUDENTS_MAX_COUNT], size_t size)
{
	for (int i = 0; i < size; i++)
	{
		printStudentInfoOnConsole(students[i]);
	}
}

void printHighestGradeFromMajor(Student students[globalVariables::STUDENTS_MAX_COUNT], size_t size, Major major, bool(*isMatching)(Major, Major, double, double))
{
	double highestSuccess = 0;

	for (int i = 0; i < size; i++)
	{

		if (isMatching(students[i].major, major, students[i].success, highestSuccess))
		{
			highestSuccess = students[i].success;
		}
		if (students[i].major == major && students[i].success > highestSuccess)
		{
		}
	}

	std::cout << highestSuccess << std::endl;
}

int main()
{
	UniversityDatabase uni = extractUniversityData("students_data.txt");

	sortStudents(uni.students, uni.studentsCount, [](const double prev, const double next) {return prev < next; });
	printDatabaseInfoOnConsole(uni.students, uni.studentsCount);

	printHighestGradeFromMajor(uni.students, uni.studentsCount, Major::IS, [](Major searched, Major curr, double currSuc, double highestSuc) {return searched == curr && currSuc > highestSuc; });
}