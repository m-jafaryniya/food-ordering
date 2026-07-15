
#include "dao/MenuDAO.h"
#include "dao/Database.h"
#include "models/Menu.h"
#include "models/Food.h"
#include "models/Drink.h"

MenuDAO::MenuDAO(Database* database) {
    this->database = database;
}

bool MenuDAO::addFood(int restaurantId, const Food& food) {
    std::string sql = "INSERT INTO FOODS ("
                      "ID, RESTAURANT_ID, NAME, DESCRIPTION, PRICE, AVAILABLE, COOK_TIME)"
                      " VALUES(?,?,?,?,?,?,?);";
    sqlite3_stmt *stmt = nullptr;
    if (sqlite3_prepare_v2(database->getConnection(), sql.c_str(), -1, &stmt, nullptr) != SQLITE_OK) {
        return false;
    }
    sqlite3_bind_int(stmt,1,food.get_ItemId());
    sqlite3_bind_int(stmt,2,restaurantId);
    sqlite3_bind_text(stmt,3,food.get_ItemName().c_str(),-1,SQLITE_TRANSIENT);
    sqlite3_bind_text(stmt,4,food.get_ItemDescription().c_str(),-1,SQLITE_TRANSIENT);
    sqlite3_bind_double(stmt,5,food.get_BasePrice());
    sqlite3_bind_int(stmt,6,food.get_available());
    sqlite3_bind_int(stmt,7,food.get_cookTime());

    bool success = sqlite3_step(stmt) == SQLITE_DONE;
    sqlite3_finalize(stmt);
    return success;
}

bool MenuDAO::updateFood(const Food& food) {
    std::string sql_update = "UPDATE FOODS SET "
                             "NAME=?"
                             "DESCRIPTION=?"
                             "PRICE=?"
                             "AVAILABLE=?"
                             "COOK_TIME=?"
                             "WHERE ID=?;";
    sqlite3_stmt *stmt = nullptr;
    if (sqlite3_prepare_v2(database->getConnection(), sql_update.c_str(), -1, &stmt, nullptr) != SQLITE_OK) {
        return false;
    }
    sqlite3_bind_text(stmt,1,food.get_ItemName().c_str(),-1,SQLITE_TRANSIENT);
    sqlite3_bind_text(stmt,2,food.get_ItemDescription().c_str(),-1,SQLITE_TRANSIENT);
    sqlite3_bind_double(stmt,3,food.get_BasePrice());
    sqlite3_bind_int(stmt,4,food.get_available());
    sqlite3_bind_int(stmt,5,food.get_cookTime());
    sqlite3_bind_int(stmt,6,food.get_ItemId());

    bool success = (sqlite3_step(stmt) == SQLITE_DONE);
    sqlite3_finalize(stmt);
    return success;
}

bool MenuDAO::deleteFood(int id) {
    std::string sql_delete = "DELETE FROM FOODS WHERE ID=?;";
    sqlite3_stmt *stmt = nullptr;
    if (sqlite3_prepare_v2(database->getConnection(), sql_delete.c_str(), -1, &stmt, nullptr) != SQLITE_OK) {
        return false;
    }
    sqlite3_bind_int(stmt,1,id);

    bool success = (sqlite3_step(stmt) == SQLITE_DONE);
    sqlite3_finalize(stmt);
    return success;
}

std::optional<Food> MenuDAO::getFoodById(int id) {
    std::string sql = "SELECT * FROM FOODS WHERE ID=?;";
    sqlite3_stmt *stmt = nullptr;
    if (sqlite3_prepare_v2(database->getConnection(), sql.c_str(), -1, &stmt, nullptr) != SQLITE_OK) {
        return std::nullopt;
    }
    sqlite3_bind_int(stmt,1,id);
    if (sqlite3_step(stmt) == SQLITE_ROW) {
        Food food;
        food.set_ItemId(sqlite3_column_int(stmt,0));
        food.set_ItemName(reinterpret_cast<const char*>(sqlite3_column_text(stmt,2)));
        food.set_ItemDescription(reinterpret_cast<const char*>(sqlite3_column_text(stmt,3)));
        food.set_BasePrice(sqlite3_column_double(stmt,4));
        food.set_available(sqlite3_column_int(stmt,5));
        food.set_cookTime(sqlite3_column_int(stmt,6));

        sqlite3_finalize(stmt);
        return food;
    }
    sqlite3_finalize(stmt);
    return std::nullopt;
}

