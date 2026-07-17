
#include "models/Restaurateur.h"

#include <iostream>
#include <ostream>

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
    for (auto it = restaurants.begin(); it != restaurants.end(); it++) {
        if ((*it)->getID() == restaurant->getID()) {
            restaurants.erase(it);
            return;
        }
    }
}

std::vector<Restaurant*>& Restaurateur::getRestaurants() {
    return restaurants;
}

void Restaurateur::showRestaurants() const {
    if (restaurants.empty()) {
        std::cout << "No restaurants!" << std::endl;
        return;
    }

    std::cout << "---Restaurants---" << std::endl;
    for (const Restaurant* restaurant : restaurants) {
        std::cout << "ID: " << restaurant->getID() << std::endl;
        std::cout << "Name: " << restaurant->getName() << std::endl;
        std::cout << "Active : " << (restaurant->getActive() ? "Yes" : "No") << std::endl;
    }
}