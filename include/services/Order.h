
#ifndef FOOD_ORDERING_SYSTEM_ORDER_H
#define FOOD_ORDERING_SYSTEM_ORDER_H
#include <vector>

#include "CartItem.h"

enum class OrderStatus {
    pending,
    preparing,
    ready,
    delivered,
    cancelled
};

class Order {
    public:
    Order();
    Order(int id, int customerId, int restaurantId, const std::vector<CartItem>& items, double totalPrice, OrderStatus status);
    void set_orderId(int id);
    void set_customerId(int id);
    void set_restaurantId(int id);
    void set_status(OrderStatus status);
    void set_totalPrice(double price);

    int get_orderId() const;
    int get_customerId() const;
    int get_restaurantId() const;
    double get_totalPrice() const;

    OrderStatus get_status() const;
    std::vector<CartItem>& get_cartItems();

    private:
    int orderId;
    int customerId;
    int restaurantId;
    std::vector<CartItem> items;
    double totalPrice;
    OrderStatus status;
};

#endif //FOOD_ORDERING_SYSTEM_ORDER_H