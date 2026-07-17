
#ifndef FOOD_ORDERING_SYSTEM_DATABASE_H
#define FOOD_ORDERING_SYSTEM_DATABASE_H

#include <sqlite3.h>
#include <string>
#include <iostream>

class Database {
    public:
    Database(const std::string& FileName);
    Database(const Database&) = delete;
    Database& operator=(const Database&) = delete;
    ~Database();
    sqlite3* getConnection() const;
    void createTables();

    private:
    sqlite3 *db;
};

#endif //FOOD_ORDERING_SYSTEM_DATABASE_H