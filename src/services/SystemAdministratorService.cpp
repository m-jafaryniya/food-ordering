
#include "services/SystemAdministratorService.h"
#include <vector>
#include <algorithm>

SystemAdministratorService::SystemAdministratorService(Database* database)
:restaurantDAO(database),customerDAO(database),restaurateurDAO(database),orderDAO(database){}

bool SystemAdministratorService::addRestaurant(const Restaurant &restaurant) {
    restaurantDAO.insertRestaurant(restaurant);
    return true;
}

bool SystemAdministratorService::activeRestaurant(int restaurantId) {
    Restaurant restaurant = restaurantDAO.getRestaurantById(restaurantId);
    restaurant.setActive(true);
    return restaurantDAO.updateRestaurant(restaurant);
}

bool SystemAdministratorService::deActiveRestaurant(int restaurantId) {
    Restaurant restaurant = restaurantDAO.getRestaurantById(restaurantId);
    restaurant.setActive(false);
    return restaurantDAO.updateRestaurant(restaurant);
}

std::vector<Restaurant> SystemAdministratorService::getRestaurants() {
    return restaurantDAO.getRestaurants();
}

int SystemAdministratorService::getRestaurantCount() {
    return restaurantDAO.getRestaurants().size();
}

int SystemAdministratorService::getRestaurateurCount() {
    std::vector<Restaurant> restaurants = restaurantDAO.getRestaurants();
    std::vector<int> ownerIds;

    for (const Restaurant& r : restaurants) {
        int ownerId = r.getOwnerId();
        if (std::find(ownerIds.begin(), ownerIds.end(), ownerId) == ownerIds.end()) {
            ownerIds.push_back(ownerId);
        }
    }
    return ownerIds.size();
}

int SystemAdministratorService::getCustomerCount() {
    return customerDAO.getCustomers().size();
}

int SystemAdministratorService::getOrderCount(int restaurantId) {
    return orderDAO.getRestaurantOrders(restaurantId).size();
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
    double total = 0.0;
    std::vector<Restaurant> restaurants = restaurantDAO.getRestaurants();

    for (const Restaurant& r : restaurants) {
        total += getRestaurantTotalSales(r.getID());
    }
    return total;
}

void SystemAdministratorService::systemReport() {
    std::cout << "====SYSTEM REPORT====" << std::endl;
    std::cout << "Restaurants count : " << getRestaurantCount() << std::endl;
    std::cout << "Restaurateurs count : " << getRestaurateurCount() << std::endl;
    std::cout << "Customers count : " << getCustomerCount() << std::endl;
    std::cout << "Total sales : " << getTotalSales() << std::endl;

    std::cout << "---Restaurants Details---" << std::endl;

    std::vector<Restaurant> restaurants = restaurantDAO.getRestaurants();
    for (const Restaurant& r : restaurants) {
        std::cout << "Restaurant name : " << r.getName() << std::endl;
        std::cout << "Order count : " << getOrderCount(r.getID()) << std::endl;
        std::cout << "Total sale : " << getRestaurantTotalSales(r.getID()) << std::endl;
        std::cout << "---------------------------------------------" << std::endl;
    }
    std::cout << "============================================" << std::endl;
}
