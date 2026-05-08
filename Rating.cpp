#include "Rating.h"
#include <iostream>

Rating::Rating(int userid, int movieid, double s)
    : userId(userid), movieId(movieid), score(s) {
        if (score < 0 || score > 5) {
            std::cout << "올바르지 않은 평점입니다. 0~5점 사이로 작성하세요." << std::endl;
            score = -1;
        }
    }

int    Rating::getUserId()  const { return userId; }
int    Rating::getMovieId() const { return movieId; }
double Rating::getScore()   const { return score; }

void Rating::display() const {
    std::cout << "USERID: " << userId
              << ", MOVIE ID: " << movieId
              << ", 평점: " << score << std::endl;
}
