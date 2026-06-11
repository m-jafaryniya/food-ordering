
#ifndef FOOD_ORDERING_SYSTEM_DRINK_H
#define FOOD_ORDERING_SYSTEM_DRINK_H
#include "Menu.h"

class Drink : public Menu {
    public:
    Drink();
    Drink(const std::string& ItemName, const std::string& ItemDescription,  double basePrice, int volume);
    std::string get_ItemType() override;
    void set_volume(int volume);
    int get_volume() const;

    private:
    int volume;
};

#endif //FOOD_ORDERING_SYSTEM_DRINK_H