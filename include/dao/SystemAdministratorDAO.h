
#ifndef FOOD_ORDERING_SYSTEM_SYSTEMADMINISTRATORDAO_H
#define FOOD_ORDERING_SYSTEM_SYSTEMADMINISTRATORDAO_H
#include <string>

#include "dao/Database.h"
#include "models/SystemAdministrator.h"

class SystemAdministratorDAO {
    public:
    SystemAdministratorDAO(Database* database);
    void insertSystemAdministrator(const SystemAdministrator& systemAdministrator);
    void deleteSystemAdministrator();
    bool existByPhone(const std::string& phone);
    SystemAdministrator getSystemAdministratorByPhone(const std::string& phone);
    bool checkPassword(const std::string& phone, const std::string& password);

    private:
    Database* database;
};

#endif //FOOD_ORDERING_SYSTEM_SYSTEMADMINISTRATORDAO_H