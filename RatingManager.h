#pragma once
#include "Rating.h"
#include "MovieManager.h"
#include "UserManager.h"
#include <vector>

class RatingManager {
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

    void loadFromFile(const std::string& filename);
    void saveToFile(const std::string& filename) const;
};