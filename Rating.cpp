#include "Movie.h"
#include <iostream>

Rating::Rating(int userid, int movieid, double s)
    : userId(userid), movieId(movieid), score(s) {
        if(score < 0 || score > 5) {
            std::cout << userId <<"님의 평점은 올바르지 않은 형식입니다. 0~5점 사이로 작성하세요." << std::endl;
            score = 0.0; //유효성 검사 후 유효하지 않을 시 0.0 세팅
        }
    }

int Rating::getUserId() const {return userId; }
int Rating::getMovieId() const {return movieId; }
double Rating::getScore() const {return score; }

void Rating::display() const {
    std::cout << "USERID: " << userId << ", MOVIE ID: " << movieId << ", 평점: " << score << std::endl;
}