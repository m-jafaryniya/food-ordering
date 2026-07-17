
#ifndef FOOD_ORDERING_SYSTEM_SYSTEMADMINISTRATORDAO_H
#define FOOD_ORDERING_SYSTEM_SYSTEMADMINISTRATORDAO_H
#include <string>

#include "dao/Database.h"
#include "models/SystemAdministrator.h"

class SystemAdministratorDAO {
    public:
    SystemAdministratorDAO(Database* database);
    bool insertSystemAdministrator(const SystemAdministrator& systemAdministrator);
    bool deleteSystemAdministrator(const SystemAdministrator& systemAdministrator);
    bool existByPhone(const std::string& phone);
    SystemAdministrator getSystemAdministratorByPhone(const std::string& phone);
    bool checkPassword(const std::string& phone, const std::string& password);

    private:
    Database* database;
};

#endif //FOOD_ORDERING_SYSTEM_SYSTEMADMINISTRATORDAO_H