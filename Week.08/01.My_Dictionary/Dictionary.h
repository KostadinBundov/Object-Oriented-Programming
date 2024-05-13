#pragma once
#include "MyString.h"

struct Pair
{
	MyString key;
	MyString value;

	Pair(const MyString& key, const MyString& value) : key(key), value(value) {}
};

class Dictionary
{
private:
	Pair** data = nullptr;
	size_t size;
	size_t capacity;

	void copyFrom(const Dictionary& other);
	void moveFrom(Dictionary&& other);
	void free();

	void resize(size_t newCapacity);
	Dictionary(size_t size);

	int findIndexToInsert(const MyString& word) const;

	void shiftElementsAfterRmoving(size_t index);
	void shiftElementsBeforeAdding(size_t index);

	int getWordIndex(const MyString& word);

public:
	Dictionary();
	Dictionary(const Dictionary& other);
	Dictionary(Dictionary&& other);

	Dictionary& operator=(const Dictionary& other);
	Dictionary& operator=(Dictionary&& other);	

	~Dictionary();

	void add(const MyString& word, const MyString& description);
	void remove(const MyString& word, const MyString& description);
	void print() const;
	MyString operator()(const MyString& word);
	Dictionary& operator+=(const Dictionary& other);

	friend Dictionary operator+(const Dictionary& lhs, const Dictionary& rhs);
};