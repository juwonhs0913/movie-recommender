#include "Movie.h"
#include <iostream>

User::User() : id(0) {}

User::User(int id, const std::string& name, const std::string& email)
    : id(id), name(name), email(email) {}

int         User::getId()    const { return id; }
std::string User::getName()  const { return name; }
std::string User::getEmail() const { return email; }

std::ostream& operator<<(std::ostream& os, const User& u) {
    os << u.id << ". " << u.name << " (" << u.email << ")";
    return os;
}