
#include "services/Order.h"

Order::Order() {
    orderId=0;
    customerId=0;
    restaurantId=0;
    delivered=false;
}

void Order::set_orderId(int id) {
    orderId=id;
}

void Order::set_customerId(int id) {
    customerId=id;
}
void Order::set_restaurantId(int id) {
    restaurantId=id;
}

void Order::set_delivered(bool delivered) {
    this->delivered=delivered;
}

int Order::get_orderId() {
    return orderId;
}

int Order::get_customerId() {
    return customerId;
}

int Order::get_restaurantId() {
    return restaurantId;
}

double Order::get_totalPrice() {
    double totalPrice=0;
    for (const CartItem& item : cartItems) {
        totalPrice += item.get_totalPrice();
    }
    return totalPrice;
}

bool Order::get_delivered() {
    return delivered;
}

std::vector<CartItem>& Order::get_cartItems() {
    return cartItems;
}