bool MenuDAO::addDrink(int restaurantId, const Drink &drink) {
    std::string sql = "INSERT INTO DRINKS ("
                      "ID, RESTAURANT_ID, NAME, DESCRIPTION, PRICE, AVAILABLE, VOLUME)"
                      " VALUES(?,?,?,?,?,?,?);";
    sqlite3_stmt *stmt = nullptr;
    if (sqlite3_prepare_v2(database->getConnection(), sql.c_str(), -1, &stmt, nullptr) != SQLITE_OK) {
        return false;
    }
    sqlite3_bind_int(stmt,1,drink.get_ItemId());
    sqlite3_bind_int(stmt,2,restaurantId);
    sqlite3_bind_text(stmt,3,drink.get_ItemName().c_str(),-1,SQLITE_TRANSIENT);
    sqlite3_bind_text(stmt,4,drink.get_ItemDescription().c_str(),-1,SQLITE_TRANSIENT);
    sqlite3_bind_double(stmt,5,drink.get_BasePrice());
    sqlite3_bind_int(stmt,6,drink.get_available());
    sqlite3_bind_int(stmt,7,drink.get_volume());

    bool success = sqlite3_step(stmt) == SQLITE_DONE;
    sqlite3_finalize(stmt);
    return success;
}

bool MenuDAO::updateDrink(const Drink &drink) {
    std::string sql_update = "UPDATE DRINKS SET "
                             "NAME=?"
                             "DESCRIPTION=?"
                             "PRICE=?"
                             "AVAILABLE=?"
                             "VOLUME=?"
                             "WHERE ID=?;";
    sqlite3_stmt *stmt = nullptr;
    if (sqlite3_prepare_v2(database->getConnection(), sql_update.c_str(), -1, &stmt, nullptr) != SQLITE_OK) {
        return false;
    }
    sqlite3_bind_text(stmt,1,drink.get_ItemName().c_str(),-1,SQLITE_TRANSIENT);
    sqlite3_bind_text(stmt,2,drink.get_ItemDescription().c_str(),-1,SQLITE_TRANSIENT);
    sqlite3_bind_double(stmt,3,drink.get_BasePrice());
    sqlite3_bind_int(stmt,4,drink.get_available());
    sqlite3_bind_int(stmt,5,drink.get_volume());
    sqlite3_bind_int(stmt,6,drink.get_ItemId());

    bool success = (sqlite3_step(stmt) == SQLITE_DONE);
    sqlite3_finalize(stmt);
    return success;
}

bool MenuDAO::deleteDrink(int id) {
    std::string sql_delete = "DELETE FROM DRINKS WHERE ID=?;";
    sqlite3_stmt *stmt = nullptr;
    if (sqlite3_prepare_v2(database->getConnection(), sql_delete.c_str(), -1, &stmt, nullptr) != SQLITE_OK) {
        return false;
    }
    sqlite3_bind_int(stmt,1,id);

    bool success = (sqlite3_step(stmt) == SQLITE_DONE);
    sqlite3_finalize(stmt);
    return success;
}

std::optional<Drink> MenuDAO::getDrinkById(int id) {
    std::string sql = "SELECT * FROM DRINKS WHERE ID=?;";
    sqlite3_stmt *stmt = nullptr;
    if (sqlite3_prepare_v2(database->getConnection(), sql.c_str(), -1, &stmt, nullptr) != SQLITE_OK) {
        return std::nullopt;
    }
    sqlite3_bind_int(stmt,1,id);
    if (sqlite3_step(stmt) == SQLITE_ROW) {
        Drink drink;
        drink.set_ItemId(sqlite3_column_int(stmt,0));
        drink.set_ItemName(reinterpret_cast<const char*>(sqlite3_column_text(stmt,2)));
        drink.set_ItemDescription(reinterpret_cast<const char*>(sqlite3_column_text(stmt,3)));
        drink.set_BasePrice(sqlite3_column_double(stmt,4));
        drink.set_available(sqlite3_column_int(stmt,5));
        drink.set_volume(sqlite3_column_int(stmt,6));

        sqlite3_finalize(stmt);
        return drink;
    }
    sqlite3_finalize(stmt);
    return std::nullopt;
}
