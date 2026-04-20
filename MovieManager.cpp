#include "Manager.h"
#include "Movie.h"
#include <iostream>
#include <algorithm>

void MovieManager::addMovie() {
    std::string title, genre;
    int year;
    std::cout << "영화 제목: ";
    std::getline(std::cin, title);
    std::cout << "장르: ";
    std::getline(std::cin, genre);
    std::cout << "출시 연도: ";
    std::cin >> year;
    
    if (year < 1888 || year > 2100) {
        std::cout << "연도는 1888~2100 사이여야 합니다.\n";
        return;
    }
    else {
        movies.push_back(Movie(currentMovieId++, title, genre, year));
        std::cout << "영화가 추가되었습니다. (ID: " << currentMovieId - 1 << ")\n";
    }
}

void MovieManager::findByTitle() {

}

void MovieManager::printAllMovies() {
    
}

void MovieManager::sortByRating() {

}

void MovieManager::addRating() {

}

void MovieManager::ratingByMovie() {

}

bool MovieManager::isExistingMovie(int id) {

}