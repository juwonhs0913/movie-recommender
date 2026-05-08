#pragma once
#include "Movie.h"
#include <vector>
#include <string>

class MovieManager {
private:
    std::vector<Movie> movies;
    int nextId;

public:
    MovieManager();

    void addMovie(const std::string& title, const std::string& genre, int year);
    void printAll() const;
    void SortByRating() const;        
    void searchByTitle(const std::string& keyword) const;

    Movie* findById(int id);
    const std::vector<Movie>& getMovies() const;
    
    void loadFromFile(const std::string& filename);
    void saveToFile(const std::string& filename) const;
};
