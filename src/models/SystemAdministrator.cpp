
#include "models/SystemAdministrator.h"

SystemAdministrator::SystemAdministrator() {}

SystemAdministrator::SystemAdministrator(const std::string &phoneNumber, const std::string &password, const std::string &userName)
    :User(phoneNumber, password, userName)
{}

SystemAdministrator::~SystemAdministrator() {}
