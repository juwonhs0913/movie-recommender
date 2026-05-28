#include "Recommender.h"
#include <iostream>
#include <algorithm>
#include <cstdlib>   
#include <set>       
#include <map>       

Recommender::Recommender(MovieManager& mm, UserManager& um, RatingManager& rm)
    : movieMgr(mm), userMgr(um), ratingMgr(rm) {}

int Recommender::SimilarityCalculate(const std::vector<Rating>& user1, const std::vector<Rating>& user2) const {
    int commonCount  = 0;   // 공통으로 본 영화 수
    int scoreDiffSum = 0;   // 평점 차이의 합
    // 이중 반복문: user1의 모든 평점 × user2의 모든 평점
    for (const Rating& r1 : user1) {
        for (const Rating& r2 : user2) {
            if (r1.getMovieId() == r2.getMovieId()) {
                commonCount++;
                scoreDiffSum += std::abs(r1.getScore() - r2.getScore());
            }
        }
    }

    if (commonCount == 0) return -100;

    return commonCount * 10 - scoreDiffSum;
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

std::vector<int> Recommender::getTopRatedMovies(int n) const {
    std::vector<int> result;

    std::vector<Movie> sortedMovies = movieMgr.SortByRating(); 
    for (int i = 0; i < n; i++) {
        result.push_back(sortedMovies[i].getId());
    }

    return result;
}

std::vector<int> Recommender::recommend(int targetUserId, int n) const {

    const std::vector<Rating>& myRatings = ratingMgr.findById(targetUserId);
    if (myRatings.empty()) {
        std::cout << "[" << targetUserId << " ]" << "사용자의 평점 데이터가 없습니다." << std::endl
                    << "전체 평점 TOP-" << n << " 영화를 추천합니다." << std::endl;
        return getTopRatedMovies(n);
    }

    std::vector<std::pair<int,int>> similarUsers = findSimilarUsers(targetUserId, 5);

    if (similarUsers.empty()) {
        std::cout << "취향이 비슷한 사용자가 없습니다." << std::endl
                  << "전체 평점 TOP-" << n << " 영화를 추천합니다." << std::endl;
        return getTopRatedMovies(n);
    }

    std::set<int> myMovieIds;
    for (const Rating& r : myRatings) {
        myMovieIds.insert(r.getMovieId());
    }

    std::map<int, double> weightedSum;   
    std::map<int, double> weightSum;     

    for (const std::pair<int,int>& su : similarUsers) {
        int userId    = su.first;
        int simScore  = su.second;

        const std::vector<Rating>& otherRatings = ratingMgr.findById(userId);

        for (const Rating& r : otherRatings) {
            int    movieId = r.getMovieId();
            double rating  = r.getScore();

            if (myMovieIds.find(movieId) == myMovieIds.end()) {
                weightedSum[movieId] += simScore * rating; 
                weightSum[movieId]   += simScore;          
            }
        }
    }

    std::vector<std::pair<int,int>> candidates;
    for (const auto& temp : weightedSum) {
        int movieId = temp.first;
        double weightedAvg = temp.second / weightSum[movieId];
        int scoreInt = weightedAvg * 1000; 
        
        candidates.push_back({movieId, scoreInt});         
    }

    std::sort(candidates.begin(), candidates.end(),
        [](const std::pair<int,int>& a, const std::pair<int,int>& b) {
            return a.second > b.second;
        });

    std::vector<int> result;
    int limit = candidates.size(); 
    
    if (limit > n) {
        limit = n;
    }
    
    for (int i = 0; i < limit; i++) {
        result.push_back(candidates[i].first);
    }
    return result;
}