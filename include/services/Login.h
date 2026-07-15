
#ifndef FOOD_ORDERING_SYSTEM_LOGIN_H
#define FOOD_ORDERING_SYSTEM_LOGIN_H

#include "dao/CustomerDAO.h"
#include "dao/RestaurateurDAO.h"
#include "dao/SystemAdministratorDAO.h"

class Login {
    public:
    Login(Database* database);
    User* login();

    private:
    CustomerDAO customerDAO;
    RestaurateurDAO restaurateurDAO;
    SystemAdministratorDAO systemAdministratorDAO;
    User* registerUser(const std::string& phone);

};
#endif //FOOD_ORDERING_SYSTEM_LOGIN_H