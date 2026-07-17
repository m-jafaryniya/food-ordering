
#include "dao/RestaurateurDAO.h"
#include "models/Restaurateur.h"
#include "models/User.h"

RestaurateurDAO::RestaurateurDAO(Database *database) {
    this->database = database;
}

bool RestaurateurDAO::insertRestaurateur(const Restaurateur &restaurateur) {
    std::string sql = "INSERT INTO RESTAURATEUR ( PHONE, PASSWORD, USERNAME, ID) VALUES (?,?,?);" ;
    sqlite3_stmt *stmt = nullptr;
    if (sqlite3_prepare_v2(database->getConnection(),sql.c_str(),-1,&stmt,nullptr) != SQLITE_OK) {
        return false;
    }
    sqlite3_bind_text(stmt,1,restaurateur.getPhoneNumber().c_str(),-1,SQLITE_TRANSIENT);
    sqlite3_bind_text(stmt,2,restaurateur.getPassword().c_str(),-1,SQLITE_TRANSIENT);
    sqlite3_bind_text(stmt,3,restaurateur.getUserName().c_str(),-1,SQLITE_TRANSIENT);
    sqlite3_bind_int(stmt,4,restaurateur.getId());

    bool success = (sqlite3_step(stmt) == SQLITE_DONE);
    sqlite3_finalize(stmt);
    return success;
}

bool RestaurateurDAO::deleteRestaurateur(const Restaurateur &restaurateur) {
    std::string sql_delete = "DELETE FROM RESTAURATEUR WHERE ID =?;";
    sqlite3_stmt *stmt = nullptr;
    if (sqlite3_prepare_v2(database->getConnection(),sql_delete.c_str(),-1,&stmt,nullptr) != SQLITE_OK) {
        return false;
    }
    sqlite3_bind_int(stmt,1,restaurateur.getId());

    bool success = (sqlite3_step(stmt) == SQLITE_DONE);
    sqlite3_finalize(stmt);
    return success;
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
    restaurateur->setPhoneNumber(argv[0]);
    restaurateur->setPassword(argv[1]);
    restaurateur->setUserName(argv[2]);
    restaurateur->setId(std::atoi(argv[3]));
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

static int callbackGetRestaurateurs(void* data, int argc, char** argv, char** azColName) {
    std::vector<Restaurateur>* restaurateurs = static_cast<std::vector<Restaurateur>*>(data);
    Restaurateur restaurateur;
    restaurateur.setPhoneNumber(argv[0] ? argv[0] : "");
    restaurateur.setPassword(argv[1] ? argv[1] : "");
    restaurateur.setUserName(argv[2] ? argv[2] : "");
    restaurateur.setId(std::atoi(argv[3]));
    restaurateurs->push_back(restaurateur);
    return 0;
}

std::vector<Restaurateur> RestaurateurDAO::getRestaurateurs() {
    std::vector<Restaurateur> restaurateurs;
    std::string sql = "SELECT PHONE, PASSWORD, USERNAME, ID FROM RESTAURATEUR;";

    char *messageError = nullptr;
    sqlite3_exec(database->getConnection(), sql.c_str(), callbackGetRestaurateurs, &restaurateurs, &messageError);
    if (messageError) {
        std::cerr << "Error : " << messageError << std::endl;
        sqlite3_free(messageError);
    }
    return restaurateurs;
}
