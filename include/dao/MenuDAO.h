
#ifndef FOOD_ORDERING_SYSTEM_MENUDAO_H
#define FOOD_ORDERING_SYSTEM_MENUDAO_H
#include <optional>
#include <string>
#include <vector>
#include "dao/Database.h"
#include "models/Menu.h"
#include "models/Food.h"
#include "models/Drink.h"

class MenuDAO {
    public:
    MenuDAO(Database* database);

    bool addFood(int restaurantId, const Food& food);
    bool updateFood(const Food& food);
    bool deleteFood(int id);
    std::optional<Food> getFoodById(int id);

    bool addDrink(int restaurantId, const Drink& drink);
    bool updateDrink(const Drink& drink);
    bool deleteDrink(int id);
    std::optional<Drink> getDrinkById (int id);

    std::vector<Menu*> getRestaurantMenu(int restaurantId);
    private:
    Database *database;

};

#endif //FOOD_ORDERING_SYSTEM_MENUDAO_H