#include <iostream>
#include <fstream>

unsigned getFileSize(std::ifstream& source)
{
	unsigned startIndex = source.tellg();

	source.seekg(0, std::ios::end);

	unsigned result = source.tellg();

	source.seekg(startIndex);
	source.clear();

	return result;
}

unsigned getFileSize(const char* fileName)
{
	std::ifstream ifs(fileName);

	if (!ifs.is_open()) 
	{
		return 0;
	}
		
	return getFileSize(ifs);
}

int main()
{
	std::cout << getFileSize("File.txt");
}
