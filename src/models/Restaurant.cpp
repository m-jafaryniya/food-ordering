
#include "models/Restaurant.h"
#include "models/IdMaker.h"

Restaurant::Restaurant() {}

Restaurant::Restaurant(const std::string& name,
    const Address& address, bool active,
    int OperationTime, const std::string& phone, const std::string& information) {
    ID = IdMaker::get_RestaurantID();
    this->name = name;
    this->address = address;
    this->active = active;
    this->OperationTime = OperationTime;
    this->phone = phone;
    this->information = information;
}

Restaurant::~Restaurant(){}

int Restaurant::get_ID() const {
    return ID;
}

std::string Restaurant::get_name() const {
    return name;
}

Address Restaurant::get_address() {
    return address;
}

bool Restaurant::get_active() const {
    return active;
}

int Restaurant::get_operationTime() const {
    return OperationTime;
}

std::string Restaurant::get_phone() const
{
    return phone;
}

std::string Restaurant::get_information() const {
    return information;
}

void Restaurant::set_name(const std::string& name) {
    this->name = name;
}

void Restaurant::set_address(const Address& address) {
    this->address = address;
}

void Restaurant::set_active(const bool active) {
    this->active = active;
}

void Restaurant::set_operationTime(const int operationTime) {
    this->OperationTime = operationTime;
}

void Restaurant::set_phone(const std::string& phone) {
    this-> phone = phone;
}

void Restaurant::set_information(const std::string& information) {
    this->information = information;
}

void Restaurant::addMenuItem(Menu *menu) {
    MenuList.push_back(menu);
}

void Restaurant::removeMenuItem(int id) {

}

std::vector<Menu *>& Restaurant::getMenuList() {
    return MenuList;
}
