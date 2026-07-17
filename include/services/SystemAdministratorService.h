
#ifndef FOOD_ORDERING_SYSTEM_SYSTEMADMINISTRATORSERVICE_H
#define FOOD_ORDERING_SYSTEM_SYSTEMADMINISTRATORSERVICE_H

#include "dao/CustomerDAO.h"
#include "dao/RestaurateurDAO.h"
#include "dao/OrderDAO.h"
#include "dao/RestaurantDAO.h"

class SystemAdministratorService {
    public:
    SystemAdministratorService();
    bool addRestaurant(const Restaurant &restaurant);
    bool activeRestaurant(int restaurantId);
    bool deActiveRestaurant(int restaurantId);
    std::vector<Restaurant> getRestaurants();

    int getRestaurantCount();
    int getRestaurateurCount();
    int getCustomerCount();
    int getOrderCount(int restaurantId);
    double getRestaurantTotalSales(int restaurantId);
    double getTotalSales();
    void systemReport();

private:
    RestaurantDAO restaurantDAO;
    CustomerDAO customerDAO;
    RestaurateurDAO restaurateurDAO;
    OrderDAO orderDAO;
};

#endif //FOOD_ORDERING_SYSTEM_SYSTEMADMINISTRATORSERVICE_H