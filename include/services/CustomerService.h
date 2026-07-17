
#ifndef FOOD_ORDERING_SYSTEM_CUSTOMERSERVICE_H
#define FOOD_ORDERING_SYSTEM_CUSTOMERSERVICE_H
#include <vector>

#include "dao/CustomerDAO.h"
#include "dao/MenuDAO.h"
#include "dao/OrderDAO.h"
#include "dao/RestaurantDAO.h"
#include "services/Order.h"
#include "services/Cart.h"
#include "models/Restaurant.h"

class CustomerService {
    public:
    CustomerService(Database* database);
    std::vector<Restaurant> getAllRstaurants();
    std::vector<Menu*> getRestaurantMenu(int restaurantId);
    bool addToCart(int restaurantId, int itemId, int quantity);
    void removeFromCart(int itemId);
    void clearCart();
    Cart getCart();
    double calculateCost();
    bool placeOrder(int customerId, int restaurantId);
    std::vector<Order> getOrders(int customerId);

    private:
    Cart cart;
    CustomerDAO customerDAO;
    RestaurantDAO restaurantDAO;
    MenuDAO menuDAO;
    OrderDAO orderDAO;
};

#endif //FOOD_ORDERING_SYSTEM_CUSTOMERSERVICE_H