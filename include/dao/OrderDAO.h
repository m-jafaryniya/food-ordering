
#ifndef FOOD_ORDERING_SYSTEM_ORDERDAO_H
#define FOOD_ORDERING_SYSTEM_ORDERDAO_H

#include "services/Order.h"
#include "dao/Database.h"

class OrderDAO {
    public:
    OrderDAO(Database* database);
    bool insertOrder(const Order& order);
    bool insertOrderItems(int orderId, const std::vector<CartItem>& items);
    bool deleteOrder(int orderId);
    Order getOrderById(int id);
    std::vector<CartItem> getOrderItems(int orderId);
    std::vector<Order> getCustomerOrders(int customerId);
    std::vector<Order> getRestaurantOrders(int restaurantId);
    bool updateOrderStatus(int orderId, OrderStatus status);
    bool deleteOrderItems(int orderId);

    private:
    Database* database;
    std::string statusToString(OrderStatus status);
    OrderStatus stringToStatus(const std::string& status);

};

#endif //FOOD_ORDERING_SYSTEM_ORDERDAO_H