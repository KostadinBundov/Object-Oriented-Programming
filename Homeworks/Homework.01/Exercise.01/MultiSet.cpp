#include "MultiSet.h";

const uint8_t MultiSet::bucketSize = sizeof(uint8_t) * 8;

namespace customFunctions 
{
	void addNumberNTimes(MultiSet& set, const unsigned number, const uint8_t count)
	{
		for (int i = 0; i < count; i++)
		{
			set.addNumber(number);
		}
	}
	void printNumberInBinary(unsigned number)
	{
		unsigned mask = 1 << (MultiSet::bucketSize - 1);

		while (mask != 0)
		{
			std::cout << ((number & mask) ? '1' : '0');
			mask >>= 1;
		}
	}
}

void MultiSet::setBitsUsage(uint8_t number)
{
	if (number < 1 || number > 8)
	{
		throw std::out_of_range("K must be between 1 and 8");
	}

	this->bitsUsage = number;
}

void MultiSet::setMaxNumber(int number)
{
	if (number < 0)
	{
		throw std::out_of_range("Max number has to be a positive number");
	}

	this->maxNumber = number;
}

MultiSet::MultiSet(int n, uint8_t k)
{
	this->setBitsUsage(k);
	this->setMaxNumber(n);

	this->maxNumberOccurrences = powerOfTwo(this->bitsUsage) - 1;
	this->size = (n + 1) * k / this->bucketSize + 1;
	this->buckets = new uint8_t[size]{ 0 };
}

MultiSet::MultiSet(const MultiSet& other)
{
	copyFrom(other);
}

MultiSet& MultiSet::operator=(const MultiSet& other)
{
	if (this != &other)
	{
		free();
		copyFrom(other);
	}

	return *this;

	free();
}

MultiSet::~MultiSet()
{
	free();
}

void MultiSet::free()
{
	delete[] this->buckets;

	this->size = 0;
	this->maxNumber = 0;
	this->bitsUsage = 1;
	this->maxNumberOccurrences = 1;
}

void MultiSet::copyFrom(const MultiSet& other)
{
	this->size = other.size;
	this->buckets = new uint8_t[size];

	for (int i = 0; i < size; i++)
	{
		this->buckets[i] = other.buckets[i];
	}

	this->maxNumberOccurrences = other.maxNumberOccurrences;
	this->maxNumber = other.maxNumber;
	this->bitsUsage = other.bitsUsage;
}

unsigned MultiSet::getBucketIndex(unsigned element) const
{
	return element * this->bitsUsage / this->bucketSize;
}

unsigned MultiSet::getElementStartBitIndex(unsigned element) const
{
	return element * this->bitsUsage % this->bucketSize;
}

void MultiSet::addNumber(unsigned element)
{

	if (element > this->maxNumber)
	{
		throw std::out_of_range("Number is out of range");
	}

	uint8_t currentCount = this->getNumberOccurrences(element);

	if (currentCount >= this->maxNumberOccurrences)
	{
		throw std::overflow_error("Maximum occurrences exceeded");
	}

	unsigned bucketIndex = this->getBucketIndex(element);
	unsigned bitStartIndex = this->getElementStartBitIndex(element);

	uint8_t mask = (1 << this->bitsUsage) - 1;
	uint8_t newCount = currentCount + 1;

	if (bitStartIndex + this->bitsUsage <= this->bucketSize)
	{
		mask <<= (this->bucketSize - this->bitsUsage - bitStartIndex);
		this->buckets[bucketIndex] &= ~mask;
		this->buckets[bucketIndex] |= (newCount << (this->bucketSize - this->bitsUsage - bitStartIndex));
	}
	else
	{
		uint8_t lhsBitsCount = this->bucketSize - bitStartIndex;
		uint8_t rhsBitsCount = this->bitsUsage - lhsBitsCount;

		//manipulate first bucket
		uint8_t maskLhs = (1 << lhsBitsCount) - 1;
		this->buckets[bucketIndex] &= ~maskLhs;
		this->buckets[bucketIndex] |= (newCount >> rhsBitsCount);

		//Manipulate second bucket
		uint8_t maskRhs = (1 << rhsBitsCount) - 1;
		this->buckets[bucketIndex + 1] &= ~(maskRhs << (this->bucketSize - rhsBitsCount));
		this->buckets[bucketIndex + 1] |= (newCount << (this->bucketSize - rhsBitsCount));
	}
}

