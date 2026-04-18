#pragma once
#include "Movie.h"
#include <vector>

class MovieManager {
private:
    std::vector<Movie> movies;
    std::vector<Rating> ratings;
    int currentMovieId = 1;

public:
    int setReleaseYear(int ReleaseYear);
    void addMovie();
    void findByTitle() const;
    void printAllMovies() const;
    void sortByRating();
    void addRating(int userId); 
    void ratingByMovie() const;
    bool isExistingMovie(int id) const;
};

class UserManager {
private:
    std::vector<User> users;
    int currentUserId = 1;

public:
    void addUser();
    void printAllUsers() const;
    bool isExistingUser(int id) const;
};
