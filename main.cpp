#include <iostream>

#include "dao/CustomerDAO.h"
#include "dao/Database.h"
#include "dao/RestaurantDAO.h"
#include "dao/RestaurateurDAO.h"
#include "dao/SystemAdministratorDAO.h"
#include "services/CustomerService.h"
#include "services/RestaurateurService.h"
#include "services/Login.h"
#include "services/SystemAdministratorService.h"

int main() {
    Database db("food_ordering_system.db");
    Login loginManager(&db);

    User* loggedInUser = loginManager.login();
    if (loggedInUser == nullptr) {
        std::cout << "Login Failed" << std::endl;
        return 1;
    }
    std::cout << "Welcome" << std::endl;

    if (Customer* customer = dynamic_cast<Customer *>(loggedInUser)){
        CustomerService customerService(&db);
    }
    else if (Restaurateur* restaurateur = dynamic_cast<Restaurateur *>(loggedInUser)){
            RestaurateurService restaurateurService(&db);
    }
    else if (SystemAdministrator* administrator = dynamic_cast<SystemAdministrator *>(loggedInUser)){
            SystemAdministratorService systemAdministratorService(&db);
    }

    delete loggedInUser;
    return 0;
}