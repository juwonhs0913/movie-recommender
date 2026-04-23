#pragma once
#include "Movie.h"
#include <vector>
#include <string>

class UserManager {
private:
    std::vector<User> users;
    int currentUserId = 1;
public:
    UserManager();
    void addUser();
    void printAllUsers() const;     
    bool isExistingUser(int userId) const;    
};

class MovieManager {
private:
    std::vector<Movie> movies;
    int currentMovieId = 1;
public:
    MovieManager();

    void addMovie();
    void findByTitle() const;       
    void printAllMovies() const;    
    void sortByRating() const;      
    bool isExistingMovie(int movieId) const;  
    void ratingByMovie() const;  
    void addRating(const UserManager& u_manager);
};

