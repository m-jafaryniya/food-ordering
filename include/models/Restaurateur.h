
#ifndef FOOD_ORDERING_SYSTEM_RESTAURATEUR_H
#define FOOD_ORDERING_SYSTEM_RESTAURATEUR_H
#include <vector>
#include "User.h"
class Restaurant;

class Restaurateur : public User {
    public:
    Restaurateur();
    ~Restaurateur() override = default;
    Restaurateur(const std::string &phoneNumber, const std::string &password, const std::string &userName);
    void addRestaurant(const Restaurant* restaurant);
    void removeRestaurant(const Restaurant* restaurant);
    std::vector<Restaurant*>& getRestaurants();
    void showRestaurants() const;

    private:
    std::vector<Restaurant*> restaurants;
};

#endif //FOOD_ORDERING_SYSTEM_RESTAURATEUR_H