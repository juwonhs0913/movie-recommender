#include "RatingManager.h"
#include <iostream>
#include <algorithm>
#include <fstream>
#include <sstream>

RatingManager::RatingManager() {}

void RatingManager::addRating(int userId, int movieId, double score,
                               MovieManager& movieMgr, const UserManager& userMgr) {
    const User* user = userMgr.findById(userId);
    if (user == nullptr) {
        std::cout << "존재하지 않는 사용자 ID입니다.\n";
        return;
    }

    Movie* movie = movieMgr.findById(movieId);
    if (movie == nullptr) {
        std::cout << "존재하지 않는 영화 ID입니다.\n";
        return;
    }

    Rating rating(userId, movieId, score);

    if (rating.getScore() != -1) {
        movie->addRating(score);
        ratings.push_back(rating);
        std::cout << "[" << user->getName() << "]님이 영화 ["
                  << movie->getTitle() << "]에 " << score << "점을 입력했습니다.\n";
    }
}

void RatingManager::ratingByMovie(int movieId, MovieManager& movieMgr) const {
    Movie* movie = movieMgr.findById(movieId);
    if (movie == nullptr) {
        std::cout << "존재하지 않는 영화 ID입니다.\n";
        return;
    }

    for (const Movie& m : movieMgr.getMovies()) {
        if (m.getId() == movieId) {
            std::cout << m;
            return;
        }
    }
}


std::vector<Rating> RatingManager::findById(int userId) const {
    std::vector<Rating> result;
    for (const Rating& r : ratings) {
        if (r.getUserId() == userId) {
            result.push_back(r);
        }
    }
    return result;
}

const std::vector<Rating>& RatingManager::getRatings() const {
    return ratings;
}

std::vector<int> RatingManager::getAllUserId() const {
    std::vector<int> id;
    for (const Rating& r : ratings) {
        id.push_back(r.getUserId());
    }
    return id;
}


void RatingManager::loadFromFile(const std::string& filename) {
    std::ifstream file(filename);         
    if (!file.is_open()) {                
        std::cerr << "Error: " << filename << " 을(를) 열 수 없습니다.\n";
        return;
    }

    std::string line;
    std::getline(file, line);              

    while (std::getline(file, line)) {
        if (!line.empty() && line.back() == '\r') line.pop_back();
             
        std::stringstream ss(line);
        std::string token;

        std::getline(ss, token, ','); int    userId  = std::stoi(token);
        std::getline(ss, token, ','); int    movieId = std::stoi(token);
        std::getline(ss, token, ','); double score   = std::stod(token);


        Rating r(userId, movieId, score);
        ratings.push_back(r);

    }

    file.close();
    std::cout << filename << " 로드 완료: " << size() << "건\n";
}

void RatingManager::saveToFile(const std::string& filename) const {
    std::ofstream file(filename);
    if (!file.is_open()) {
        std::cerr << "Error: " << filename << " 저장 실패\n";
        return;
    }

    file << "userId,movieId,score\n";

    for (const Rating& r : ratings) {
        file << r.getUserId()  << ","
             << r.getMovieId() << ","
             << r.getScore()   << "\n";
    }

    file.close();
    std::cout << filename << " 저장 완료: " << size() << "건\n";
}