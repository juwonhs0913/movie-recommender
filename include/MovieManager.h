#pragma once
#include "BaseManager.h"
#include "Movie.h"
#include <vector>
#include <string>

class MovieManager : public BaseManager{
private:
    std::vector<Movie> movies;
    int nextId;

public:
    MovieManager();
    

    void addMovie(const std::string& title, const std::string& genre, int year);
    void printAll() const;
    void SortByRating();       
    void searchByTitle(const std::string& keyword) const;
    std::vector<int> getTopN(int n);

    Movie* findById(int id);
    const std::vector<Movie>& getMovies() const;
    
    void loadFromFile(const std::string& filename) override;
    void saveToFile(const std::string& filename) const override;
    int size() const override {return movies.size();}
};
