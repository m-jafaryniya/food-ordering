
#ifndef FOOD_ORDERING_SYSTEM_CART_H
#define FOOD_ORDERING_SYSTEM_CART_H

#include <vector>

#include "services/CartItem.h"

class Cart {
    public:
    Cart();
    virtual ~Cart();
    Cart(int customerId);
    int get_customerId() const;

    std::vector<CartItem> get_items() const;
    void addItem(int itemId, const std::string& itemType, int quantity);
    void removeItem(int itemId);
    void clear();
    double get_totalPrice() const;

    private:
    int customerId;
    std::vector<CartItem> items;
};

#endif //FOOD_ORDERING_SYSTEM_CART_H