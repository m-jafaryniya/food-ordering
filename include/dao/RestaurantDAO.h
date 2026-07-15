
#ifndef FOOD_ORDERING_SYSTEM_RESTAURANTDAO_H
#define FOOD_ORDERING_SYSTEM_RESTAURANTDAO_H

#include <vector>

#include "dao/Database.h"
#include "models/Restaurant.h"

class RestaurantDAO {
public:
    RestaurantDAO(Database* database);
    void insertRestaurant(const Restaurant& restaurant);
    void deleteRestaurant(const Restaurant& restaurant);
    bool updateRestaurant(const Restaurant& restaurant);
    Restaurant getRestaurantById(int Id);
    std::vector<Restaurant> getRestaurants();

private:
    Database* database;
};

#endif //FOOD_ORDERING_SYSTEM_RESTAURANTDAO_H