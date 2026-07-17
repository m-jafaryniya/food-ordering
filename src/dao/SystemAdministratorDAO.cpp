
#include "dao/SystemAdministratorDAO.h"
#include "models/SystemAdministrator.h"
#include "models/User.h"

SystemAdministratorDAO::SystemAdministratorDAO(Database* database) {
    this->database = database;
}

void SystemAdministratorDAO::insertSystemAdministrator(const SystemAdministrator& systemAdministrator) {
    std::string sql = "INSERT INTO SYSTEM_ADMINISTRATOR ( PHONE, PASSWORD, USERNAME, ID) VALUES ('" +
    systemAdministrator.getPhoneNumber() + "', '" +
        systemAdministrator.getPassword() + "', '" +
            systemAdministrator.getUserName() + "', '" +
                std::to_string(systemAdministrator.getId()) + "');";
    char* messageError;
    int exit = sqlite3_exec(database->getConnection(), sql.c_str(), nullptr, 0, &messageError);
    if (exit != SQLITE_OK) {
        std::cerr << "Error Insert : " << messageError << std::endl;
        sqlite3_free(messageError);
    } else {
        std::cout << "Records created successfully!" << std::endl;
    }
}

static int callbackExists(void* data, int argc, char** argv, char** azColName) {
    bool* exists = static_cast<bool*>(data);
    *exists = true;
    return 0;
}

bool SystemAdministratorDAO::existByPhone(const std::string &phone) {
    bool exists = false;
    std::string sql = "SELECT ID FROM SYSTEM_ADMINISTRATOR WHERE PHONE='" + phone + "';";
    char *messageError;
    sqlite3_exec(database->getConnection(), sql.c_str(), callbackExists, &exists, &messageError);
    if (messageError) {
        sqlite3_free(messageError);
    }
    return exists;
}

static int callbackSystemAdministratorByPhone(void* data, int argc, char** argv, char** azColName) {
    SystemAdministrator* systemAdministrator = static_cast<SystemAdministrator*>(data);
    systemAdministrator->setPhoneNumber(argv[0]);
    systemAdministrator->setPassword(argv[1]);
    systemAdministrator->setUserName(argv[2]);
    systemAdministrator->setId(std::atoi(argv[3]));
    return 0;
}

SystemAdministrator SystemAdministratorDAO::getSystemAdministratorByPhone(const std::string& phone) {
    SystemAdministrator systemAdministrator;
    char* messageError = nullptr;
    std::string sql = "SELECT PHONE, PASSWORD, USERNAME, ID ""FROM SYSTEM_ADMINISTRATOR WHERE PHONE='" + phone + "';";
    sqlite3_exec(database->getConnection(), sql.c_str(), callbackSystemAdministratorByPhone, &systemAdministrator, &messageError);
    if (messageError) {
        sqlite3_free(messageError);
    }
    return systemAdministrator;
}

static int callbackPassword(void* data, int argc, char** argv, char** azColName) {
    std::string* password = static_cast<std::string*>(data);
    *password = argv[0];
    return 0;
}

bool SystemAdministratorDAO::checkPassword(const std::string &phone, const std::string &password) {
    std::string dbPassword;
    std::string sql = "SELECT PASSWORD FROM SYSTEM_ADMINISTRATOR ""WHERE PHONE='" + phone + "';";
    char *messageError;
    sqlite3_exec(database->getConnection(), sql.c_str(), callbackPassword, &dbPassword, &messageError);
    if (messageError) {
        sqlite3_free(messageError);
    }
    return dbPassword == password;
}
