#pragma once
#include <vector>
#include <string>
#include <map>
#include <set>
#include "MovieManager.h"
#include "UserManager.h"
#include "RatingManager.h"

class Recommender {
private:
    MovieManager& movieMgr;
    UserManager& userMgr;
    RatingManager& ratingMgr;

    int SimilarityCalculate(const std::vector<Rating>& user1,
                            const std::vector<Rating>& user2) const;

    std::vector<std::pair<int, int>> findSimilarUsers(int targetUserId, int k = 5) const;
    std::vector<int> getTopRatedMovies(int n = 5) const;

    std::set<int> getWatchedMovieIds(const std::vector<Rating>& ratings) const;
    std::vector<std::pair<int, double>> calculateCandidates(
        const std::vector<std::pair<int, int>>& similarUsers, 
        const std::set<int>& myWatchedMovieIds) const;
    std::vector<int> extractTopN(std::vector<std::pair<int, double>>& candidates, int n) const;

public:
    Recommender(MovieManager& mm, UserManager& um, RatingManager& rm);
    std::vector<int> recommend(int targetUserId, int n = 5) const;
};