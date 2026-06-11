
#include "models/Drink.h"

Drink::Drink() {}

Drink::Drink(const std::string &ItemName, const std::string &ItemDescription, const double basePrice, const int volume)
:Menu(ItemName, ItemDescription, basePrice) {
    this->volume = volume;
}

std::string Drink::get_ItemType() {
    return "Drink" ;
}

void Drink::set_volume(int volume) {
    this->volume = volume;
}

int Drink::get_volume() const {
    return this->volume;
}
