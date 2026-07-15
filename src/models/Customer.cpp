
#include "models/Customer.h"
#include "models/User.h"

Customer::Customer() {}

Customer::Customer(const std::string &phoneNumber, const std::string &password, const std::string &userName)
:User(phoneNumber, password, userName){}

Customer::~Customer() {}

void Customer::set_wallet(double wallet) {
    this->wallet = wallet;
}

double Customer::get_wallet() const {
    return wallet;
}


