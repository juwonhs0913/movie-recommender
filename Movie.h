#pragma once
#include <string>
#include <iostream>

class Movie {
private:
    int         id;
    std::string title;
    std::string genre;
    int         releaseYear;
    double      totalRating;
    int         ratingCount;
public:
    Movie();
    Movie(int id, const std::string& title,
          const std::string& genre, int year);

    int         getId()            const;
    std::string getTitle()         const;
    std::string getGenre()         const;
    int         getReleaseYear()   const;
    double      getAverageRating() const;
    int         getRatingCount()   const;

    void setReleaseYear(int year);
    void addRating(double r);
    void display()                 const;

    bool operator==(const Movie& other) const;
    bool operator<(const Movie& other)  const;
    friend std::ostream& operator<<(std::ostream& os, const Movie& m);
};

class User {
private:
    int         id;
    std::string name;
    std::string email;
public:
    User();
    User(int id, const std::string& name, const std::string& email);

    int         getId()    const;
    std::string getName()  const;
    std::string getEmail() const;
    void display()         const;

    friend std::ostream& operator<<(std::ostream& os, const User& u);
};

class Rating {
private:
    int    userId;
    int    movieId;
    double score;
public:
    Rating(int userid, int movieid, double s);

    int    getUserId()  const;
    int    getMovieId() const;
    double getScore()   const;
    void   display()    const;
};