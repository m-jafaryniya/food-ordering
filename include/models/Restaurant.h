
#ifndef FOOD_ORDERING_SYSTEM_RESTAURANT_H
#define FOOD_ORDERING_SYSTEM_RESTAURANT_H
#include <string>
#include <vector>

class Menu;
#include "models/Address.h"

class Restaurant {
public:
    Restaurant();
    Restaurant(const std::string& name,
        const Address& address, bool active, int OperationTime,
        const std::string& phone, const std::string& information);
    ~Restaurant();
    int getID() const;
    std::string getName() const;
    const Address& getAddress() const;
    bool getActive() const;
    int getOperationTime() const;
    std::string getPhone() const;
    std::string getInformation() const;
    int getOwnerId() const;
    void setId(int id);
    void setName(const std::string &name);
    void setAddress(const Address& address);
    void setActive(bool active);
    void setOperationTime(int operationTime);
    void setPhone(const std::string& phone);
    void setInformation(const std::string& information);
    void setOwnerId(int ownerId);
    void addMenuItem(Menu *menu);
    void removeMenuItemById(int id);
    std::vector<Menu *>& getMenuList();

private:
    int Id;
    std::string name;
    Address address;
    bool active;
    int operationTime;
    std::string phone;
    std::string information;
    int ownerId;
    std::vector<Menu *> menuList;
};

#endif //FOOD_ORDERING_SYSTEM_RESTAURANT_H