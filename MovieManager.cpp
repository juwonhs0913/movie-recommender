#include "Manager.h"
#include "Movie.h"
#include <iostream>
#include <algorithm>

int MovieManager::setReleaseYear(int year) {
    if (year < 1888 || year > 2100) {
        std::cout << "유효하지 않은 연도입니다.\n";
        return 0;
    }
    return year;
}

void MovieManager::addMovie() {
    std::string title, genre;
    int year;
    std::cout << "영화 제목: ";
    std::getline(std::cin, title);
    std::cout << "장르: ";
    std::getline(std::cin, genre);
    std::cout << "출시 연도: ";
    std::cin >> year;
    
    year = setReleaseYear(year);
    if(year != 0) {
        movies.push_back(Movie(currentMovieId++, title, genre, year));
        std::cout << "영화가 추가되었습니다. (ID: " << currentMovieId - 1 << ")\n";
    }
}

void MovieManager::findByTitle() const {

}

void MovieManager::printAllMovies() const {
    
}

void MovieManager::sortByRating() {

}

void MovieManager::addRating(int userId) {

}

void MovieManager::ratingByMovie() const {

}

bool MovieManager::isExistingMovie(int id) const {

}