
#include "models/Menu.h"
#include "models/IdMaker.h"

Menu::Menu() {}

Menu::Menu(const std::string &ItemName, const std::string &ItemDescription, const double basePrice) {
    this->ItemId = IdMaker::get_MenuID();
    this->ItemName = ItemName;
    this->ItemDescription = ItemDescription;
    this->basePrice = basePrice;
}

Menu::~Menu() {}
