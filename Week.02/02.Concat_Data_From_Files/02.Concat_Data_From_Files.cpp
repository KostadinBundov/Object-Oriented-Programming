#include <iostream>
#include <fstream>

void concatFiles(const char* outputFileName, const char** inputFileNames, int numberOfFiles)
{
    std::ofstream dest(outputFileName);

    if (!dest.is_open())
    {
        std::cerr << "Cannot open the output file." << std::endl;
        return;
    }

    char buff[1024];

    for (int i = 0; i < numberOfFiles; ++i)
    {
        std::ifstream inputFile(inputFileNames[i]);

        if (!inputFile.is_open())
        {
            std::cerr << "Cannot open input file " << inputFileNames[i] << std::endl;
            continue;
        }

        while (!inputFile.eof())
        {
            inputFile.getline(buff, 1024);

            dest << buff << std::endl;
        }

        inputFile.close();
    }

    dest.close();
}

int main()
{
    const char* files[] = { "file1.txt", "file2.txt", "file3.txt" };
    size_t numberOfFiles = 3;

    concatFiles("output.txt", files, numberOfFiles);
}
