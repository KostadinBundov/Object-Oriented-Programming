#include <iostream>
#include <fstream>

namespace ErrorMessages {
	const char CANNOT_OPEN_FILE[] = "Cannot open file!";
}

namespace FileNames {
	constexpr char RAW_FILE_NAME[] = "rawFile.dat";
	constexpr char KEY_FILE_NAME[] = "keyFile.dat";
}

unsigned getFileSize(std::ifstream& source)
{
	unsigned startIndex = source.tellg();

	source.seekg(0, std::ios::end);

	unsigned result = source.tellg();

	source.seekg(startIndex);
	source.clear();

	return result;
}

int* extractRowDataFromFile(std::ifstream& source, size_t& size)
{
	size_t fileSize = getFileSize(source);
	size = fileSize / sizeof(int);

	int* fileData = new int[size];

	source.read((char*)fileData, fileSize);

	return fileData;
}

uint8_t extractKeyFromFile(std::ifstream& source)
{
	uint8_t key = 0;

	source.read((char*)&key, sizeof(key));

	return key;
}

void decypherMessage(const char* rawMessageFileName, const char* keyFileName)
{
	std::ifstream rawMessageSource(rawMessageFileName, std::ios::binary);

	if (!rawMessageSource.is_open())
	{
		std::cout << ErrorMessages::CANNOT_OPEN_FILE << std::endl;
		return;
	}

	size_t size = 0;
	int* elements = extractRowDataFromFile(rawMessageSource, size);

	std::ifstream keySource(keyFileName, std::ios::binary);

	uint8_t key = extractKeyFromFile(keySource);

	for (int i = 0; i < size; i++)
	{
		std::cout << elements[i] + key << " ";
	}

	std::cout << std::endl;

	delete[] elements;
}

int main()
{
	decypherMessage(FileNames::RAW_FILE_NAME, FileNames::KEY_FILE_NAME);
}