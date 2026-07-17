
#ifndef FOOD_ORDERING_SYSTEM_IDMAKER_H
#define FOOD_ORDERING_SYSTEM_IDMAKER_H

class IdMaker {
    public:

    static int getUserID();
    static int getRestaurantID();
    static int getMenuID();

    private:
    static int UserID;
    static int RestaurantID;
    static int MenuID;
};

#endif //FOOD_ORDERING_SYSTEM_IDMAKER_H