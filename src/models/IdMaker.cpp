
#include "models/IdMaker.h"

int IdMaker::UserID=10000;
int IdMaker::RestaurantID=10000;
int IdMaker::MenuID = 1;

int IdMaker::getUserID() {
    return UserID++;
}

int IdMaker::getRestaurantID() {
    return RestaurantID++;
}

int IdMaker::getMenuID() {
    return MenuID++;
}
