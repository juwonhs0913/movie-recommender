#include "UserManager.h"
#include <iostream>
#include <fstream>
#include <sstream>

UserManager::UserManager() : nextId(1) {}

void UserManager::addUser(const std::string& name, const std::string& email) {
    User u(nextId++, name, email);
    users.push_back(u);
    std::cout << "사용자 [" << name << "]가 추가되었습니다.\n";
}

void UserManager::printAll() const {
    if (users.empty()) {
        std::cout << "등록된 사용자가 없습니다.\n";
        return;
    }
    std::cout << "\n=== 전체 사용자 목록 ===\n";
    for (const User& u : users) {
        std::cout << u << "\n";
    }
}

const User* UserManager::findById(int id) const {
    for (const User& u : users) {
        if (u.getId() == id) return &u;
    }
    return nullptr;
}

const std::vector<User>& UserManager::getUsers() const {
    return users;
}


void UserManager::loadFromFile(const std::string& filename) {
    std::ifstream file(filename);          // 1. 파일 열기
    if (!file.is_open()) {                 // 2. 열기 확인
        std::cerr << "Error: " << filename << " 을(를) 열 수 없습니다.\n";
        return;
    }

    std::string line;
    std::getline(file, line);             

    while (std::getline(file, line)) {
        std::stringstream ss(line);
        std::string token;

        std::getline(ss, token, ','); int id           = std::stoi(token);
        std::getline(ss, token, ','); std::string name  = token;
        std::getline(ss, token, ','); std::string email = token;

        User u(id, name, email);           
        users.push_back(u);

        if (id >= nextId) nextId = id + 1;
    }

    file.close();
    std::cout << filename << " 로드 완료: " << size() << "건\n";
}

void UserManager::saveToFile(const std::string& filename) const {
    std::ofstream file(filename);
    if (!file.is_open()) {
        std::cerr << "Error: " << filename << " 저장 실패\n";
        return;
    }

    file << "id,name,email\n";

    for (const User& u : users) {
        file << u.getId()    << ","
             << u.getName()  << ","
             << u.getEmail() << "\n";
    }

    file.close();
    std::cout << filename << " 저장 완료: " << size() << "건\n";
}