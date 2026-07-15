
#include "services/CartItem.h"

CartItem::CartItem() {
    itemId=0;
    itemType="";
    quantity =0;
}

CartItem::CartItem(int itemId,const std::string& itemType, int quantity) {
    this->itemId=itemId;
    this->itemType=itemType;
    this->quantity = quantity;
}

int CartItem::get_itemId() const {
    return itemId;
}

std::string CartItem::get_itemType() const {
    return itemType;
}

int CartItem::get_quantity() const {
    return quantity
}

void CartItem::set_itemId(int itemId) {
    this->itemId = itemId;
}

void CartItem::set_itemType(const std::string& itemType) {
    this->itemType = itemType;
}

void CartItem::set_quantity(int quantity) {
    this->quantity = quantity;
}

double CartItem::get_totalPrice() const {
    double totalP = item->get_BasePrice()*quantity;
    return totalP;
}
