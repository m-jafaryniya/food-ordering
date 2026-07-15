
#ifndef FOOD_ORDERING_SYSTEM_MENU_H
#define FOOD_ORDERING_SYSTEM_MENU_H
#include <string>

class Menu {
    public:
    Menu();
    Menu(const std::string &ItemName, const std::string &ItemDescription, double basePrice);
    virtual ~Menu();
    virtual std::string get_ItemType()=0;
    void set_ItemId(int id);
    void set_ItemName(const std::string& name);
    void set_ItemDescription(const std::string& description);
    void set_BasePrice(double price);
    void set_available(bool available);
    int get_ItemId() const;
    std::string get_ItemName() const;
    std::string get_ItemDescription() const;
    double get_BasePrice() const;
    bool get_available() const;

    private:
    int ItemId;
    std::string ItemName;
    std::string ItemDescription;
    double basePrice;
    bool available;
};

#endif //FOOD_ORDERING_SYSTEM_MENU_H