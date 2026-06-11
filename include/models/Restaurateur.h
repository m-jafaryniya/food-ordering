
#ifndef FOOD_ORDERING_SYSTEM_RESTAURATEUR_H
#define FOOD_ORDERING_SYSTEM_RESTAURATEUR_H
#include "User.h"
#include "Restaurant.h"

class Restaurateur : public User {
    public:
    Restaurateur();
    Restaurateur(const std::string &phoneNumber, const std::string &password, const std::string &userName);
    virtual ~Restaurateur();
    void add_restaurant(const Restaurant* restaurant);
    void remove_restaurant(const Restaurant* restaurant);
    std::vector<Restaurant*>& get_restaurants();
    void show_restaurants() const;

    private:
    std::vector<Restaurant*> restaurants;
};

#endif //FOOD_ORDERING_SYSTEM_RESTAURATEUR_H