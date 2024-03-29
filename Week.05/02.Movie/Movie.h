#pragma once
#include <cstdint>;

enum class Genre {
	Action = 1,
	Comoedy = 2,
	Drama = 4,
	Fantasy = 8,
	Horror = 16,
	Mystery = 32,
	Romance = 64,
	Undefined = 128
};

const char* getGenreName(Genre genre);

class Movie
{
private:
	char* name = nullptr;
	char* director = nullptr;
	unsigned  duration = 0;
	uint8_t genres = 0;

	void free();
	void copyFrom(const Movie& other);

public:
	Movie() = default;
	Movie(const char* name, const char* director, unsigned duration, uint8_t genres);

	const char* getName() const;
	const char* getDirector() const;
	unsigned getDuration() const;

	void setName(const char* name);
	void setDirector(const char* director);
	void setDuration(unsigned duration);

	void addGenre(Genre genre);
	void removeGenre(Genre genre);
	void printInfo();

	Movie& operator=(const Movie& other);

	~Movie();
};