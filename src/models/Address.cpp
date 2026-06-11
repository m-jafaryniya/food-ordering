
#include "models/Address.h"

Address::Address() {}

Address::Address(const std::string &cityName, const std::string &streetName, const std::string &alleyName, const int block) {
    this->cityName = cityName;
    this->streetName = streetName;
    this->alleyName = alleyName;
    this->block = block;
}

Address::~Address() {}
