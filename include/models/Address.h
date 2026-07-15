
#ifndef FOOD_ORDERING_SYSTEM_ADDRESS_H
#define FOOD_ORDERING_SYSTEM_ADDRESS_H
#include <string>

class Address {
public:
    Address();
    Address(const std::string &cityName, const std::string &streetName, const std::string &alleyName, int block);
    virtual ~Address();
    void set_cityName(const std::string &cityName);
    void set_streetName(const std::string &streetName);
    void set_alleyName(const std::string &alleyName);
    void set_block(int block);
    std::string get_cityName();
    std::string get_streetName();
    std::string get_alleyName();
    int get_block();

private:
    std::string cityName;
    std::string streetName;
    std::string alleyName;
    int block;
};

#endif //FOOD_ORDERING_SYSTEM_ADDRESS_H