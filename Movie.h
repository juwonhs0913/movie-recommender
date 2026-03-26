#pragma once
#include <string>

class Movie {
private:
    int         id;
    std::string title;
    std::string genre;
    int         releaseYear;
    double      totalRating;    // averageRating 제거
    int         ratingCount;    // 추가

public:
    Movie();                    // 기본 생성자 추가
    Movie(int id, const std::string& title,
          const std::string& genre, int year);

    int         getId()              const;
    std::string getTitle()           const;
    std::string getGenre()           const;
    int         getReleaseYear()     const;  // getYear → getReleaseYear
    double      getAverageRating()   const;  // getRating → getAverageRating
    int         getRatingCount()     const;  // 추가

    void addRating(double r);               // 추가
    void display()               const;
};

class User {
private:
    int         id;     //사용자 ID
    std::string name;   //이름
    std::string email;  //이메일

public:
    User(); //기본 생성자
    User(int id, const std::string& name,
        const std::string& email);
    
    int         getId() const;
    std::string getName() const;
    std::string getEmail() const;

    void display() const;
};

class Rating {
private:
    int    userId;    // 평가한 사용자
    int    movieId;   // 평가 대상 영화
    double score;     // 0.0 ~ 5.0

public:
    Rating(int userid, int movieid, double s);

    int getuserId() const;
    int getmovieId() const;
    double getscore() const;

    void display() const;
    // TODO: 생성자 (score 유효성 검사 포함)
    //       getter, display()
    // ⚠ score 가 0~5 범위인지 확인!
};