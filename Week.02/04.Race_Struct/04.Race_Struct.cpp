#include <iostream>
#include <fstream>
#include <sstream>

const size_t RUNNER_NUMBER_SIZE_MAX = 40;
const size_t RACE_RUNNERS_SIZE_MAX = 100;

struct Time {
	unsigned seconds;
	unsigned minutes;
	unsigned hours;
};

struct Runner {
	char number[RUNNER_NUMBER_SIZE_MAX];
	Time time;
};

struct Race {
	size_t runnersCount;
	Runner runners[RACE_RUNNERS_SIZE_MAX];
};


void writeTimeInFile(std::ofstream& dest, const Time& time)
{
	dest << time.hours << ":" << time.minutes << ":" << time.seconds;
	dest << std::endl;
}
void writeRunnerInFile(std::ofstream& dest, const Runner& runner, const unsigned runnerIndex)
{
	dest << runnerIndex << '.' << runner.number << " ";
	writeTimeInFile(dest, runner.time);
}
void writeRaceInFile(std::ofstream& dest, Race* race)
{
	for (int i = 0; i < race->runnersCount; i++)
	{
		writeRunnerInFile(dest, race->runners[i], i + 1);
	}
}
void saveInFile(const char* fileName, Race* race)
{
	std::ofstream ofs(fileName);

	if (!ofs.is_open())
	{
		return;
	}

	writeRaceInFile(ofs, race);
}

Time readTimeFromFile(std::ifstream& source)
{
	char timeInfo[1024];

	source.getline(timeInfo, 1024);

	std::stringstream ss(timeInfo);

	Time time;
	char discard;

	ss >> time.hours >> discard >> time.minutes >> discard >> time.seconds;

	return time;
}
Runner readRunnerFromFile(std::ifstream& source)
{
	Runner runner;

	int index = source.tellg();
	index += 2;

	source.seekg(index);

	source.getline(runner.number, 1024, '-');

	runner.time = readTimeFromFile(source);

	return runner;
}
Race readRaceFromFile(std::ifstream& source)
{
	Race race;
	Runner runner;

	unsigned currIndex = 0;

	while (!source.eof())
	{
		runner = readRunnerFromFile(source);

		race.runners[currIndex++] = runner;
	}

	race.runnersCount = currIndex;

	return race;
}
Race readFromFile(const char* fileName)
{
	std::ifstream source(fileName);

	if (!source.is_open())
	{
		return { };
	}

	return readRaceFromFile(source);
}

int main()
{
	Race race = readFromFile("Source.txt");

	saveInFile("Dest.txt", &race);
}

