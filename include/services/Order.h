
#ifndef FOOD_ORDERING_SYSTEM_ORDER_H
#define FOOD_ORDERING_SYSTEM_ORDER_H
#include <vector>

#include "CartItem.h"

class Order {
    public:
    Order();
    void set_orderId(int id);
    void set_customerId(int id);
    void set_restaurantId(int id);
    void set_delivered(bool delivered);

    int get_orderId();
    int get_customerId();
    int get_restaurantId();
    double get_totalPrice();
    bool get_delivered();
    std::vector<CartItem>& get_cartItems();

    private:
    int orderId;
    int customerId;
    int restaurantId;
    std::vector<CartItem> cartItems;
    bool delivered;
};

#endif //FOOD_ORDERING_SYSTEM_ORDER_H