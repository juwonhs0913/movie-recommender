#include <iostream>
#include <string>
#include "MovieManager.h"
#include "UserManager.h"
#include "RatingManager.h"
#include "Recommender.h"

void printMenu() {
    std::cout << "\n===== Movie Recommender =====\n";
    std::cout << "[ 영화 ]\n";
    std::cout << "   1. 영화 추가\n";
    std::cout << "   2. 제목으로 검색\n";
    std::cout << "   3. 전체 목록 출력\n";
    std::cout << "   4. 정렬 출력\n";
    std::cout << "[ 사용자 ]\n";
    std::cout << "   5. 사용자 추가\n";
    std::cout << "   6. 사용자 목록 출력\n";
    std::cout << "   7. 사용자 맞춤 추천 영화\n";
    std::cout << "[ 평점 ]\n";
    std::cout << "   8. 평점 입력\n";
    std::cout << "   9. 영화별 평점 보기\n";
    std::cout << "[ 통계 ]\n";
    std::cout << "  10. 통계 보기\n";
    std::cout << " 0. 저장 및 종료\n";
    std::cout << "선택 > ";
}

int main() {
    MovieManager movieMgr;
    UserManager  userMgr;
    RatingManager ratingMgr;
    Recommender recommender(movieMgr, userMgr, ratingMgr);

    movieMgr.loadFromFile("data/movies.csv");
    userMgr.loadFromFile("data/users.csv");
    ratingMgr.loadFromFile("data/ratings.csv", movieMgr);

    int choice = -1;

    while (true) {
        printMenu();
        std::cin >> choice;

        if (choice == 0) {
            movieMgr.saveToFile("data/movies.csv");
            userMgr.saveToFile("data/users.csv");
            ratingMgr.saveToFile("data/ratings.csv");

            std::cout << "프로그램을 종료합니다.\n";
            break;
        }

        if (choice == 1) {
            std::string title, genre;
            int year;
            std::cin.ignore();
            std::cout << "제목: ";
            std::getline(std::cin, title);
            std::cout << "장르: ";
            std::getline(std::cin, genre);
            std::cout << "개봉 연도 (1888~2100): ";
            std::cin >> year;
            movieMgr.addMovie(title, genre, year);
        }

        else if (choice == 2) {
            std::string keyword;
            std::cin.ignore();
            std::cout << "영화 제목: ";
            std::getline(std::cin, keyword);
            movieMgr.searchByTitle(keyword);
        }

        else if (choice == 3) {
            movieMgr.printAll();
        }

        else if (choice == 4) {
            // 정렬 서브메뉴
            std::cout << "\n=== 정렬 옵션 ===\n";
            std::cout << "   1. 평점순 (높은 순)\n";
            std::cout << "   2. 가나다순 (제목)\n";
            std::cout << "   3. 최신순 (개봉 연도)\n";
            std::cout << "   4. ID순 (영화 ID)\n";
            std::cout << "선택 > ";
            int sortChoice;
            std::cin >> sortChoice;
            if (sortChoice == 1) {
                movieMgr.SortByRating();
            } 
            else if (sortChoice == 2) {
                movieMgr.sortByTitle();
            }
            else if (sortChoice == 3) {
                movieMgr.sortByYear();
            }
            else if (sortChoice == 4) {
                movieMgr.sortById();
            } 
            else {
                std::cout << "잘못된 선택입니다.\n";
                continue;
            }
            movieMgr.printAll();
        }

        else if (choice == 5) {
            std::string name, email;
            std::cin.ignore();
            std::cout << "이름: ";
            std::getline(std::cin, name);
            std::cout << "이메일: ";
            std::getline(std::cin, email);
            userMgr.addUser(name, email);
        }

        else if (choice == 6) {
            userMgr.printAll();
        }

        else if (choice == 7) {
            int userId;
            std::cout << "사용자 ID: ";
            std::cin >> userId;
            auto result = recommender.recommend(userId);
            for (int id : result) {
                Movie* m = movieMgr.findById(id);
                if (m) std::cout << *m << "\n";
            }
        }
        
        else if (choice == 8) {
            int userId, movieId;
            double score;
            std::cout << "사용자 ID: ";
            std::cin >> userId;
            std::cout << "영화 ID: ";
            std::cin >> movieId;
            std::cout << "평점 (0.0~5.0): ";
            std::cin >> score;

            ratingMgr.addRating(userId, movieId, score, movieMgr, userMgr);
        }

        else if (choice == 9) {
            int movieId;
            std::cout << "영화 ID: ";
            std::cin >> movieId;
            ratingMgr.ratingByMovie(movieId, movieMgr);
        }

        else if (choice == 10) {
            movieMgr.showStatistics();
        }
    }

    return 0;
}