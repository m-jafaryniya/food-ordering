
#include "models/Restaurateur.h"
#include "models/Restaurant.h"
#include <vector>

Restaurateur::Restaurateur() {}

Restaurateur::Restaurateur(const std::string &phoneNumber, const std::string &password, const std::string &userName)
:User(phoneNumber, password, userName)
{}

Restaurateur::~Restaurateur() {}

void Restaurateur::add_restaurant(const Restaurant *restaurant) {
    restaurants.push_back(restaurant);
}

void Restaurateur::remove_restaurant(const Restaurant *restaurant) {

}

std::vector<Restaurant*>& Restaurateur::get_restaurants() {
    return restaurants;
}

void Restaurateur::show_restaurants() const {

}
