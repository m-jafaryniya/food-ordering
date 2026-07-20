
#include "services/Order.h"

Order::Order() {
    orderId=0;
    customerId=0;
    restaurantId=0;
    totalPrice=0;
    status=OrderStatus::pending;
}

Order::Order(int id, int customerId, int restaurantId, const std::vector<CartItem> &items, double totalPrice, OrderStatus status) {
    orderId=id;
    this->customerId=customerId;
    this->restaurantId=restaurantId;
    this->items=items;
    this->totalPrice=totalPrice;
    this->status=status;
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

void Order::set_status(OrderStatus status) {
    this->status=status;
}

void Order::set_totalPrice(double price) {
    totalPrice=price;
}

int Order::get_orderId() const {
    return orderId;
}

int Order::get_customerId() const {
    return customerId;
}

int Order::get_restaurantId() const {
    return restaurantId;
}

double Order::get_totalPrice() const {
    if (totalPrice > 0) {
        return totalPrice;
    }
    double TotalPrice=0;
    for (const CartItem& item : items) {
        TotalPrice += item.get_totalPrice();
    }
    return TotalPrice;
}

OrderStatus Order::get_status() const {
    return status;
}

std::vector<CartItem>& Order::get_cartItems() {
    return items;
}
