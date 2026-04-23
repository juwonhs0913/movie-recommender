#include "Manager.h"
#include <iostream>
#include <algorithm>

MovieManager::MovieManager() {}

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

void MovieManager::findByTitle() const {
    std::string title;
    bool found = false;

    std::cout << "찾을 영화를 입력하세요: ";
    std::getline(std::cin, title);

    for (const Movie& m : movies) {
        if (m.getTitle().find(title) != std::string::npos) {
            std::cout << m << "\n";
            found = true;
        }
    }
    if (!found) std::cout << "검색 결과가 없습니다.\n";
}

void MovieManager::printAllMovies() const {
    if (movies.empty()) {
        std::cout << "등록된 영화가 없습니다.\n";
        return;
    }
    for (const Movie& m : movies) std::cout << m << "\n";
    std::cout << "총 " << movies.size() << "편\n";
}

void MovieManager::sortByRating() const {
    if (movies.empty()) {
        std::cout << "등록된 영화가 없습니다.\n";
        return;
    }
    std::vector<Movie> sorted = movies;
    std::sort(sorted.begin(), sorted.end(), [](const Movie& a, const Movie& b) {
    return a.getAverageRating() > b.getAverageRating();
});
    for (const Movie& m : sorted) std::cout << m << "\n";
}

bool MovieManager::isExistingMovie(int movieId) const {
    for (const Movie& m : movies)
        if (m.getId() == movieId) return true;
    return false;
}

void MovieManager::addRating(const UserManager& u_manager) {
    int userId;
    std::cout << "사용자 ID 입력: ";
    std::cin >> userId;
    std::cin.ignore();

    if (!u_manager.isExistingUser(userId)) {
        std::cout << "존재하지 않는 사용자입니다.\n";
        return;
    }

    int movieId;
    std::cout << "영화 ID 입력: ";
    std::cin >> movieId;
    std::cin.ignore();

    if (!isExistingMovie(movieId)) {
        std::cout << "존재하지 않는 영화 ID입니다.\n";
        return;
    }

    double score;
    std::cout << "평점 (0.0~5.0): ";
    std::cin >> score;
    std::cin.ignore();

    if (score < 0.0 || score > 5.0) {
        std::cout << "평점은 0.0~5.0 사이여야 합니다.\n";
        return;
    }

    for (Movie& m : movies) {
        if (m.getId() == movieId) {
            m.addRating(score);
            std::cout << "평점이 등록되었습니다.\n";
            return;
        }
    }
}

void MovieManager::ratingByMovie() const {
    int movieId;
    std::cout << "영화의 ID를 입력하세요: ";
    std::cin >> movieId;

    if (!isExistingMovie(movieId)) {
        std::cout << "존재하지 않는 영화 ID입니다.\n";
        return;
    }
    for (const Movie& m : movies) {
        if (m.getId() == movieId) {
            std::cout << m;
            return;
        }
    }
}