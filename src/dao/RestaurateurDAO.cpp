
#include "dao/RestaurateurDAO.h"
#include "models/Restaurateur.h"
#include "models/User.h"

RestaurateurDAO::RestaurateurDAO(Database *database) {
    this->database = database;
}

void RestaurateurDAO::insertRestaurateur(const Restaurateur &restaurateur) {
    std::string sql = "INSERT INTO RESTAURATEUR ( PHONE, PASSWORD, USERNAME, ID) VALUES ('" +
    restaurateur.get_phoneNumber() + "', '" +
        restaurateur.get_password() + "', '" +
            restaurateur.get_userName() + "', '" +
                std::to_string(restaurateur.get_id()) + "');";
    char* messageError;
    int exit = sqlite3_exec(database->getConnection(), sql.c_str(), NULL, 0, &messageError);
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

bool RestaurateurDAO::existByPhone(const std::string &phone) {
    bool exists = false;
    std::string sql = "SELECT ID FROM RESTAURATEUR WHERE PHONE='" + phone + "';";
    char *messageError;
    sqlite3_exec(database->getConnection(), sql.c_str(), callbackExists, &exists, &messageError);
    if (messageError) {
        sqlite3_free(messageError);
    }
    return exists;
}

static int callbackRestaurateurByPhone(void* data, int argc, char** argv, char** azColName) {
    Restaurateur* restaurateur = static_cast<Restaurateur*>(data);
    restaurateur->set_phoneNumber(argv[0]);
    restaurateur->set_password(argv[1]);
    restaurateur->set_userName(argv[2]);
    restaurateur->set_id(std::atoi(argv[3]));
    return 0;
}

Restaurateur RestaurateurDAO::getRestaurateurByPhone(const std::string& phone) {
    Restaurateur restaurateur;
    char* messageError = nullptr;
    std::string sql = "SELECT PHONE, PASSWORD, USERNAME, ID ""FROM RESTAURATEUR WHERE PHONE='" + phone + "';";
    sqlite3_exec(database->getConnection(), sql.c_str(), callbackRestaurateurByPhone, &restaurateur, &messageError);
    if (messageError) {
        sqlite3_free(messageError);
    }
    return restaurateur;
}

static int callbackPassword(void* data, int argc, char** argv, char** azColName) {
    std::string* password = static_cast<std::string*>(data);
    *password = argv[0];
    return 0;
}

bool RestaurateurDAO::checkPassword(const std::string &phone, const std::string &password) {
    std::string dbPassword;
    std::string sql = "SELECT PASSWORD FROM RESTAURATEUR ""WHERE PHONE='" + phone + "';";
    char *messageError;
    sqlite3_exec(database->getConnection(), sql.c_str(), callbackPassword, &dbPassword, &messageError);
    if (messageError) {
        sqlite3_free(messageError);
    }
    return dbPassword == password;
}
