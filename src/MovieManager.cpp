#include "MovieManager.h"
#include <iostream>
#include <algorithm>
#include <fstream>
#include <sstream>
#include <chrono>  
#include <numeric> 
#include <map>     
#include <cctype>  

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

void MovieManager::SortByRating() {
    if (movies.empty()) {
        std::cout << "등록된 영화가 없습니다.\n";
        return ;
    }

    std::sort(movies.begin(), movies.end(),
              [](const Movie& a, const Movie& b) {
                  return a.getAverageRating() > b.getAverageRating();
              });

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

std::vector<int> MovieManager::getTopN(int n) const {
    if (movies.empty()) return {};

    auto sorted = movies; // 복사 (원본 보호)
    int limit = std::min((int)sorted.size(), n);

    std::partial_sort(sorted.begin(), sorted.begin() + limit, sorted.end(),
                      [](const Movie& a, const Movie& b) {
                          return a.getAverageRating() > b.getAverageRating();
                      });

    std::vector<int> topNIds;
    for (int i = 0; i < limit; i++) {
        topNIds.push_back(sorted[i].getId());
    }
    return topNIds;
}

void MovieManager::sortByTitle() {
    if (movies.empty()) {
        std::cout << "등록된 영화가 없습니다.\n";
        return;
    }
    std::sort(movies.begin(), movies.end(),
              [](const Movie& a, const Movie& b) {
                  return a.getTitle() < b.getTitle(); 
              });
}

void MovieManager::sortByYear() {
    if (movies.empty()) {
        std::cout << "등록된 영화가 없습니다.\n";
        return;
    }
    std::sort(movies.begin(), movies.end(),
              [](const Movie& a, const Movie& b) {
                  return a.getReleaseYear() > b.getReleaseYear(); 
              });
}

void MovieManager::sortById() {
    if (movies.empty()) {
        std::cout << "등록된 영화가 없습니다.\n";
        return;
    }
    std::sort(movies.begin(), movies.end(),
              [](const Movie& a, const Movie& b) {
                  return a.getId() < b.getId(); 
              });
}

double MovieManager::getAverageRating() const {
    if (movies.empty()) {
        throw std::runtime_error("영화 데이터가 없습니다.");
    }
    double sum = std::accumulate(
        movies.begin(), movies.end(), 0.0,
        [](double acc, const Movie& m) {
            return acc + m.getAverageRating();
        });
    return sum / static_cast<double>(movies.size());
}

std::map<std::string, double> MovieManager::getAverageRatingByGenre() const {
    std::map<std::string, double> sumByGenre;
    std::map<std::string, int>    countByGenre;

    for (const auto& m : movies) {
        sumByGenre[m.getGenre()]   += m.getAverageRating();
        countByGenre[m.getGenre()]++;
    }

    std::map<std::string, double> avgByGenre;
    for (const auto& [genre, sum] : sumByGenre) {
        avgByGenre[genre] = sum / countByGenre[genre];
    }
    return avgByGenre;
}

std::string MovieManager::getMostPopularGenre() const {
    if (movies.empty()) {
        throw std::runtime_error("영화 데이터가 없습니다.");
    }

    auto avgByGenre = getAverageRatingByGenre();

    auto it = std::max_element(
        avgByGenre.begin(), avgByGenre.end(),
        [](const std::pair<std::string, double>& a,
           const std::pair<std::string, double>& b) {
            return a.second < b.second;
        });
    return it->first;
}

void MovieManager::showStatistics() const {
    while (true) {
        std::cout << "\n=== 통계 메뉴 ===\n";
        std::cout << "   1. 전체 평균 평점\n";
        std::cout << "   2. 장르별 평균 평점\n";
        std::cout << "   3. Top N 영화\n";
        std::cout << "   0. 돌아가기\n";
        std::cout << "선택 > ";

        int choice;
        std::cin >> choice;

        try {
            switch (choice) {
                case 1: {
                    double avg = getAverageRating();
                    std::cout << "전체 평균 평점: " << avg << "\n";
                    break;
                }
                case 2: {
                    auto byGenre = getAverageRatingByGenre();
                    if (byGenre.empty()) {
                        std::cout << "데이터가 없습니다.\n";
                        break;
                    }
                    std::cout << "\n장르별 평균 평점:\n";
                    for (const auto& [genre, avg] : byGenre) {
                        std::cout << "  " << genre << " : " << avg << "\n";
                    }
                    std::string popular = getMostPopularGenre();
                    std::cout << "인기 장르 (장르별 평점 기준): " << popular << "\n";
                    break;
                }
                case 3: {
                    int n;
                    std::cout << "상위 몇 개를 볼까요? ";
                    std::cin >> n;
                    if (n <= 0) {
                        std::cout << "1 이상의 값을 입력하세요.\n";
                        break;
                    }
                    std::vector<int> topIds = getTopN(n);
                    std::cout << "\n=== Top " << topIds.size() << " 영화 ===\n";
                    for (int i = 0; i < (int)topIds.size(); i++) {
                        const Movie* m = findById(topIds[i]);
                        std::cout << (i + 1) << "위  " << *m << "\n";
                    }
                    break;
                }
                case 0:
                    return;
                default:
                    std::cout << "잘못된 선택입니다.\n";
            }
        } catch (const std::exception& e) {
            std::cerr << "오류: " << e.what() << "\n";
        }
    }
}

Movie* MovieManager::findById(int id) {
    for (Movie& m : movies) {
        if (m.getId() == id) return &m;
    }
    throw std::out_of_range("영화ID가 존재하지 않습니다.");
}

const Movie* MovieManager::findById(int id) const {
    for (const Movie& m : movies) {
        if (m.getId() == id) return &m;
    }
    throw std::out_of_range("영화ID가 존재하지 않습니다.");
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
    int lineNum = 0;
    while (std::getline(file, line)) {
        lineNum++;
        try {
            std::stringstream ss(line);
            std::string token;
            
            std::getline(ss, token, ','); int id = std::stoi(token);
            std::getline(ss, token, ','); std::string title = token;
            std::getline(ss, token, ','); std::string genre = token;
            std::getline(ss, token, ','); int year = std::stoi(token);

            Movie m(id, title, genre, year);
            movies.push_back(m);
            if (id >= nextId) nextId = id + 1;
        } catch (const std::exception& e) {
            std::cerr << lineNum << "번 줄 건너뜀: " << e.what() << std::endl; 
        }
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