
#include "models/User.h"
#include "models/IdMaker.h"
#include <iostream>
#include <string>

User::User()= default;

User::User(const std::string &phoneNumber, const std::string &password, const std::string &userName) {
    this->id = IdMaker::getUserID();
    this->phoneNumber = phoneNumber;
    this->password = password;
    this->userName = userName;
}

User::~User() {}

void User::setPhoneNumber(std::string phoneNumber) {
    this->phoneNumber = phoneNumber;
}

void User::setPassword(std::string password) {
    this->password = password;
}

void User::setUserName(std::string userName) {
    this->userName = userName;
}

int User::getId() const {
    return id;
}

std::string User::getPhoneNumber() const {
    return this->phoneNumber;
}

std::string User::getPassword() const {
    return this->password;
}

std::string User::getUserName() const {
    return this->userName;
}

void User::showInformation() const {
    std::cout << "user name : " << this->userName << std::endl;
    std::cout << "phone number : " << this->phoneNumber << std::endl;
    std::cout << "id : " << this->id << std::endl;
}

void User::setId(int id) {
    this->id = id;
}
