
#include "services/SystemAdministratorService.h"

SystemAdministratorService::SystemAdministratorService() {

}

bool SystemAdministratorService::addRestaurant(const Restaurant &restaurant) {

}

bool SystemAdministratorService::activeRestaurant(int restaurantId) {
    Restaurant restaurant;
    restaurantDAO.getRestaurantById(restaurantId);
    restaurant.set_active(true);
    restaurantDAO.updateRestaurant(restaurant);
    return true;
}

bool SystemAdministratorService::deActiveRestaurant(int restaurantId) {
    Restaurant restaurant;
    restaurantDAO.getRestaurantById(restaurantId);
    restaurant.set_active(false);
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
    return restaurateurDAO.getRestaurateurs().size();
}

int SystemAdministratorService::getCustomerCount() {
    return customerDAO.getCustomers().size();
}

int SystemAdministratorService::getOrderCount(int restaurantId) {
    return orderDAO.getOrders().size();
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
    double total =0 ;
    std::vector<Order> orders = orderDAO.getOrders();
    for (const Order &order : orders) {
        total+=order.get_totalPrice();
    }
    return total;
}
