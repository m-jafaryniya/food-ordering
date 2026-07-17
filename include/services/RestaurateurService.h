
#ifndef FOOD_ORDERING_SYSTEM_RESTAURATEURSERVICE_H
#define FOOD_ORDERING_SYSTEM_RESTAURATEURSERVICE_H
#include "dao/MenuDAO.h"
#include "dao/OrderDAO.h"
#include "dao/RestaurantDAO.h"
#include "models/Restaurateur.h"
#include "models/Restaurant.h"
#include "services/Order.h"

class RestaurateurService {
public:
    RestaurateurService();
    bool insertRestaurant (const Restaurateur& owner, const std::string name);
    bool editRestaurant (const Restaurant& restaurant);
    bool deleteRestaurant (int restaurantId);
    bool changeRestaurantStatus (int restaurantId, bool isOpen);
    Restaurant getRestaurant (int restaurantId);
    std::vector<Restaurant> getRestaurants(int ownerId);

    bool addMenuItem(const Menu& item);
    bool editMenuItem(const Menu& item);
    bool deleteMenuItem(const Menu& item);
    bool changeMenuItemPrice(int itemId, double newPrice);
    bool changeMenuItemAvailability(int itemId, bool available);
    std::vector<Menu> getMenuItems(int restaurantId);

    std::vector<Order> getRestaurantOrders(int restaurantId);
    std::vector<Order> getPendingOrders(int restaurantId);
    bool acceptOrder(int orderId);
    bool cancelOrder(int orderId);
    bool readyOrder(int orderId);
    bool deliveredOrder(int orderId);
    bool changeOrderStatus(int orderId, OrderStatus status);

private:
    RestaurantDAO restaurantDAO;
    MenuDAO menuDAO;
    OrderDAO orderDAO;
};

#endif //FOOD_ORDERING_SYSTEM_RESTAURATEURSERVICE_H