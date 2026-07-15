
#ifndef FOOD_ORDERING_SYSTEM_CARTDAO_H
#define FOOD_ORDERING_SYSTEM_CARTDAO_H

#include "services/Cart.h"
#include "dao/Database.h"

class CartDAO {
    public:
    CartDAO(Database* database);
    bool addItem(int customerId, int itemId, const std::string& itemType, int quantity);
    bool deleteItem(int customerId, int itemId, const std::string& itemType);
    bool updateQuantity(int customerId, int itemId, const std::string& itemType, int quantity);
    Cart get_cart(int customerId);
    bool clear_cart(int customerId);

    private:
    Database* database;
};

#endif //FOOD_ORDERING_SYSTEM_CARTDAO_H