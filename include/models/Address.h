
#ifndef FOOD_ORDERING_SYSTEM_ADDRESS_H
#define FOOD_ORDERING_SYSTEM_ADDRESS_H
#include <string>

class Address {
public:
    Address();
    Address(const std::string &cityName, const std::string &streetName, const std::string &alleyName, int block);
    virtual ~Address();

private:
    std::string cityName;
    std::string streetName;
    std::string alleyName;
    int block;
};

#endif //FOOD_ORDERING_SYSTEM_ADDRESS_H