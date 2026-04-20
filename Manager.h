#pragma once
#include "Movie.h"
#include <vector>
#include <string>

class MovieManager {
private:
    std::vector<Movie> movies;
    int currentMovieId = 1;
public:
    MovieManager();

    void addMovie();
    void findByTitle();
    void printAllMovies();                        
    void sortByRating();                         
    bool isExistingMovie(int movieId);          
    void addRating();
    void ratingByMovie();              

};

class UserManager {
private:
    std::vector<User> users;
    int currentUserId = 1;
public:
    UserManager();
    void addUser();
    void printAllUsers();
    bool isExistingUser(int userId);
};