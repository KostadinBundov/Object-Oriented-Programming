#include "ModifiableIntegerFunction.h";

const unsigned ModifiableIntegerFunction::elementsCount = UINT16_MAX + 1;
const unsigned ModifiableIntegerFunction::zeroIndex = elementsCount / 2;

void ModifiableIntegerFunction::ModifiableIntegerFunction::free()
{
	delete[] this->arr;
	delete[] this->excludedPoints;

	this->arr = nullptr;
	this->excludedPoints = nullptr;

	this->isSurjective = true;
	this->isInjective = true;
	this->isModified = true;
}

void ModifiableIntegerFunction::copyFrom(const ModifiableIntegerFunction& other)
{
	this->initializeArrays();

	for (int i = 0; i < elementsCount; i++)
	{
		this->arr[i] = other.arr[i];
		this->excludedPoints[i] = other.excludedPoints[i];
	}
}

void ModifiableIntegerFunction::fillArr(short (*func)(short x))
{
	for (int value = SHRT_MIN, index = 0; value <= SHRT_MAX; value++, index++)
	{
		try
		{
			this->arr[index] = func(value);
		}
		catch (...)
		{
			this->excludedPoints[index] = true;
			this->arr[index] = 0;// set as a defValue...
		}
	}
}

void ModifiableIntegerFunction::initializeArrays()
{
	this->arr = new short[elementsCount] {0};
	this->excludedPoints = new bool[elementsCount] {0};
}

ModifiableIntegerFunction ModifiableIntegerFunction::composeKTimes(int counter) const
{
	ModifiableIntegerFunction copy(*this);

	while (counter > 0)
	{
		for (int i = 0; i < elementsCount; i++)
		{
			short result = copy.arr[i];
			copy.arr[i] = copy.arr[result];
		}

		counter--;
	}

	return copy;
}

ModifiableIntegerFunction ModifiableIntegerFunction::inverseFunction() const
{
	if (!this->checkIsBijective())
	{
		throw std::runtime_error("Function isn't inverse!");
	}

	ModifiableIntegerFunction copy(*this);

	for (int i = 0; i < elementsCount; i++)
	{
		short result = this->arr[i];
		copy.arr[result] = i;
	}

	return copy;
}

ModifiableIntegerFunction::ModifiableIntegerFunction(short (*func)(short x))
{
	this->initializeArrays();
	this->fillArr(func);
}

ModifiableIntegerFunction::ModifiableIntegerFunction(const ModifiableIntegerFunction& other)
{
	this->copyFrom(other);
}

ModifiableIntegerFunction& ModifiableIntegerFunction::operator=(const ModifiableIntegerFunction& other)
{
	if (this != &other)
	{
		this->free();
		this->copyFrom(other);
	}

	return *this;
}

ModifiableIntegerFunction::~ModifiableIntegerFunction()
{
	this->free();
}

void ModifiableIntegerFunction::setResult(short x, short y)
{
	this->arr[zeroIndex + x] = y;

	this->isModified = true;
}

void ModifiableIntegerFunction::excludePoint(short x)
{
	this->excludedPoints[zeroIndex + x] = true;

	this->isModified = true;
}

ModifiableIntegerFunction& ModifiableIntegerFunction::operator+=(const ModifiableIntegerFunction& other)
{
	for (int i = 0; i < elementsCount; i++)
	{
		if (this->excludedPoints[i])
		{
			continue;
		}

		if (other.excludedPoints[i])
		{
			this->arr[i] = 0;
			this->excludedPoints[i] = true;
			continue;
		}

		this->arr[i] = this->arr[i] + other.arr[i];
		this->excludedPoints[i] = this->excludedPoints[i] || other.excludedPoints[i];
	}

	this->isModified = true;

	return *this;
}

ModifiableIntegerFunction& ModifiableIntegerFunction::operator-=(const ModifiableIntegerFunction& other)
{
	for (int i = 0; i < elementsCount; i++)
	{
		if (this->excludedPoints[i] || other.excludedPoints[i]) {
			this->excludedPoints[i] = true;
			continue;
		}

		this->arr[i] = this->arr[i] - other.arr[i];
	}

	this->isModified = true;
	return *this;
}

ModifiableIntegerFunction operator+(const ModifiableIntegerFunction& lhs, const ModifiableIntegerFunction& rhs)
{
	ModifiableIntegerFunction result = ModifiableIntegerFunction(lhs);
	result += rhs;

	result.isModified = true;

	return result;
}

ModifiableIntegerFunction operator-(const ModifiableIntegerFunction& lhs, const ModifiableIntegerFunction& rhs)
{
	ModifiableIntegerFunction result = ModifiableIntegerFunction(lhs);
	result -= rhs;

	result.isModified = true;

	return result;
}

