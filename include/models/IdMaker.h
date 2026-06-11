
#ifndef FOOD_ORDERING_SYSTEM_IDMAKER_H
#define FOOD_ORDERING_SYSTEM_IDMAKER_H

class IdMaker {
    public:
    IdMaker();
    virtual ~IdMaker();

    static int FoodID;

    static int get_UserID();
    static int get_RestaurantID();
    static int get_MenuID();

    private:
    static int UserID;
    static int RestaurantID;
    static int MenuID;
};

#endif //FOOD_ORDERING_SYSTEM_IDMAKER_H