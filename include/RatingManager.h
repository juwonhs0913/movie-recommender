#pragma once
#include "BaseManager.h"
#include "Rating.h"
#include "MovieManager.h"
#include "UserManager.h"
#include <vector>

class RatingManager : public BaseManager {
private:
    std::vector<Rating> ratings;

public:
    RatingManager();

    void addRating(int userId, int movieId, double score,
                   MovieManager& movieMgr, const UserManager& userMgr);

    void ratingByMovie(int movieId, MovieManager& movieMgr) const;

    std::vector<Rating> findById(int userId) const;
    const std::vector<Rating>& getRatings() const;
    std::vector<int> getAllUserId() const;

    void loadFromFile(const std::string& filename) override;
    void loadFromFile(const std::string& filename, MovieManager& moviemgr); //함수 오버로딩, rating.csv의 평점정보를 사용하기 위함
    void saveToFile(const std::string& filename) const override;
    int size() const override { return ratings.size();}
};