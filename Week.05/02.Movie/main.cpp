#include <iostream>
#include "MovieSchedule.h"

int main() {
    // Create a few movie objects
    Movie movie1("The Shawshank Redemption", "Frank Darabont", 142, (uint8_t)Genre::Drama);
    Movie movie2("The Godfather", "Francis Ford Coppola", 175, (uint8_t)Genre::Drama | (uint8_t)Genre::Action);
    Movie movie3("The Dark Knight", "Christopher Nolan", 152, (uint8_t)Genre::Action | (uint8_t)Genre::Drama);

    // Initialize the movie schedule
    MovieSchedule schedule;

    // Add movies to the schedule
    schedule.addMovie(movie1);
    schedule.addMovie(movie2);
    schedule.addMovie(movie3);

    // Print information about a specific movie
    std::cout << "Printing information for a specific movie:" << std::endl;
    schedule.printMovieInfo("The Dark Knight");

    // Print the total minutes of watching
    unsigned totalMinutes = schedule.getTotalMinutesOfWatching();
    std::cout << "Total minutes of watching: " << totalMinutes << " minutes" << std::endl;

}