#include "Recommender.h"
#include <iostream>
#include <algorithm>
#include <cmath>     
#include <set>       
#include <map>       

namespace {
    constexpr int NO_COMMON_MOVIE = -100;
    constexpr int COMMON_MOVIE_WEIGHT = 10;
}

Recommender::Recommender(MovieManager& mm, UserManager& um, RatingManager& rm)
    : movieMgr(mm), userMgr(um), ratingMgr(rm) {}

int Recommender::SimilarityCalculate(const std::vector<Rating>& user1, const std::vector<Rating>& user2) const {
    int commonCount  = 0;   // 공통으로 본 영화 수
    
    // 기존에 int였으나 평점(score)이 double이므로 누적 값도 double로 수정
    double scoreDiffSum = 0.0;   

    // 이중 반복문: user1의 모든 평점 × user2의 모든 평점
    for (const Rating& r1 : user1) {
        for (const Rating& r2 : user2) {
            if (r1.getMovieId() == r2.getMovieId()) {
                commonCount++;
                scoreDiffSum += std::abs(r1.getScore() - r2.getScore());
            }
        }
    }

    if (commonCount == 0) return NO_COMMON_MOVIE;

    return (commonCount * COMMON_MOVIE_WEIGHT) - scoreDiffSum;
}

std::vector<std::pair<int,int>> Recommender::findSimilarUsers(int targetUserId, int k) const {
    std::vector<std::pair<int,int>> similarities;

    const std::vector<Rating>& myRatings = ratingMgr.findById(targetUserId);

    for (const User& other : userMgr.getUsers()) {
        if (other.getId() == targetUserId) continue;

        const std::vector<Rating>& otherRatings = ratingMgr.findById(other.getId());

        int sim = SimilarityCalculate(myRatings, otherRatings);

        if (sim > 0) {
            similarities.push_back({other.getId(), sim}); 
        }
    }

    std::sort(similarities.begin(), similarities.end(),
        [](const std::pair<int,int>& a, const std::pair<int,int>& b) {
            return a.second > b.second;
        });

    int limit = similarities.size();
    
    if (limit > k) {
        limit = k;
    }

    similarities.resize(limit);

    return similarities;
}

std::set<int> Recommender::getWatchedMovieIds(const std::vector<Rating>& ratings) const {
    std::set<int> watched;
    for (const Rating& r : ratings) {
        watched.insert(r.getMovieId());
    }
    return watched;
}

std::vector<std::pair<int, double>> Recommender::calculateCandidates(
    const std::vector<std::pair<int, int>>& similarUsers, 
    const std::set<int>& myWatchedMovieIds) const {
    
    std::map<int, double> weightedSum;
    std::map<int, double> weightSum;

    for (const auto& su : similarUsers) {
        const std::vector<Rating>& otherRatings = ratingMgr.findById(su.first);
        for (const Rating& r : otherRatings) {
            if (myWatchedMovieIds.find(r.getMovieId()) == myWatchedMovieIds.end()) {
                weightedSum[r.getMovieId()] += su.second * r.getScore();
                weightSum[r.getMovieId()] += su.second;
            }
        }
    }

    std::vector<std::pair<int, double>> candidates;
    for (const auto& entry : weightedSum) {
        candidates.push_back({entry.first, entry.second / weightSum[entry.first]});
    }
    return candidates;
}

std::vector<int> Recommender::extractTopN(std::vector<std::pair<int, double>>& candidates, int n) const {
    std::sort(candidates.begin(), candidates.end(),
        [](const auto& a, const auto& b) { return a.second > b.second; });

    std::vector<int> result;
    int limit = std::min((int)candidates.size(), n);
    for (int i = 0; i < limit; i++) {
        result.push_back(candidates[i].first);
    }
    return result;
}

std::vector<int> Recommender::recommend(int targetUserId, int n) const {
    const std::vector<Rating>& myRatings = ratingMgr.findById(targetUserId);
    
    if (myRatings.empty()) {
        std::cout << "사용자 데이터 부족. 전체 상위 영화를 추천합니다." << std::endl;
        return movieMgr.getTopN(n);
    }

    auto similarUsers = findSimilarUsers(targetUserId, 5);
    if (similarUsers.empty()) {
        return movieMgr.getTopN(n);
    }

    auto watchedIds = getWatchedMovieIds(myRatings);
    auto candidates = calculateCandidates(similarUsers, watchedIds);

    return extractTopN(candidates, n);
}