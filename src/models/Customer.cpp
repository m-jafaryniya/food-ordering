
#include "models/Customer.h"

Customer::Customer() {}

Customer::Customer(const std::string &phoneNumber, const std::string &password, const std::string &userName)
:User(phoneNumber, password, userName) {
}

Customer::~Customer() = default;

void Customer::setWallet(double wallet) {
    this->wallet = wallet;
}

double Customer::getWallet() const {
    return wallet;
}


