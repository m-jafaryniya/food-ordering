
#ifndef FOOD_ORDERING_SYSTEM_CUSTOMER_H
#define FOOD_ORDERING_SYSTEM_CUSTOMER_H
#include "User.h"

class Customer : public User{
    public:
    Customer();
    Customer(const std::string &phoneNumber, const std::string &password, const std::string &userName);
    virtual ~Customer();


    private:

};

#endif //FOOD_ORDERING_SYSTEM_CUSTOMER_H