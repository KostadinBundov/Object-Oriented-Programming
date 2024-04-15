#include <iostream>
#include <fstream>

const size_t BUFFER_SiZE = 1024;


void copyFile(std::ifstream& source)
{
	char buff[BUFFER_SiZE];

	while (!source.eof())
	{
		source.getline(buff, BUFFER_SiZE);

		std::cout << buff << std::endl;
	}
}
void copyFileText(const char* fileName)
{
	std::ifstream ifs(fileName);

	if (!ifs.is_open())
	{
		return;
	}

	copyFile(ifs);
}

int main()
{
	char fileName[] = "01.Print_Program_Code.cpp";
	copyFileText(fileName);
}