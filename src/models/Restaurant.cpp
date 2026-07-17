
#include "models/Restaurant.h"
#include "models/Menu.h"
#include "models/IdMaker.h"

Restaurant::Restaurant() {}

Restaurant::Restaurant(const std::string& name,
    const Address& address, bool active,
    int OperationTime, const std::string& phone, const std::string& information) {
    Id = IdMaker::getRestaurantID();
    this->name = name;
    this->address = address;
    this->active = active;
    this->operationTime = OperationTime;
    this->phone = phone;
    this->information = information;
}

Restaurant::~Restaurant(){}

int Restaurant::getID() const {
    return Id;
}

std::string Restaurant::getName() const {
    return name;
}

const Address& Restaurant::getAddress() const {
    return address;
}

bool Restaurant::getActive() const {
    return active;
}

int Restaurant::getOperationTime() const {
    return operationTime;
}

std::string Restaurant::getPhone() const
{
    return phone;
}

std::string Restaurant::getInformation() const {
    return information;
}

int Restaurant::getOwnerId() const {
    return ownerId;
}

void Restaurant::setId(int id) {
    this->Id = id;
}

void Restaurant::setName(const std::string& name) {
    this->name = name;
}

void Restaurant::setAddress(const Address& address) {
    this->address = address;
}

void Restaurant::setActive(bool active) {
    this->active = active;
}

void Restaurant::setOperationTime(int operationTime) {
    this->operationTime = operationTime;
}

void Restaurant::setPhone(const std::string& phone) {
    this-> phone = phone;
}

void Restaurant::setInformation(const std::string& information) {
    this->information = information;
}

void Restaurant::setOwnerId(const int ownerId) {
    this->ownerId = ownerId;
}

void Restaurant::addMenuItem(Menu *menu) {
    menuList.push_back(menu);
}

void Restaurant::removeMenuItemById(int id) {
    for (auto it = menuList.begin(); it != menuList.end(); ++it) {
        if ((*it)->get_ItemId() == id) {
            delete *it;
            menuList.erase(it);
            return;
        }
    }
}

std::vector<Menu *>& Restaurant::getMenuList() {
    return menuList;
}
