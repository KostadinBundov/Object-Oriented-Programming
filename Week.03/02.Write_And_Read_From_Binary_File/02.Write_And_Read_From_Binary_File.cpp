#include <iostream>
#include <fstream>

namespace GlobalConstants {
	constexpr size_t ARRAY_SIZE = 7;
}

namespace ErrorMessages {
	const char CANNOT_OPEN_FILE[] = "Cannot open file!";
}

void writeInBinaryFile(std::ofstream& dest, const int* arr)
{
	dest.write((const char*)arr, GlobalConstants::ARRAY_SIZE * sizeof(int));
}

void wirteInBinaryFile(const char* fileName, const int* arr)
{
	std::ofstream ofs(fileName, std::ios::binary);

	if (!ofs.is_open())
	{
		std::cout << ErrorMessages::CANNOT_OPEN_FILE << std::endl;
		return;
	}

	writeInBinaryFile(ofs, arr);
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

int* readFromBinaryFile(std::ifstream& source, size_t& size)
{
	size_t sizeOfFile = getFileSize(source);
	size = sizeOfFile / sizeof(int);

	int* arr = new int[size];

	source.read((char*)arr, sizeOfFile);

	return arr;
}

int* readFromBinaryFile(const char* fileName, size_t& size)
{
	std::ifstream ifs(fileName, std::ios::binary);

	unsigned startIndex = ifs.tellg();

	if (!ifs.is_open())
	{
		std::cout << ErrorMessages::CANNOT_OPEN_FILE << std::endl;
		return nullptr;
	}

	int* result = readFromBinaryFile(ifs, size);

	ifs.seekg(startIndex, std::ios::beg);
	ifs.clear();

	return result;
}

void printArr(const int* arr, size_t size)
{
	for (int i = 0; i < size; i++)
	{
		std::cout << arr[i] << std::endl;
	}
}

int getMaxNumberFromBinaryFile(std::ifstream& source)
{
	int maxNumber = INT32_MIN;
	int currentNumber = 0;

	while (true)
	{
		source.read((char*)&currentNumber, sizeof(currentNumber));

		if (source.eof())
		{
			break;
		}

		if (currentNumber > maxNumber)
		{
			maxNumber = currentNumber;
		}
	}

	return maxNumber;
}

int getMaxNumberFromBinaryFile(const char* fileName)
{
	std::ifstream ifs(fileName, std::ios::binary);

	if (!ifs.is_open())
	{
		std::cout << ErrorMessages::CANNOT_OPEN_FILE << std::endl;
		return -1;
	}

	return getMaxNumberFromBinaryFile(ifs);
}

int main()
{
	int arr[GlobalConstants::ARRAY_SIZE] = { 1, 4, 5, 6, 2, 7, 3 };

	wirteInBinaryFile("numbers.dat", arr);

	size_t size = 0;
	int* arrResult = readFromBinaryFile("numbers.dat", size);

	printArr(arrResult, size);
	delete[] arrResult;

	std::cout << "Max Element: " << getMaxNumberFromBinaryFile("numbers.dat") << std::endl;
}