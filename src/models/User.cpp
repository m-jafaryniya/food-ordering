
#include "models/User.h"
#include "models/IdMaker.h"
#include <iostream>
#include <string>

User::User()= default;

User::User(const std::string &phoneNumber, const std::string &password, const std::string &userName) {
    this->id = IdMaker::get_UserID();
    this->phoneNumber = phoneNumber;
    this->password = password;
    this->userName = userName;
}

User::~User() {}

void User::set_phoneNumber(std::string phoneNumber) {
    this->phoneNumber = phoneNumber;
}

void User::set_password(std::string password) {
    this->password = password;
}

void User::set_userName(std::string userName) {
    this->userName = userName;
}

int User::get_id() const {
    return id;
}

std::string User::get_phoneNumber() const {
    return this->phoneNumber;
}

std::string User::get_password() const {
    return this->password;
}

std::string User::get_userName() const {
    return this->userName;
}

void User::showInformation() const {
    std::cout << "user name : " << this->userName << std::endl;
    std::cout << "phone number : " << this->phoneNumber << std::endl;
    std::cout << "id : " << this->id << std::endl;
}
