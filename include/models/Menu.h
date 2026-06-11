
#ifndef FOOD_ORDERING_SYSTEM_MENU_H
#define FOOD_ORDERING_SYSTEM_MENU_H
#include <string>

class Menu {
    public:
    Menu();
    Menu(const std::string &ItemName, const std::string &ItemDescription, double basePrice);
    virtual ~Menu();
    virtual std::string get_ItemType()=0;

    private:
    int ItemId;
    std::string ItemName;
    std::string ItemDescription;
    double basePrice;
    bool available;
};

#endif //FOOD_ORDERING_SYSTEM_MENU_H