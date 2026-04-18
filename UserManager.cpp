#include "Manager.h"
#include <iostream>

void UserManager::addUser() {
    std::string name, email;
    std::cout << "사용자 이름: ";
    std::getline(std::cin, name);
    std::cout << "이메일: ";
    std::getline(std::cin, email);

    users.push_back(User(currentUserId, name, email));
    std::cout << "사용자가 추가되었습니다. (ID: " << currentUserId++ << ")\n";
}

void UserManager::printAllUsers() const {
    if (users.empty()) { std::cout << "등록된 사용자가 없습니다.\n"; return; }
    for (const auto& user : users) user.display();
}

bool UserManager::isExistingUser(int id) const {
    for (const auto& user : users) {
        if (user.getId() == id) return true;
    }
    return false;
}