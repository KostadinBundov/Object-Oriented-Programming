#include <iostream>;
#include "Movie.h";
#pragma warning (disable : 4996) 


Movie::Movie(const char* name, const char* director, unsigned duration, uint8_t genres)
{
	this->setName(name);
	this->setDirector(director);
	this->setDuration(duration);
	this->setGenres(genres);
}

const char* Movie::getName() const
{
	return this->name;
}
const char* Movie::getDirector() const
{
	return this->director;
}
unsigned Movie::getDuration() const
{
	return this->duration;
}
uint8_t Movie::getGenres() const
{
	return this->genres;
}

void Movie::setName(const char* name)
{
	delete[] this->name; 
	this->name = new char[strlen(name) + 1];
	strcpy(this->name, name);
}
void Movie::setDirector(const char* director)
{
	delete[] this->director;
	this->director = new char[strlen(director) + 1];
	strcpy(this->director, director);
}
void Movie::setDuration(unsigned duration)
{
	this->duration = duration;
}
void Movie::setGenres(uint8_t genres)
{
	if (this->genres > 64 && this->genres != 128)
	{
		return;
	}

	this->genres = genres;
}

void Movie::addGenre(Genre genre)
{
	if(this->genres == 128)
	{
		return;
	}

	if (!(this->genres & (uint8_t)genre))
	{
		this->genres |= (uint8_t)genre;
	}
}
void Movie::removeGenre(Genre genre)
{
	if (this->genres & 1)
	{
		this->genres ^= (uint8_t)genre;
	}
}
void Movie::printInfo()
{
	std::cout << this->name << std::endl;
	std::cout << this->director << std::endl;
	std::cout << this->duration << std::endl;

	for (int i = 1; i <= 128; i <<= 1)
	{
		if (this->genres & (uint8_t)i)
		{
			std::cout << getGenreName((Genre)i) << "/";
		}
	}

	std::cout << std::endl;
}

void Movie::free()
{
	delete[] this->name;
	delete[] this->director;

	this->name = nullptr;
	this->director = nullptr;
	this->duration = 0;
	this->genres = 0;
}

void Movie::copyFrom(const Movie& other)
{
	this->name = new char[strlen(other.name) + 1];
	strcpy(this->name, other.name);
	this->director = new char[strlen(other.director) + 1];
	strcpy(this->director, other.director);

	this->duration = other.duration;
	this->genres = other.genres;
}

Movie& Movie::operator=(const Movie& other)
{
	if (this != &other)
	{
		free();
		copyFrom(other);
	}

	return *this;
}

Movie::~Movie()
{
	this->free();
}

const char* getGenreName(Genre genre)
{
	switch (genre)
	{
	case Genre::Action:
		return "Action";
	case Genre::Comoedy:
		return "Comedy";
	case Genre::Drama:
		return "Drama";
	case Genre::Fantasy:
		return "Fantasy";
	case Genre::Horror:
		return "Horror";
	case Genre::Mystery:
		return "Mystery";
	case Genre::Romance:
		return "Romance";
	case Genre::Undefined:
		return "Undefined";
	}
}