#include "Manager.h"
#include "Movie.h"
#include <iostream>

void showMenu() {
    std::cout << "=====" << " Movie Recommender " << "=====\n\n"
            <<"[ 영화 ]\n" << "1. 영화 출력\n" << "2. 제목으로 검색\n" <<"3. 전체 목록 출력\n" << "4. 평점순 정렬 출력\n\n"
            <<"[ 사용자 ]\n" << "5. 사용자 추가\n" << "6. 사용자 목록 출력\n\n"
            <<"[ 평점 ]\n" << "7. 평점 입력\n" << "8. 영화별 평점 보기\n\n"
            <<"0. 프로그램 종료\n\n" << "선택 > _ ";
}

int main() {

    int menuChoice = -1;

    while (menuChoice != 0) {
        showMenu();
        std::cin >> menuChoice;

        switch (menuChoice) {
            case 1:
            case 2:
            case 3:
            case 4:
            case 5:
            case 6:
            case 7:
            case 8:
        }
    }
    return 0;
}