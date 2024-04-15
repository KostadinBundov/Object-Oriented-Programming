#include <iostream>
#include <fstream>

const size_t BUFFER_SIZE = 1024;

unsigned strLen(const char* str)
{
	if (!str)
	{
		return 0;
	}

	unsigned count = 0;

	while (*str)
	{
		count++;
		str += 1;
	}

	return count;
}

void InsertRowReversed(const char* str, int size, std::ofstream& dest)
{
	if (!str)
	{
		return;
	}

	size -= 1;

	while (size >= 0)
	{
		dest << str[size--];
	}

	dest << std::endl;
}

void copyFile(std::ifstream& source, std::ofstream& dest)
{
	char buff[BUFFER_SIZE];

	while (!source.eof())
	{
		source.getline(buff, BUFFER_SIZE);

		size_t currBuffSize = strlen(buff);

		InsertRowReversed(buff, currBuffSize, dest);
	}
}

void copyFileDataToAnother(const char* fileName)
{
	std::ifstream source(fileName);

	if (!source.is_open())
	{
		return;
	}

	std::ofstream dest("DestFile.txt");

	if (!dest.is_open())
	{
		return;
	}

	copyFile(source, dest);
}

int main()
{
	char fileName[] = "SourceFile.txt";

	copyFileDataToAnother(fileName);
}