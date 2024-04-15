#include <iostream>

using std::cin;
using std::cout;
using std::endl;

struct Point {
	int x;
	int y;
};

struct Line {
	Point start;
	Point end;
};

void readPoint(Point& point)
{
	cin >> point.x;
	cin >> point.y;
}

void readLine(Line& line)
{
	readPoint(line.start);
	readPoint(line.end);
}

int getLineLength(const Line& line)
{
	int dx = line.start.x - line.end.x;
	int dy = line.start.y - line.end.y;

	return sqrt(dx * dx + dy * dy);
}

void sortLines(Line* lines, size_t size)
{
	int* lengths = new int[size];

	for (int i = 0; i < size; i++)
	{
		lengths[i] = getLineLength(lines[i]);
	}


	for (int i = 0; i < size; i++)
	{
		unsigned index = i;

		for (int j = i + 1; j < size; j++)
		{
			if (lengths[index] > lengths[j])
			{
				index = j;
			}
		}

		if (index != i)
		{
			std::swap(lengths[i], lengths[index]);
			std::swap(lines[i], lines[index]);
		}
	}


	delete[] lengths;
}

void printLines(const Line* lines, size_t size)
{
	for (int i = 0; i < size; i++)
	{
		cout << "{" << lines[i].start.x << ";" << lines[i].start.y << "} - {" << lines[i].end.x << ";" << lines[i].end.y << "}" << endl;
	}
}

int main()
{
	int n;
	cin >> n;

	Line* lines = new Line[n];

	for (int i = 0; i < n; i++)
	{
		readLine(lines[i]);
	}

	sortLines(lines, n);

	printLines(lines, n);

	delete[] lines;
}