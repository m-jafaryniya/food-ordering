
#ifndef FOOD_ORDERING_SYSTEM_FOOD_H
#define FOOD_ORDERING_SYSTEM_FOOD_H
#include "Menu.h"

class Food : public Menu {
    public:
    Food();
    Food(const std::string& ItemName, const std::string& ItemDescription,  double basePrice, int cookTime);
    std::string get_ItemType() override;
    void set_cookTime(int cookTime);
    int get_cookTime() const;

    private:
    int cookTime;
};

#endif //FOOD_ORDERING_SYSTEM_FOOD_H