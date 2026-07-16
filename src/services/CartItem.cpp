
#include "services/CartItem.h"

CartItem::CartItem() {
    itemId=0;
    quantity =0;
}

CartItem::CartItem(int itemId, int quantity, double unitprice) {
    this->itemId = itemId;
    this->quantity = quantity;
    this->unitPrice = unitprice;
}

int CartItem::get_itemId() const {
    return itemId;
}

int CartItem::get_quantity() const {
    return quantity;
}

double CartItem::get_unitPrice() const {
    return unitPrice;
}

void CartItem::set_itemId(int itemId) {
    this->itemId = itemId;
}

void CartItem::set_quantity(int quantity) {
    this->quantity = quantity;
}

void CartItem::set_unitPrice(double unitPrice) {
    this->unitPrice = unitPrice;
}

double CartItem::get_totalPrice() const {
    return quantity*unitPrice;
}
