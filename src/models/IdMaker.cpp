
#include "models/IdMaker.h"

int IdMaker::UserID=10000;
int IdMaker::RestaurantID=10000;
int IdMaker::FoodID=1;

int IdMaker::get_UserID() {
    return UserID++;
}

int IdMaker::get_RestaurantID() {
    return RestaurantID++;
}

int IdMaker::get_MenuID() {
    return MenuID++;
}
