
#include "services/SystemAdministratorService.h"

SystemAdministratorService::SystemAdministratorService(Database* database)
:restaurantDAO(database),customerDAO(database),restaurateurDAO(database),orderDAO(database){}

bool SystemAdministratorService::addRestaurant(const Restaurant &restaurant) {
    restaurantDAO.insertRestaurant(restaurant);
    return true;
}

bool SystemAdministratorService::activeRestaurant(int restaurantId) {
    Restaurant restaurant;
    restaurantDAO.getRestaurantById(restaurantId);
    restaurant.setActive(true);
    restaurantDAO.updateRestaurant(restaurant);
    return true;
}

bool SystemAdministratorService::deActiveRestaurant(int restaurantId) {
    Restaurant restaurant;
    restaurantDAO.getRestaurantById(restaurantId);
    restaurant.setActive(false);
    restaurantDAO.updateRestaurant(restaurant);
    return true;
}

std::vector<Restaurant> SystemAdministratorService::getRestaurants() {
    return restaurantDAO.getRestaurants();
}

int SystemAdministratorService::getRestaurantCount() {
    return restaurantDAO.getRestaurants().size();
}

int SystemAdministratorService::getRestaurateurCount() {
    return 0;
}

int SystemAdministratorService::getCustomerCount() {
    return customerDAO.getCustomers().size();
}

int SystemAdministratorService::getOrderCount(int restaurantId) {
    return 0;
}

double SystemAdministratorService::getRestaurantTotalSales(int restaurantId) {
    double total = 0;
    std::vector<Order> orders = orderDAO.getRestaurantOrders(restaurantId);
    for (const Order &order : orders) {
        if (order.get_status() == OrderStatus::delivered) {
            total += order.get_totalPrice();
        }
    }
    return total;
}

double SystemAdministratorService::getTotalSales() {
    return 0;
}
