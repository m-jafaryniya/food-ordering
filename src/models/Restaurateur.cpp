
#include "models/Restaurateur.h"
#include "models/Restaurant.h"
#include <vector>

Restaurateur::Restaurateur() {}

Restaurateur::Restaurateur(const std::string &phoneNumber, const std::string &password, const std::string &userName)
:User(phoneNumber, password, userName)
{}

void Restaurateur::addRestaurant(Restaurant *restaurant) {
    restaurants.push_back(restaurant);
}

void Restaurateur::removeRestaurant(const Restaurant *restaurant) {

}

std::vector<Restaurant*>& Restaurateur::getRestaurants() {
    return restaurants;
}

void Restaurateur::showRestaurants() const {

}