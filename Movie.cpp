#include "Movie.h"
#include <iostream>

Movie::Movie()
    : id(0), releaseYear(0),
      totalRating(0.0), ratingCount(0) {}

Movie::Movie(int id, const std::string& title,
             const std::string& genre, int year)
    : id(id), title(title), genre(genre),
      releaseYear(year),
      totalRating(0.0), ratingCount(0) {}

int         Movie::getId()          const { return id; }
std::string Movie::getTitle()       const { return title; }
std::string Movie::getGenre()       const { return genre; }
int         Movie::getReleaseYear() const { return releaseYear; }
int         Movie::getRatingCount() const { return ratingCount; }

double Movie::getAverageRating() const {
    if (ratingCount == 0) return 0.0; 
    return totalRating / ratingCount;
}

void Movie::setReleaseYear(int year) {
    if (year < 1888 || year > 2100) {
        std::cout << "유효하지 않은 연도입니다.\n";
        return;
    }
    releaseYear = year;
}
void Movie::addRating(double r) {
    if (r < 0.0 || r > 5.0) return;  
    totalRating += r;
    ratingCount++;
}

void Movie::display() const {         
    std::cout << id << ". " << title
              << " (" << releaseYear << ")"
              << "  평점: " << getAverageRating()
              << " (" << ratingCount << "건)"
              << std::endl;
}

// 연산자 오버로딩 구현
bool Movie::operator==(const std::string& targetTitle) const {
    return title == targetTitle;
}

bool Movie::operator<(const Movie& other) const {
    return getAverageRating() < other.getAverageRating(); 
}

std::ostream& operator<<(std::ostream& os, const Movie& m) {
    os << m.id << ". " << m.title << " (" << m.releaseYear << ") 평점: " 
       << m.getAverageRating() << " (" << m.ratingCount << "건)";
    return os;
}