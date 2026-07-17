
#include "models/Address.h"

Address::Address() {}

Address::Address(const std::string &cityName, const std::string &streetName, const std::string &alleyName, const int block) {
    this->cityName = cityName;
    this->streetName = streetName;
    this->alleyName = alleyName;
    this->block = block;
}

Address::~Address() {}

void Address::set_cityName(const std::string &cityName) {
    this->cityName = cityName;
}

void Address::set_streetName(const std::string &streetName) {
    this->streetName = streetName;
}

void Address::set_alleyName(const std::string &alleyName) {
    this->alleyName = alleyName;
}

void Address::set_block(const int block) {
    this->block = block;
}

std::string Address::get_cityName() const {
    return cityName;
}

std::string Address::get_streetName() const {
    return streetName;
}

std::string Address::get_alleyName() const {
    return alleyName;
}

int Address::get_block() const {
    return block;
}