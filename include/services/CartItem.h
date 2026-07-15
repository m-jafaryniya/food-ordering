
#ifndef FOOD_ORDERING_SYSTEM_CARTITEM_H
#define FOOD_ORDERING_SYSTEM_CARTITEM_H

#include "models/Menu.h"

class CartItem {
    public:
    CartItem();
    virtual ~CartItem();
    CartItem(int itemId, const std::string& itemType, int quantity);
    int get_itemId() const;
    std::string get_itemType() const;
    int get_quantity() const;
    void set_itemId(int id);
    void set_itemType(const std::string& itemType);
    void set_quantity(int quantity);
    double get_totalPrice() const;

    private:
    int itemId;
    std::string itemType;
    int quantity;

};

#endif //FOOD_ORDERING_SYSTEM_CARTITEM_H