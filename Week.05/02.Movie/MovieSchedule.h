#pragma once
#include "Movie.h";

constexpr size_t MAX_COUNT_MOVIES = 10;
constexpr unsigned MINUTES_IN_HOUR = 60;
constexpr unsigned MINUTES_IN_DAY = 24 * 60;

class MovieSchedule
{
private:
	size_t count = 0;
	Movie moviesList[MAX_COUNT_MOVIES];

public:
	MovieSchedule() = default;
	MovieSchedule(size_t count, Movie* moviesList);

	size_t getMoviesCount() const;
	const Movie* getMoviesList() const;

	void setMovies(Movie* movieList, size_t count);

	void addMovie(const Movie& movie);
	void printMovieInfo(const char* name) const;

	unsigned getTotalMinutesOfWatching() const;
};