ModifiableIntegerFunction ModifiableIntegerFunction::operator()(const ModifiableIntegerFunction& g) const
{
	ModifiableIntegerFunction copy(g);

	for (int i = 0; i < elementsCount; i++)
	{
		short result = copy.arr[i];
		copy.arr[i] = this->arr[zeroIndex + result];

		//слагам че нямаме дефинирана стойност за това x но въпреки това отгоре си задавам някаква стойност която няма да има ефект, тъй като и в другите меди си проверяваме дали точките са дефинирани

		if (this->excludedPoints[i])
		{
			copy.excludedPoints[i] = true;
		}
	}

	return copy;
}

ModifiableIntegerFunction ModifiableIntegerFunction::operator^(int k) const
{
	if (k == -1)
	{
		return this->inverseFunction();
	}
	else if (k >= 0)
	{
		return this->composeKTimes(k);
	}
	else
	{
		throw std::runtime_error("K must be (-1) or greater value!");
	}
}

bool ModifiableIntegerFunction::checkIsInjective() const
{
	if (!this->isModified)
	{
		return this->isInjective;
	}

	MultiSet set(elementsCount - 1, 1);

	// идеята е да преминаваме през всеки един от елементите и да видим колко е y и да го добаавяме като срещане, итерираме през стойностите на x тоест ако стигнем до ситуация в която добавяме два пъти един и същи елемент в масива
	// значи не е изпълнено условието за инекция, тъй като за два различни x-а се получава едно и също y, което значи че не е инекция
	// като минат всички итерации на for и не сме влезнали в горната ситуация, то означава че всяко число се съдържа поп точно един път и за всяко x има по точно едно y

	for (int i = 0; i < elementsCount; i++)
	{
		try
		{
			set.addNumber(zeroIndex + arr[i]);
		}
		catch (const std::overflow_error& error)
		{
			this->isInjective = false;
			break;
		}
		catch (...)
		{
			std::cout << "another error while adding to the set";
			return false;
		}
	}

	this->isModified = false;
	return this->isInjective;
}

bool ModifiableIntegerFunction::checkIsSurjective() const
{
	if (!this->isModified)
	{
		return this->isSurjective;
	}

	MultiSet set(elementsCount - 1, 1);

	for (int i = 0; i < elementsCount; i++)
	{
		if (this->excludedPoints[i])
		{
			this->isSurjective = false;
			break;
		}

		try
		{
			set.addNumber(zeroIndex + arr[i]);
		}
		catch (const std::overflow_error& error)
		{
			continue;
		}
		catch (...)
		{
			std::cout << "another error while adding to the set";
			return false;
		}
	}

	for (int i = SHRT_MIN; i <= SHRT_MAX; i++)
	{
		if (set.getNumberOccurrences(zeroIndex + i) == 0)
		{
			this->isSurjective = false;
			break;
		}
	}

	this->isModified = false;
	return this->isSurjective;
}

bool ModifiableIntegerFunction::checkIsBijective() const
{
	bool res = this->checkIsInjective();
	isModified = true;
	res = res && this->checkIsSurjective();

	isModified = false;
	return res;
}

bool operator==(const ModifiableIntegerFunction& lhs, const ModifiableIntegerFunction& rhs)
{
	for (int i = 0; i < ModifiableIntegerFunction::elementsCount - 1; i++)
	{
		if (lhs.excludedPoints[i] || rhs.excludedPoints[i])
		{
			if (lhs.excludedPoints[i] != rhs.excludedPoints[i])
			{
				return false;
			}
		}
		else
		{
			if (lhs.arr[i] != rhs.arr[i])
			{
				return false;
			}
		}
	}

	return true;
}

bool operator!=(const ModifiableIntegerFunction& lhs, const ModifiableIntegerFunction& rhs)
{
	return !(lhs == rhs);
}

bool operator<(const ModifiableIntegerFunction& lhs, const ModifiableIntegerFunction& rhs)
{
	for (int i = 0; i < ModifiableIntegerFunction::elementsCount - 1; i++)
	{
		if (lhs.excludedPoints[i] && !rhs.excludedPoints[i])
		{
			continue;
		}
		else if (!lhs.excludedPoints[i] && rhs.excludedPoints[i])
		{
			return false;
		}
		else
		{
			if (lhs.arr[i] > rhs.arr[i] || lhs.arr[i] == rhs.arr[i])
			{
				return false;
			}
			else
			{
				continue;
			}
		}
	}

	return true;
}

