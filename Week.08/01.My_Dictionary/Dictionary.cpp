#include "Dictionary.h"

void Dictionary::copyFrom(const Dictionary& other)
{
	data = new Pair * [other.capacity] {nullptr};

	for (int i = 0; i < other.size; i++)
	{
		if (other.data[i] != nullptr)
		{
			data[i] = new Pair(other.data[i]->key, other.data[i]->value);
		}
	}

	capacity = other.capacity;
	size = other.size;
}

void Dictionary::moveFrom(Dictionary&& other)
{
	data = other.data;
	other.data = nullptr;

	size = other.size;
	other.size = 0;

	capacity = other.capacity;
	other.capacity = 0;
}

void Dictionary::free()
{
	for (int i = 0; i < capacity; i++)
	{
		delete data[i];
	}

	delete[] data;
}

void Dictionary::resize(size_t newCapacity)
{
	capacity = newCapacity;

	Pair** temporaryData = new Pair * [capacity] {nullptr};

	for (int i = 0; i < size; i++)
	{
		if (data[i] != nullptr)
		{
			temporaryData[i] = new Pair(data[i]->key, data[i]->value);
		}
	}

	delete[] data;
	data = temporaryData;
}

int Dictionary::findIndexToInsert(const MyString& word) const
{
	int start = 0;
	int end = size - 1;

	while (start <= end)
	{
		int index = start + end / 2;

		if (word == data[index]->key)
		{
			return index;
		}
		else if (word < data[index]->key)
		{
			end = index - 1;
		}
		else if (word > data[index]->key)
		{
			start = index + 1;
		}
	}

	return end + 1;
}

void Dictionary::shiftElementsAfterRmoving( size_t index)
{
	for (int i = index; i < capacity; i++)
	{
		data[i] = data[i + 1];
	}

	data[capacity - 1] = nullptr;
}
void Dictionary::shiftElementsBeforeAdding(size_t index)
{
	for (int i = capacity - 1; i > index; i--)
	{
		data[i] = data[i - 1];
	}

	data[index] = nullptr;
}

Dictionary::Dictionary(size_t size)
{
	capacity = size;
	this->size = size;
	data = new Pair * [capacity] {nullptr};
}

Dictionary::Dictionary(const Dictionary& other)
{
	copyFrom(other);
}

Dictionary::Dictionary(Dictionary&& other)
{
	moveFrom(std::move(other));
}

Dictionary::Dictionary()
{
	capacity = 8;
	size = 0;
	data = new Pair * [capacity] {nullptr};
}

Dictionary::~Dictionary()
{
	free();
}

Dictionary& Dictionary::operator=(const Dictionary& other)
{
	if (this != &other)
	{
		free();
		copyFrom(other);
	}

	return *this;
}

Dictionary& Dictionary::operator=(Dictionary&& other)
{
	if (this != &other)
	{
		free();
		moveFrom(std::move(other));
	}

	return *this;
}

int Dictionary::getWordIndex(const MyString& word)
{
	int start = 0;
	int end = size - 1;

	while (start <= end)
	{
		int index = start + end / 2;

		if (word == data[index]->key)
		{
			return index;
		}
		else if (word < data[index]->key)
		{
			end = index - 1;
		}
		else if (word > data[index]->key)
		{
			start = index + 1;
		}
	}

	return -1;
}

void Dictionary::add(const MyString& word, const MyString& description)
{
	if (size == 0)
	{
		data[0] = new Pair(word, description);
		size++;
		return;
	}

	int indexOfWord = getWordIndex(word);

	if (indexOfWord == -1)
	{
		int indexToInsert = findIndexToInsert(word);
		shiftElementsBeforeAdding(indexToInsert);
		data[indexToInsert] = new Pair(word, description);
	}
	else
	{
		data[indexOfWord]->value += description;
	}

	size++;
}

void Dictionary::remove(const MyString& word, const MyString& description)
{
	int indexOfWord = getWordIndex(word);

	if (indexOfWord == -1)
	{
		throw std::invalid_argument("Word isn't in dictionary!");
	}

	delete data[indexOfWord];
	data[indexOfWord] = nullptr;
	shiftElementsAfterRmoving(indexOfWord);

	size--;
}

void Dictionary::print() const
{
	for (int i = 0; i < size; i++)
	{
		std::cout << "Word: ";
		std::cout << data[i]->key << std::endl;

		std::cout << "Description: ";
		std::cout << data[i]->value << std::endl;
	}
}

MyString Dictionary::operator()(const MyString& word)
{
	int indexOfWord = getWordIndex(word);

	if (indexOfWord == -1)
	{
		throw std::invalid_argument("Word isn't in dictionary!");
	}

	MyString result = data[indexOfWord]->value;
	return result;
}
Dictionary& Dictionary::operator+=(const Dictionary& other)
{
	if (size + other.size > capacity)
	{
		resize(size + other.size);
	}

	for (int i = 0; i < other.size; i++)
	{
		data[size + i] = new Pair(other.data[i]->key, other.data[i]->value);
	}
	size += other.size;

	return *this;
}

Dictionary operator+(const Dictionary & lhs, const Dictionary & rhs)
{
	Dictionary res = Dictionary(lhs.size + rhs.size);

	res += lhs;
	res += rhs;

	return res;
}
