#include "MovieManager.h"
#include <iostream>
#include <algorithm>
#include <fstream>
#include <sstream>

MovieManager::MovieManager() : nextId(1) {}

void MovieManager::addMovie(const std::string& title,
                             const std::string& genre, int year) {
    Movie m(nextId, title, genre, year);
    if(m.setReleaseYear(year)) {
        movies.push_back(m);
        std::cout << "ID:" << nextId++ << " [" << title << "]가 추가되었습니다.\n";
    }
    else{
        std::cout << "유효하지 않은 연도 입니다." << std::endl;
    }
}

void MovieManager::printAll() const {
    if (movies.empty()) {
        std::cout << "등록된 영화가 없습니다.\n";
        return;
    }
    for (const Movie& m : movies) std::cout << m << "\n";
    std::cout << "총 " << movies.size() << "편\n";
}

std::vector<Movie> MovieManager::SortByRating() const {
    if (movies.empty()) {
        std::cout << "등록된 영화가 없습니다.\n";
        return {};
    }

    std::vector<Movie> sorted = movies;
    std::sort(sorted.begin(), sorted.end(),
              [](const Movie& a, const Movie& b) {
                  return a.getAverageRating() > b.getAverageRating();
              });

    return sorted;
}


void MovieManager::searchByTitle(const std::string& title) const {
    bool found = false;
    for (const Movie& m : movies) {
        if (m.getTitle().find(title) != std::string::npos) {
            std::cout << m << "\n";
            found = true;
        }
    }
    if (!found) {
        std::cout << "검색 결과가 없습니다.\n";
    }
}

Movie* MovieManager::findById(int id) {
    for (Movie& m : movies) {
        if (m.getId() == id) return &m;
    }
    return nullptr;
}

const std::vector<Movie>& MovieManager::getMovies() const {
    return movies;
}

void MovieManager::loadFromFile(const std::string& filename) {
    std::ifstream file(filename);          
    if (!file.is_open()) {                 
        std::cerr << "Error: " << filename << " 을 열 수 없습니다.\n";
        return;
    }

    std::string line;
    std::getline(file, line);              

    while (std::getline(file, line)) {    
        std::stringstream ss(line);
        std::string token;

        std::getline(ss, token, ','); int            id = std::stoi(token);
        std::getline(ss, token, ','); std::string title = token;
        std::getline(ss, token, ','); std::string genre = token;
        std::getline(ss, token, ','); int          year = std::stoi(token);

        Movie m(id, title, genre, year);     
        movies.push_back(m);

        if (id >= nextId) nextId = id + 1;
    }

    file.close();
    std::cout << filename << " 로드 완료: " << size() << "건\n";
}

void MovieManager::saveToFile(const std::string& filename) const {
    std::ofstream file(filename);          
    if (!file.is_open()) {
        std::cerr << "Error: " << filename << " 저장 실패\n";
        return;
    }

    file << "id,title,genre,year\n";

    for (const Movie& m : movies) {
        file << m.getId()            << ","
             << m.getTitle()         << ","
             << m.getGenre()         << ","
             << m.getReleaseYear()   << "\n";
    }

    file.close();
    std::cout << filename << " 저장 완료: " << size() << "건\n";
}