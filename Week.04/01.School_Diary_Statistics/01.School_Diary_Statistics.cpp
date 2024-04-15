#include <iostream>
#include <fstream>

#pragma warning( disable : 4996)

namespace ErrorMessages {
	constexpr char CANNOT_OPEN_FILE[]{"File cannot be open"};
}

struct Subject {
	char* name = nullptr;
	unsigned gradesCount = 0;
	double* grades = nullptr;

	double getSumGrades() const
	{
		double totalSum = 0;

		for (int i = 0; i < gradesCount; i++)
		{
			totalSum += grades[i];
		}

		return totalSum;
	}
};

struct Diary {
	size_t subjectsCount = 0;
	Subject* subjectsList = nullptr;

	unsigned calculateAverageSuccess() const
	{
		double gradesTotalSum = 0;
		

		for (int i = 0; i < subjectsCount; i++)
		{
			gradesTotalSum += subjectsList[i].getSumGrades();
		}

		return gradesTotalSum / subjectsCount;
	}
};

void freeSubject(Subject& subject)
{
	delete[] subject.name;
	delete[] subject.grades;
	subject.gradesCount = 0;
}

void freeDiary(Diary& diary)
{
	for (int i = 0; i < diary.subjectsCount; i++)
	{
		freeSubject(diary.subjectsList[i]);
	}

	delete[] diary.subjectsList;
	diary.subjectsCount = 0;
}

void saveSubject(std::ofstream& dest, const Subject& subject)
{
	size_t nameLength = strlen(subject.name);

	dest.write((const char*) &nameLength, sizeof(nameLength));
	dest.write(subject.name, nameLength);
	dest.write((const char*)&subject.gradesCount, sizeof(subject.gradesCount));
	dest.write((const char*)subject.grades, subject.gradesCount * sizeof(double));
}

void writeInBinaryFile(std::ofstream& dest, const Diary& diary)
{
	dest.write((const char*)&diary.subjectsCount, sizeof(diary.subjectsCount));

	for (int i = 0; i < diary.subjectsCount; i++)
	{
		saveSubject(dest, diary.subjectsList[i]);
	}
}

void writeInBinaryFile(const char* fileName, const Diary& diary)
{
	std::ofstream ofs(fileName);

	if (!ofs.is_open())
	{
		std::cout << ErrorMessages::CANNOT_OPEN_FILE << std::endl;
		return;
	}

	writeInBinaryFile(ofs, diary);
}

void readSubject(std::ifstream& source, Subject& subject)
{
	size_t nameLength = 0;

	source.read((char*)&nameLength, sizeof(nameLength));
	subject.name = new char[nameLength + 1];
	source.read(subject.name, nameLength);
	subject.name[nameLength] = '\0';

	source.read((char*)&subject.gradesCount, sizeof(subject.gradesCount));
	subject.grades = new double[subject.gradesCount];
	source.read((char*)subject.grades, subject.gradesCount * sizeof(double));
}

void readFromBinaryFile(std::ifstream& source, Diary& diary)
{
	source.read((char*) &diary.subjectsCount, sizeof(diary.subjectsCount));

	diary.subjectsList = new Subject[diary.subjectsCount];

	for (int i = 0; i < diary.subjectsCount; i++)
	{
		readSubject(source, diary.subjectsList[i]);
	}
}

void readFromBinaryFile(const char* fileName, Diary& diary)
{
	std::ifstream ifs(fileName);

	if (!ifs.is_open())
	{
		std::cout << ErrorMessages::CANNOT_OPEN_FILE << std::endl;
		return;
	}

	readFromBinaryFile(ifs, diary);
}

int main()
{
	Diary d;
	d.subjectsCount = 4;
	d.subjectsList = new Subject[d.subjectsCount];

	d.subjectsList[0].name = new char[strlen("AAA") + 1];
	strcpy(d.subjectsList[0].name, "AAA");	
	d.subjectsList[0].gradesCount = 4;
	d.subjectsList[0].grades = new double[4] {6, 5, 6, 3};

	d.subjectsList[1].name = new char[strlen("BBB") + 1];
	strcpy(d.subjectsList[1].name, "BBB");
	d.subjectsList[1].gradesCount = 3;
	d.subjectsList[1].grades = new double[3] {6, 5, 6};

	d.subjectsList[2].name = new char[strlen("CCC") + 1];
	strcpy(d.subjectsList[2].name, "CCC");
	d.subjectsList[2].gradesCount = 4;
	d.subjectsList[2].grades = new double[4] {6, 5, 6, 3};

	d.subjectsList[3].name = new char[strlen("DDD") + 1];
	strcpy(d.subjectsList[3].name, "DDD");
	d.subjectsList[3].gradesCount = 3;
	d.subjectsList[3].grades = new double[3] {3, 3, 3};

	writeInBinaryFile("file.dat", d);

	std::cout << d.calculateAverageSuccess() << std::endl;

	Diary result;

	readFromBinaryFile("file.dat", result);

	std::cout << result.calculateAverageSuccess() << std::endl;

	freeDiary(d);
	freeDiary(result);
}