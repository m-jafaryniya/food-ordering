
#ifndef FOOD_ORDERING_SYSTEM_DATABASE_H
#define FOOD_ORDERING_SYSTEM_DATABASE_H

#include <sqlite3.h>
#include <string>
#include <iostream>

class Database {
    public:
    Database(const std::string& FileName);
    ~Database();
    sqlite3* getConnection() const;

    private:
    sqlite3 *db;
};

#endif //FOOD_ORDERING_SYSTEM_DATABASE_H