uint8_t MultiSet::getNumberOccurrences(unsigned element) const
{
	unsigned bucketIndex = this->getBucketIndex(element);
	unsigned bitStartIndex = this->getElementStartBitIndex(element);

	uint8_t currBucketValue = this->buckets[bucketIndex];

	currBucketValue <<= bitStartIndex;

	if (bitStartIndex + this->bitsUsage <= this->bucketSize)
	{
		currBucketValue >>= (this->bucketSize - this->bitsUsage);
	}
	else
	{

		uint8_t lhsBitsCount = this->bucketSize - bitStartIndex;
		uint8_t rhsBitsCount = this->bitsUsage - lhsBitsCount;

		currBucketValue >>= (this->bucketSize - lhsBitsCount);

		uint8_t mask = (1 << lhsBitsCount) - 1;
		currBucketValue &= mask;

		uint8_t nextBucketValue = this->buckets[bucketIndex + 1];
		nextBucketValue >>= (this->bucketSize - rhsBitsCount);

		currBucketValue <<= rhsBitsCount;
		currBucketValue |= nextBucketValue;
	}

	return currBucketValue;
}

unsigned MultiSet::getMaxNumber() const
{
	return this->maxNumber;
}

uint8_t MultiSet::getBitsUsage() const
{
	return this->bitsUsage;
}

uint8_t MultiSet::getMaxNumberOccurrences() const
{
	return this->maxNumberOccurrences;
}

void MultiSet::printMultiSet() const
{
	std::cout << "{ ";

	for (int i = 0; i <= this->maxNumber; i++)
	{
		uint8_t occurrences = this->getNumberOccurrences(i);

		if (occurrences != 0)
		{
			for (int j = 0; j < occurrences; j++)
			{
				std::cout << i << " ";
			}
		}
	}

	std::cout << "}" << std::endl;
}

void MultiSet::printMultiSetMemoryRepresentation() const
{
	for (int i = 0; i < this->size; i++)
	{
		customFunctions::printNumberInBinary(this->buckets[i]);
		std::cout << " ";
	}

	std::cout << std::endl;
}

void MultiSet::serialize(const char* fileName) const
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

	this->writeInFile(ofs);
}

void MultiSet::deserialize(const char* fileName)
{
	if (!fileName)
	{
		throw std::invalid_argument("Empty file name!");
	}

	std::ifstream ifs(fileName, std::ios::binary);

	if (!ifs.is_open())
	{
		throw std::runtime_error("File can't be open!");
	}

	this->readFromFile(ifs);
}

MultiSet intersection(const MultiSet& lhs, const MultiSet& rhs)
{
	unsigned upperBound = std::min(lhs.getMaxNumber(), rhs.getMaxNumber());
	uint8_t neededBits = std::min(lhs.getBitsUsage(), rhs.getBitsUsage());
	MultiSet result(upperBound, neededBits);

	for (int i = 0; i < result.getMaxNumber(); i++)
	{
		uint8_t lhsCurrOccurr = lhs.getNumberOccurrences(i);
		uint8_t rhsCurrCccurr= rhs.getNumberOccurrences(i);

		if (lhsCurrOccurr && rhsCurrCccurr)
		{
			customFunctions::addNumberNTimes(result, i, std::min(lhsCurrOccurr, rhsCurrCccurr));
		}
	}

	return result;
}

MultiSet difference(const MultiSet& lhs, const MultiSet& rhs)
{
	unsigned upperBound = lhs.getMaxNumber();
	uint8_t neededBits = lhs.getBitsUsage();
	MultiSet result(upperBound, neededBits);

	for (int i = 0; i < result.getMaxNumber(); i++)
	{
		int8_t lhsCurrOccurr = lhs.getNumberOccurrences(i);
		int8_t rhsCurrCccurr = rhs.getNumberOccurrences(i);

		if (lhsCurrOccurr && rhsCurrCccurr && lhsCurrOccurr > rhsCurrCccurr)
		{
			customFunctions::addNumberNTimes(result, i, lhsCurrOccurr - rhsCurrCccurr);
		}
	}

	return result;
}

MultiSet complement(const MultiSet& multiSet)
{
	MultiSet result(multiSet.getMaxNumber(), multiSet.getBitsUsage());

	for (int i = 0; i <= result.getMaxNumber(); i++)
	{
		uint8_t occurrences = multiSet.getNumberOccurrences(i);

		customFunctions::addNumberNTimes(result, i, result.getMaxNumberOccurrences() - occurrences);
	}

	return result;
}

void MultiSet::writeInFile(std::ofstream& ofs) const
{
	ofs.write((const char*)&this->bitsUsage, sizeof(this->bitsUsage));
	ofs.write((const char*)&this->maxNumber, sizeof(this->maxNumber));
	ofs.write((const char*)this->buckets, this->size * sizeof(bucketSize));
}

void MultiSet::readFromFile(std::ifstream& ifs)
{
	this->free();

	uint8_t bits = 0;
	int number = 0;

	ifs.read((char*)&bits, sizeof(this->bitsUsage));
	this->setBitsUsage(bits);
	ifs.read((char*)&number, sizeof(this->maxNumber));
	this->setMaxNumber(number);

	this->size = (this->maxNumber + 1) * this->bitsUsage / this->bucketSize + 1;
	this->buckets = new uint8_t[size];
	ifs.read((char*)this->buckets, size * sizeof(this->bucketSize));
}