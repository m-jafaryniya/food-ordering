
#include "services/RestaurateurService.h"

RestaurateurService::RestaurateurService() {

}

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
    menuDAO.deleteDrink();
    menuDAO.deleteFood();
    restaurantDAO.deleteRestaurant(restaurantId);
    return true;
}

bool RestaurateurService::changeRestaurantStatus(int restaurantId, bool isOpen) {
    restaurantDAO.changeRestaurantStatus(restaurantId, isOpen);
    return true;
}

Restaurant RestaurateurService::getRestaurant(int restaurantId) {
    return restaurantDAO.getRestaurantById(restaurantId);
}

std::vector<Restaurant> RestaurateurService::getRestaurants(int ownerId) {
    return restaurantDAO.getRestaurantsByOwner();
}

bool RestaurateurService::addMenuItem(const Menu &item) {
    menuDAO.addFood();
    menuDAO.addDrink();
    return true;
}

bool RestaurateurService::editMenuItem(const Menu &item) {
    menuDAO.updateDrink();
    menuDAO.updateFood();
    return true;
}

bool RestaurateurService::deleteMenuItem(const Menu &item) {
    menuDAO.deleteDrink();
    menuDAO.deleteFood();
    return true;
}

bool RestaurateurService::changeMenuItemPrice(int itemId, double newPrice) {
    menuDAO.changePrice(itemId, newPrice);
    return true;
}

bool RestaurateurService::changeMenuItemAvailability(int itemId, bool available) {
    menuDAO.changeItemAvailability(itemId, available);
    return true;
}

std::vector<Order> RestaurateurService::getRestaurantOrders(int restaurantId) {
    return orderDAO.getRestaurantOrders(restaurantId);
}

std::vector<Order> RestaurateurService::getPendingOrders(int restaurantId) {
    return orderDAO.getOrderByStatus(restaurantId, OrderStatus::pending);
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


