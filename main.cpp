#include <iostream>

#include "dao/CustomerDAO.h"
#include "dao/Database.h"
#include "dao/RestaurantDAO.h"
#include "dao/RestaurateurDAO.h"
#include "dao/SystemAdministratorDAO.h"
#include "services/CustomerService.h"
#include "services/RestaurateurService.h"
#include "services/Login.h"

int main() {
    Database db("food_ordering_system");
    db.createTables();

    CustomerDAO customerDAO(&db);
    RestaurantDAO restaurantDAO(&db);
    RestaurateurDAO restaurateurDAO(&db);
    SystemAdministratorDAO system_administratorDAO(&db);

    CustomerService (customerDAO, restaurantDAO);
    RestaurateurService (customerDAO, restaurantDAO);
    Login (customerDAO, restaurateurDAO, system_administratorDAO);

}
