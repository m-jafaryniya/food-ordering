

#ifndef FOOD_ORDERING_SYSTEM_RESTAURATEURDAO_H
#define FOOD_ORDERING_SYSTEM_RESTAURATEURDAO_H
#include "models/Restaurateur.h"
#include "dao/Database.h"

class RestaurateurDAO {
    public:
    RestaurateurDAO(Database* database);
    bool insertRestaurateur(const Restaurateur& restaurateur);
    bool deleteRestaurateur(const Restaurateur& restaurateur);
    bool existByPhone(const std::string& phone);
    Restaurateur getRestaurateurByPhone(const std::string& phone);
    bool checkPassword(const std::string& phone, const std::string& password);

    private:
    Database* database;
};

#endif //FOOD_ORDERING_SYSTEM_RESTAURATEURDAO_H