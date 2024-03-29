#include "MovieSchedule.h";
#include <string.h>;
#include<iostream>;

MovieSchedule::MovieSchedule(size_t count, Movie* moviesList)
{
	this->setMovies(moviesList, count);
}

size_t MovieSchedule::getMoviesCount() const
{
	return this->count;
}
const Movie* MovieSchedule::getMoviesList() const
{
	return this->moviesList;
}

void MovieSchedule::setMovies(Movie* moviesList, size_t count)
{
	if (count > MAX_COUNT_MOVIES)
	{
		return;
	}

	for (int i = 0; i < count; i++)
	{
		this->moviesList[i] = moviesList[i];
	}

	this->count = count;
}

void MovieSchedule::addMovie(const Movie& movie)
{
	if (this->count >= MAX_COUNT_MOVIES)
	{
		return;
	}

	this->moviesList[this->count] = movie;
	this->count++;
}
void MovieSchedule::printMovieInfo(const char* name) const
{
	unsigned minutes = 0;

	for (int i = 0; i < this->count; i++)
	{
		if (strcmp(this->moviesList[i].getName(), name) == 0)
		{
			if (minutes > MINUTES_IN_DAY)
			{
				minutes -= MINUTES_IN_DAY;
			}

			std::cout << "<" << this->moviesList[i].getName() << "> - " << "<" << minutes / 60 << ">:<" << minutes % 60 << ">" << std::endl;
		}
		else
		{
			minutes += this->moviesList[i].getDuration();
		}
	}
}

unsigned MovieSchedule::getTotalMinutesOfWatching() const
{
	unsigned minutes = 0;

	for (int i = 0; i < this->count; i++)
	{
		minutes += this->moviesList[i].getDuration();
	}

	return minutes;
}

