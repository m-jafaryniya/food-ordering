
#ifndef FOOD_ORDERING_SYSTEM_CARTITEM_H
#define FOOD_ORDERING_SYSTEM_CARTITEM_H

#include "models/Menu.h"

class CartItem {
    public:
    CartItem();
    virtual ~CartItem();
    CartItem(int itemId, int quantity, double unitprice);
    int get_itemId() const;
    int get_quantity() const;
    double get_unitPrice() const;
    void set_itemId(int id);
    void set_quantity(int quantity);
    void set_unitPrice(double unitPrice);
    double get_totalPrice() const;

    private:
    int itemId;
    int quantity;
    double unitPrice;

};

#endif //FOOD_ORDERING_SYSTEM_CARTITEM_H