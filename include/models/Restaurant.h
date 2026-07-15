
#ifndef FOOD_ORDERING_SYSTEM_RESTAURANT_H
#define FOOD_ORDERING_SYSTEM_RESTAURANT_H
#include <string>
#include <vector>

#include "models/Menu.h"
#include "models/Address.h"

class Restaurant {
public:
    Restaurant();
    Restaurant(const std::string& name,
        const Address& address, bool active, int OperationTime,
        const std::string& phone, const std::string& information);
    virtual ~Restaurant();
    int get_ID() const;
    std::string get_name() const;
    Address get_address() const;
    bool get_active() const;
    int get_operationTime() const;
    std::string get_phone() const;
    std::string get_information() const;
    void set_id(int id);
    void set_name(const std::string &name);
    void set_address(const Address& address);
    void set_active(const bool active);
    void set_operationTime(const int operationTime);
    void set_phone(const std::string& phone);
    void set_information(const std::string& information);
    void addMenuItem(Menu *menu);
    void removeMenuItem(int id);
    std::vector<Menu *>& getMenuList();

private:
    int ID;
    std::string name;
    Address address;
    bool active;
    int OperationTime;
    std::string phone;
    std::string information;
    std::vector<Menu *> MenuList;
};

#endif //FOOD_ORDERING_SYSTEM_RESTAURANT_H