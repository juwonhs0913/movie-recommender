#include "Movie.h"
#include <iostream>
#include <vector>

int main() {
    std::vector<Movie> movies;

    movies.emplace_back(Movie(1, "Inception",    "Sci-Fi",   2010));
    movies.emplace_back(Movie(2, "Parasite",     "Thriller", 2019));
    movies.emplace_back(Movie(3, "Interstellar", "Sci-Fi",   2014));
    movies.emplace_back(Movie(4, "왕과 사는 남자", "History", 2026));
    movies.emplace_back(Movie(5, "너의 이름은", "Animation",  2017));

    movies[0].addRating(4.8);
    movies[0].addRating(4.5);
    movies[1].addRating(5.0);
    movies[2].addRating(3.4);
    movies[3].addRating(5.0);
    movies[3].addRating(5.0);
    movies[3].addRating(4.8);
    movies[3].addRating(4.5);

    std::cout << movies[0].getId() << ". " << movies[0].getTitle()
              << "(" << movies[0].getGenre() << ", " 
              << movies[0].getReleaseYear() << ") 평점: "
              << movies[0].getAverageRating() << "("
              << movies[0].getRatingCount() << "건)"
              << std::endl;

    for (const Movie& m : movies) {
        m.display();    
    }

    std::cout << "총 " << movies.size() << "편" << std::endl;

    std::cout << std::endl;
    
    std::vector<Rating> ratings;
    
    ratings.emplace_back(1, 1, 5);
    ratings.emplace_back(2, 1, 3.4);
    ratings.emplace_back(3, 2, 5.0);
    ratings.emplace_back(4, 3, 9.9);


    //Rating r1(1, 1, 5);
    //Rating r2(2, 1, 9.8); // 오류 출력 -> 0.0

    std::cout << "USERID: " << ratings[0].getuserId() << ", MOVIE ID: "
                << ratings[0].getmovieId() << ", 평점: "
                << ratings[0].getscore() <<std::endl; 

    for (const Rating& r : ratings) {
        r.display();    
    }

    std::cout << std::endl;

    std::vector<User> users;

    users.emplace_back(1, "juwon", "juwonhs0913@naver.com");
    users.emplace_back(2, "KIM", "minjaekim@ssu.ac.kr");
    users.emplace_back(3, "jane", "masdasdaim@ssu.ac.kr");
    users.emplace_back(4, "samsung", "098asdkjha09!!@ssu.ac.kr");

    //User u1(1, "juwon", "juwonhs0913@naver.com");
    //User u2(2, "KIM", "minjaekim@ssu.ac.kr");

    std::cout << "사용자 정보: " << users[0].getId() << "." << users[0].getName() << "(" 
                << users[0].getEmail() << ")" << std::endl;

    for(const User& u : users) {
        u.display();
    }

    return 0;
}