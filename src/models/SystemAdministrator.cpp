
#include "models/SystemAdministrator.h"

#include "dao/Database.h"

SystemAdministrator::SystemAdministrator() {}

SystemAdministrator::SystemAdministrator(const std::string &phoneNumber, const std::string &password, const std::string &userName)
    :User(phoneNumber, password, userName)
{}

