
#include "models/Food.h"

Food::Food() {}

Food::Food(const std::string& ItemName, const std::string& ItemDescription, const double basePrice, const int cookTime)
:Menu(ItemName,ItemDescription,basePrice) {
    this->cookTime = cookTime;
}

std::string Food::get_ItemType() {
    return "Food";
}

void Food::set_cookTime(int cookTime) {
    this->cookTime = cookTime;
}

int Food::get_cookTime() const {
    return this->cookTime;
}