bool operator<=(const ModifiableIntegerFunction& lhs, const ModifiableIntegerFunction& rhs)
{
	for (int i = 0; i < ModifiableIntegerFunction::elementsCount - 1; i++)
	{
		if (lhs.excludedPoints[i] && !rhs.excludedPoints[i])
		{
			continue;
		}
		else if (!lhs.excludedPoints[i] && rhs.excludedPoints[i])
		{
			return false;
		}
		else
		{
			if (lhs.arr[i] > rhs.arr[i])
			{
				return false;
			}
			else
			{
				continue;
			}
		}
	}

	return true;
}

bool operator>(const ModifiableIntegerFunction& lhs, const ModifiableIntegerFunction& rhs)
{
	for (int i = 0; i < ModifiableIntegerFunction::elementsCount - 1; i++)
	{
		if (!lhs.excludedPoints[i] && rhs.excludedPoints[i])
		{
			continue;
		}
		else if (lhs.excludedPoints[i] && !rhs.excludedPoints[i])
		{
			return false;
		}
		else
		{
			if (lhs.arr[i] < rhs.arr[i] || lhs.arr[i] == rhs.arr[i])
			{
				return false;
			}
			else
			{
				continue;
			}
		}
	}

	return true;
}

bool operator>=(const ModifiableIntegerFunction& lhs, const ModifiableIntegerFunction& rhs)
{
	for (int i = 0; i < ModifiableIntegerFunction::elementsCount - 1; i++)
	{
		if (!lhs.excludedPoints[i] && rhs.excludedPoints[i])
		{
			continue;
		}
		else if (lhs.excludedPoints[i] && !rhs.excludedPoints[i])
		{
			return false;
		}
		else
		{
			if (lhs.arr[i] < rhs.arr[i])
			{
				return false;
			}
			else
			{
				continue;
			}
		}
	}

	return true;
}

bool operator||(const ModifiableIntegerFunction& lhs, const ModifiableIntegerFunction& rhs)
{
	int startIndex = -1;
	short difference = 0;

	for (int i = 0; i < ModifiableIntegerFunction::elementsCount; ++i)
	{
		if (!lhs.excludedPoints[i] && !rhs.excludedPoints[i])
		{
			startIndex = i;
			difference = std::abs(lhs.arr[i] - rhs.arr[i]);

			break;
		}
		else if (lhs.excludedPoints[i] == true && rhs.excludedPoints[i] == true)
		{
			continue;
		}

		return false;
	}

	if (startIndex == -1)
	{
		return false;
	}

	for (int i = startIndex + 1; i < ModifiableIntegerFunction::elementsCount; ++i)
	{
		if (!lhs.excludedPoints[i] && !rhs.excludedPoints[i])
		{
			if (std::abs(lhs.arr[i] - rhs.arr[i]) != difference)
			{
				return false;
			}

			continue;
		}
		else if (lhs.excludedPoints[i] ==  true && rhs.excludedPoints[i] == true)
		{
			continue;
		}

		return false;
	}

	return true;
}

void ModifiableIntegerFunction::printPointsInInterval(short firstX, short firstY, short secondX, short secondY) const
{
	if (secondX - firstX != 20 || secondY - firstY != 20)
	{
		throw std::logic_error("Input data doesn't scope as needed");
	}

	for (int i = firstX; i <= secondX; ++i)
	{
		if (this->arr[zeroIndex + i] >= firstY && this->arr[zeroIndex + i] <= secondY)
		{
			std::cout << "(" << i << "; " << this->arr[zeroIndex + i] << ")" << std::endl;
		}
	}
}

void ModifiableIntegerFunction::writeInBinary(std::ofstream& ofs) const
{
	ofs.write((const char*)this->arr, elementsCount * sizeof(short));
	ofs.write((const char*)this->excludedPoints, elementsCount * sizeof(bool));
}

void ModifiableIntegerFunction::readFromBinary(std::ifstream& ifs)
{
	this->free();
	this->initializeArrays();

	ifs.read((char*)this->arr, elementsCount * sizeof(short));
	ifs.read((char*)this->excludedPoints, elementsCount * sizeof(bool));

	this->checkIsBijective();
}

void ModifiableIntegerFunction::serializeInFile(const char* fileName) const
{
	if (!fileName || !strlen(fileName))
	{
		throw std::invalid_argument("Invalid file name");
	}

	std::ofstream ofs(fileName, std::ios::binary);

	if (!ofs.is_open())
	{
		throw std::runtime_error("File can't be open!");
	}

	this->writeInBinary(ofs);
}

void ModifiableIntegerFunction::deserializeFromFile(const char* fileName)
{
	if (!fileName || !strlen(fileName))
	{
		throw std::invalid_argument("Invalid file name");
	}

	std::ifstream ifs(fileName, std::ios::binary);

	if (!ifs.is_open())
	{
		throw std::runtime_error("File can't be open!");
	}

	this->readFromBinary(ifs);
}