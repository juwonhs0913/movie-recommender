#include "Manager.h"
#include <iostream>

UserManager::UserManager() {}

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
    if (users.empty()) {
        std::cout << "등록된 사용자가 없습니다.\n";
        return;
    }
    for (const User& u : users) std::cout << u << "\n";
}

bool UserManager::isExistingUser(int userId) const {
    int userId;
    std::cout << "사용자 ID 입력: ";
    std::cin >> userId;
    for (const User& u : users)
        if (u.getId() == userId) return true;
    return false;
}