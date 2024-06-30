#pragma once
#include <cstdint>
#include <iostream>;
#include <fstream>;

#define powerOfTwo(n) (1 << n)

class MultiSet {
private:
	unsigned maxNumber = 0;
	unsigned size = 1;
	uint8_t maxNumberOccurrences = 1;
	uint8_t bitsUsage = 1;
	uint8_t* buckets = nullptr;

	void free();
	void copyFrom(const MultiSet& other);

	void writeInFile(std::ofstream& ofs) const;
	void readFromFile(std::ifstream& ifs);

	unsigned getBucketIndex(unsigned element) const;
	unsigned getElementStartBitIndex(unsigned element) const;

	void setBitsUsage(uint8_t number);
	void setMaxNumber(int number);

public:
	static const uint8_t bucketSize;

	MultiSet() = default;

	unsigned getMaxNumber() const;
	uint8_t getBitsUsage() const;
	uint8_t getMaxNumberOccurrences() const;

	MultiSet(int n, uint8_t k);
	MultiSet(const MultiSet& other);
	MultiSet& operator=(const MultiSet& other);
	~MultiSet();

	void addNumber(unsigned element);
	uint8_t getNumberOccurrences(unsigned element) const;

	void printMultiSet() const;
	void printMultiSetMemoryRepresentation() const;

	void serialize(const char* fileName) const;
	void deserialize(const char* fileName);
};

MultiSet intersection(const MultiSet& lhs, const MultiSet& rhs);
MultiSet difference(const MultiSet& lhs, const MultiSet& rhs);
MultiSet complement(const MultiSet& multiSet);