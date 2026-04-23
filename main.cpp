#include "Manager.h"
#include <iostream>
#include <string>

void showMenu() {
    std::cout << "\n=== Movie Recommender ===\n\n";
    std::cout << "[ 영화 ]\n";
    std::cout << "  1. 영화 추가\n";
    std::cout << "  2. 제목으로 검색\n";
    std::cout << "  3. 전체 목록 출력\n";
    std::cout << "  4. 평점순 정렬 출력\n\n";
    std::cout << "[ 사용자 ]\n";
    std::cout << "  5. 사용자 추가\n";
    std::cout << "  6. 사용자 목록 출력\n\n";
    std::cout << "[ 평점 ]\n";
    std::cout << "  7. 평점 입력\n";
    std::cout << "  8. 영화별 평점 보기\n\n";
    std::cout << "  0. 종료\n\n";
    std::cout << "선택 > ";
}

int main() {
    MovieManager m_manager;
    UserManager u_manager;
    int menuChoice = 10;

    while (menuChoice != 0) {
        showMenu();
        std::cin >> menuChoice;
        std::cin.ignore();

        switch (menuChoice) {
            case 1: m_manager.addMovie(); break;
            case 2: m_manager.findByTitle(); break;
            case 3: m_manager.printAllMovies(); break;
            case 4: m_manager.sortByRating(); break;
            case 5: u_manager.addUser(); break;
            case 6: u_manager.printAllUsers(); break;
            case 7: m_manager.addRating(u_manager); break;
            case 8: m_manager.ratingByMovie(); break;
        }
    }
    return 0;
}
