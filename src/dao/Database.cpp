
#include "dao/Database.h"
#include <iostream>

Database::Database(const std::string &FileName) {
    if (sqlite3_open(FileName.c_str(), &db) != SQLITE_OK) {
        std::cout << "Can't open database" << std::endl;
    }
    createTables();
}

Database::~Database() {
    sqlite3_close(db);
}

sqlite3* Database::getConnection() const {
    return db;
}

void Database::createTables() {
    char *errMsg = nullptr;
    const char* customerTable =
        "CREATE TABLE IF NOT EXISTS CUSTOMER("
        "ID INTEGER PRIMARY KEY,"
        "PHONE TEXT UNIQUE NOT NULL,"
        "PASSWORD TEXT NOT NULL,"
        "USERNAME TEXT NOT NULL,"
        "WALLET REAL DEFAULT 0"
        ");";
    if (sqlite3_exec(db, customerTable, nullptr, nullptr, &errMsg) != SQLITE_OK) {
        std::cout << errMsg << std::endl;
        sqlite3_free(errMsg);
    };

    const char* restaurateurTable =
        "CREATE TABLE IF NOT EXISTS RESTAURATEUR ("
        "ID INTEGER PRIMARY KEY,"
        "PHONE TEXT UNIQUE NOT NULL,"
        "PASSWORD TEXT NOT NULL,"
        "USERNAME TEXT NOT NULL"
        ");";
    if (sqlite3_exec(db, restaurateurTable, nullptr, nullptr, &errMsg) != SQLITE_OK) {
        std::cout << errMsg << std::endl;
        sqlite3_free(errMsg);
    };

    const char* system_administratorTable =
        "CREATE TABLE IF NOT EXISTS SYSTEM_ADMINISTRATOR ("
        "ID INTEGER PRIMARY KEY,"
        "PHONE TEXT UNIQUE NOT NULL,"
        "PASSWORD TEXT NOT NULL,"
        "USERNAME TEXT NOT NULL"
        ");";
    if (sqlite3_exec(db, system_administratorTable, nullptr, nullptr, &errMsg) != SQLITE_OK) {
        std::cout << errMsg << std::endl;
        sqlite3_free(errMsg);
    };

    const char* restaurantTable =
        "CREATE TABLE IF NOT EXISTS RESTAURANT ("
        "ID INTEGER PRIMARY KEY,"
        "NAME TEXT NOT NULL,"
        "CITY TEXT NOT NULL,"
        "STREET TEXT NOT NULL,"
        "ALLEY TEXT NOT NULL,"
        "BLOCK INTEGER,"
        "ACTIVE INTEGER,"
        "OPERATION_TIME INTEGER,"
        "PHONE TEXT UNIQUE NOT NULL,"
        "INFORMATION TEXT NOT NULL"
        ");";
    if (sqlite3_exec(db, restaurantTable, nullptr, nullptr, &errMsg) != SQLITE_OK) {
        std::cout << errMsg << std::endl;
        sqlite3_free(errMsg);
    };

    const char* menuTable =
        "CREATE TABLE IF NOT EXISTS MENU ("
        "ID INTEGER PRIMARY KEY,"
        "RESTAURANT_ID INTEGER,"
        "NAME TEXT NOT NULL,"
        "DESCRIPTION TEXT NOT NULL,"
        "PRICE REAL,"
        "AVAILABLE INTEGER"
        ");";
    if (sqlite3_exec(db, menuTable, nullptr, nullptr, &errMsg) != SQLITE_OK) {
        std::cout << errMsg << std::endl;
        sqlite3_free(errMsg);
    };

    const char* foodTable =
        "CREATE TABLE IF NOT EXISTS FOOD ("
        "ID INTEGER PRIMARY KEY,"
        "COOK_TIME INTEGER,"
        "FOREIGN KEY(ID) REFERENCES MENU(ID)"
        ");";
    if (sqlite3_exec(db, foodTable, nullptr, nullptr, &errMsg) != SQLITE_OK) {
        std::cout << errMsg << std::endl;
        sqlite3_free(errMsg);
    };

    const char* drinkTable =
        "CREATE TABLE IF NOT EXISTS DRINK ("
        "ID INTEGER PRIMARY KEY,"
        "VOLUME INTEGER,"
        "FOREIGN KEY(ID) REFERENCES MENU(ID)"
        ");";
    if (sqlite3_exec(db, drinkTable, nullptr, nullptr, &errMsg) != SQLITE_OK) {
        std::cout << errMsg << std::endl;
        sqlite3_free(errMsg);
    };

    const char* cartTable =
        "CREATE TABLE IF NOT EXISTS CART_ITEMS ("
        "CUSTOMER_ID INTEGER,"
        "ITEM_ID INTEGER,"
        "ITEM_TYPE TEXT NOT NULL,"
        "QUANTITY INTEGER"
        ");";
    if (sqlite3_exec(db, cartTable, nullptr, nullptr, &errMsg) != SQLITE_OK) {
        std::cout << errMsg << std::endl;
        sqlite3_free(errMsg);
    };

    const char* ordersTable =
        "CREATE TABLE IF NOT EXISTS ORDERS("
        "ORDER_ID INTEGER PRIMARY KEY,"
        "CUSTOMER_ID INTEGER NOT NULL,"
        "RESTAURANT_ID INTEGER NOT NULL,"
        "TOTAL_PRICE REAL NOT NULL,"
        "STATUS TEXT NOT NULL"
        ");";
    if (sqlite3_exec(db, ordersTable, nullptr, nullptr, &errMsg) != SQLITE_OK) {
        std::cout << errMsg << std::endl;
        sqlite3_free(errMsg);
    };

    const char* cart_itemsTable =
        "CREATE TABLE IF NOT EXISTS CART_ITEM ("
        "ID INTEGER PRIMARY KEY AUTOINCREMENT,"
        "ORDER_ID INTEGER NOT NULL,"
        "ITEM_ID INTEGER NOT NULL,"
        "QUANTITY INTEGER NOT NULL,"
        "UNIT_PRICE REAL NOT NULL"
        ");";
    if (sqlite3_exec(db, cart_itemsTable, nullptr, nullptr, &errMsg) != SQLITE_OK) {
        std::cout << errMsg << std::endl;
        sqlite3_free(errMsg);
    };

}