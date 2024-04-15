#include <iostream>
#include <fstream>
#include <ctime>

constexpr size_t SIZE = 1024;

void replaceSymbol(char* str, const char replace, const char with)
{
	size_t strSize = strlen(str);

	if (strSize > 0 && str[strSize - 1] == replace)
	{
		str[strSize - 1] = with;
	}
}

int readUserInput(char* line)
{
	std::cin.getline(line, SIZE);

	if (std::cin.eof() || line[0] == '\0')
	{
		return 0;
	}

	return 1;
}

void insertUserInput(std::ofstream& dest)
{
	char line[SIZE];

	while (true)
	{
		if (!readUserInput(line))
		{
			break;
		}

		time_t now = time(0);
		char str[32];
		ctime_s(str, 32, &now);

		replaceSymbol(str, '\n', '\0');

		dest << '[' << str << ']' << ": " << line << std::endl;
	}
}

void insertUserInput(const char* fileName)
{
	std::ofstream ofs(fileName, std::ios::app);

	if (!ofs.is_open())
	{
		std::cout << "File can't be open";
		return;
	}

	insertUserInput(ofs);
}

int main()
{
	insertUserInput("LOGS.txt");
}