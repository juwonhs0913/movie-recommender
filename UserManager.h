#pragma once
#include "User.h"
#include <vector>
#include <string>

class UserManager {
private:
    std::vector<User> users;
    int nextId;

public:
    UserManager();

    void addUser(const std::string& name, const std::string& email);
    void printAll() const;

    const User* findById(int id) const;
    const std::vector<User>& getUsers() const;

    void loadFromFile(const std::string& filename);
    void saveToFile(const std::string& filename) const;
};