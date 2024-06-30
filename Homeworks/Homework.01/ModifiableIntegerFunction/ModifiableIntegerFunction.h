#pragma once
#include <iostream>
#include <fstream>;
#include "MultiSet.h";

class ModifiableIntegerFunction 
{
private:

	const static unsigned elementsCount;
	const static unsigned zeroIndex;

	//Динамичен заради бързото препълване на стека
	short* arr = nullptr;
	bool* excludedPoints = nullptr;

	mutable bool isSurjective = true;
	mutable bool isInjective = true;
	mutable bool isModified = true;

	void copyFrom(const ModifiableIntegerFunction& other);
	void free();

	void fillArr(short (*func)(short));
	void initializeArrays();

	ModifiableIntegerFunction composeKTimes(int k) const;
	ModifiableIntegerFunction inverseFunction() const;

	void writeInBinary(std::ofstream& ofs) const;
	void readFromBinary(std::ifstream& ifs);

public:

	ModifiableIntegerFunction() = default;
	ModifiableIntegerFunction(short (*func)(short x));
	ModifiableIntegerFunction(const ModifiableIntegerFunction& other);

	ModifiableIntegerFunction& operator=(const ModifiableIntegerFunction& other);
	~ModifiableIntegerFunction();

	void setResult(short x, short y);
	void excludePoint(short x);

	ModifiableIntegerFunction& operator+=(const ModifiableIntegerFunction& other);
	ModifiableIntegerFunction& operator-=(const ModifiableIntegerFunction& other);
	friend ModifiableIntegerFunction operator+(const ModifiableIntegerFunction&, const ModifiableIntegerFunction&);
	friend ModifiableIntegerFunction operator-(const ModifiableIntegerFunction&, const ModifiableIntegerFunction&);

	ModifiableIntegerFunction operator()(const ModifiableIntegerFunction& func) const;
	ModifiableIntegerFunction operator^(int k) const;

	friend bool operator==(const ModifiableIntegerFunction& lhs, const ModifiableIntegerFunction& rhs);
	friend bool operator!=(const ModifiableIntegerFunction& lhs, const ModifiableIntegerFunction& rhs);
	friend bool operator<(const ModifiableIntegerFunction& lhs, const ModifiableIntegerFunction& rhs);
	friend bool operator<=(const ModifiableIntegerFunction& lhs, const ModifiableIntegerFunction& rhs);
	friend bool operator>(const ModifiableIntegerFunction& lhs, const ModifiableIntegerFunction& rhs);
	friend bool operator>=(const ModifiableIntegerFunction& lhs, const ModifiableIntegerFunction& rhs);

	friend bool operator||(const ModifiableIntegerFunction& lhs, const ModifiableIntegerFunction& rhs);

	bool checkIsSurjective() const;
	bool checkIsInjective() const;
	bool checkIsBijective() const;

	void serializeInFile(const char* fileName) const;
	void deserializeFromFile(const char* fileName);

	void printPointsInInterval(short firstX, short firstY, short secondX, short secondY) const;
};