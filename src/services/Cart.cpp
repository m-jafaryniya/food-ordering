
#include "services/Cart.h"

Cart::Cart() {
    customerId = 0;
}

Cart::Cart(int customerId) {
    this->customerId = customerId;
}

Cart::~Cart() {

}

int Cart::get_customerId() const {
    return customerId;
}

std::vector<CartItem> Cart::get_items() const {
    return items;
}

void Cart::addItem(int itemId, double unitPrice, int quantity) {
    items.push_back(CartItem(itemId, quantity, unitPrice));
}

void Cart::removeItem(int itemId) {
    for (auto it = items.begin(); it != items.end(); it++) {
        if (it->get_itemId() == itemId) {
            items.erase(it);
            break;
        }
    }
}

void Cart::clear() {
    items.clear();
}

double Cart::get_totalPrice() const {
    double totalPrice = 0;
    for (const CartItem& item : items) {
        totalPrice += item.get_totalPrice();
    }
    return totalPrice;
}
