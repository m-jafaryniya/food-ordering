
#include "dao/Database.h"
#include <iostream>

Database::Database(const std::string &FileName) {
    if (sqlite3_open(FileName.c_str(), &db) != SQLITE_OK) {
        std::cout << "Can't open database" << std::endl;
    }
}

Database::~Database() {
    sqlite3_close(db);
}

sqlite3* Database::getConnection() const {
    return db;
}
