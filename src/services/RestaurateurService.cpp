
#include "services/RestaurateurService.h"

RestaurateurService::RestaurateurService(Database* database)
    :menuDAO(database),restaurantDAO(database),orderDAO(database){}

bool RestaurateurService::insertRestaurant(const Restaurateur &owner, const std::string name) {
    Restaurant restaurant;
    restaurant.setOwnerId(owner.getId());
    restaurant.setName(name);

    restaurantDAO.insertRestaurant(restaurant);
    return true;
}

bool RestaurateurService::editRestaurant(const Restaurant &restaurant) {
    restaurantDAO.updateRestaurant(restaurant);
    return true;
}

bool RestaurateurService::deleteRestaurant(int restaurantId) {
    menuDAO.deleteDrink(restaurantId);
    menuDAO.deleteFood(restaurantId);

    Restaurant restaurant;
    restaurant.setId(restaurantId);
    restaurantDAO.deleteRestaurant(restaurant);
    return true;
}

bool RestaurateurService::changeRestaurantStatus(int restaurantId, bool isOpen) {
    return true;
}

Restaurant RestaurateurService::getRestaurant(int restaurantId) {
    return restaurantDAO.getRestaurantById(restaurantId);
}

std::vector<Restaurant> RestaurateurService::getRestaurants(int ownerId) {
    std::vector<Restaurant> restaurants;
    return restaurants;
}

bool RestaurateurService::addMenuItem(const Menu &item) {
    return true;
}

bool RestaurateurService::editMenuItem(const Menu &item) {
    return true;
}

bool RestaurateurService::deleteMenuItem(const Menu &item) {
    return true;
}

bool RestaurateurService::changeMenuItemPrice(int itemId, double newPrice) {
    return true;
}

bool RestaurateurService::changeMenuItemAvailability(int itemId, bool available) {
    return true;
}

std::vector<Order> RestaurateurService::getRestaurantOrders(int restaurantId) {
    return orderDAO.getRestaurantOrders(restaurantId);
}

std::vector<Order> RestaurateurService::getPendingOrders(int restaurantId) {
    std::vector<Order> orders;
    return orders;
}

bool RestaurateurService::changeOrderStatus(int orderId, OrderStatus status) {
    orderDAO.updateOrderStatus(orderId, status);
    return true;
}

bool RestaurateurService::acceptOrder(int orderId) {
    changeOrderStatus(orderId, OrderStatus::preparing);
    return true;
}

bool RestaurateurService::cancelOrder(int orderId) {
    changeOrderStatus(orderId, OrderStatus::cancelled);
    return true;
}

bool RestaurateurService::readyOrder(int orderId) {
    changeOrderStatus(orderId, OrderStatus::ready);
    return true;
}

bool RestaurateurService::deliveredOrder(int orderId) {
    changeOrderStatus(orderId, OrderStatus::delivered);
    return true;
}


