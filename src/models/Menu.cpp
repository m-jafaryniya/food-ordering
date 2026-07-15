
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

void Menu::set_ItemId(const int id) {
    this->ItemId = id;
}

void Menu::set_ItemName(const std::string &name) {
    this->ItemName = name;
}

void Menu::set_ItemDescription(const std::string &description) {
    this->ItemDescription = description;
}

void Menu::set_BasePrice(const double price) {
    basePrice = price;
}

void Menu::set_available(bool available) {
    this->available = available;
}

int Menu::get_ItemId() const {
    return ItemId;
}

std::string Menu::get_ItemName() const {
    return ItemName;
}

std::string Menu::get_ItemDescription() const {
    return ItemDescription;
}

double Menu::get_BasePrice() const {
    return basePrice;
}

bool Menu::get_available() const {
    return available;
}