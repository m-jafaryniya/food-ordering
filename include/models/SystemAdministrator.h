
#ifndef FOOD_ORDERING_SYSTEM_SYSTEMADMINISTRATOR_H
#define FOOD_ORDERING_SYSTEM_SYSTEMADMINISTRATOR_H
#include "User.h"

class SystemAdministrator : public User {
    public:
    SystemAdministrator();
    SystemAdministrator(const std::string &phoneNumber, const std::string &password, const std::string &userName);
    virtual ~SystemAdministrator();


    private:
};

#endif //FOOD_ORDERING_SYSTEM_SYSTEMADMINISTRATOR_H