
#include "dao/MenuDAO.h"
#include "dao/Database.h"
#include "models/Menu.h"
#include "models/Food.h"
#include "models/Drink.h"
#include "models/Restaurant.h"

MenuDAO::MenuDAO(Database* database) {
    this->database = database;
}

bool MenuDAO::addFood(int restaurantId, const Food& food) {
    std::string sqlMenu = "INSERT INTO MENU ("
                      "ID, RESTAURANT_ID, NAME, DESCRIPTION, PRICE, AVAILABLE)"
                      " VALUES(?,?,?,?,?,?);";
    sqlite3_stmt *stmtMenu = nullptr;
    if (sqlite3_prepare_v2(database->getConnection(), sqlMenu.c_str(), -1, &stmtMenu, nullptr) != SQLITE_OK) {
        return false;
    }
    sqlite3_bind_int(stmtMenu,1,food.get_ItemId());
    sqlite3_bind_int(stmtMenu,2,restaurantId);
    sqlite3_bind_text(stmtMenu,3,food.get_ItemName().c_str(),-1,SQLITE_TRANSIENT);
    sqlite3_bind_text(stmtMenu,4,food.get_ItemDescription().c_str(),-1,SQLITE_TRANSIENT);
    sqlite3_bind_double(stmtMenu,5,food.get_BasePrice());
    sqlite3_bind_int(stmtMenu,6,food.get_available());

    if (sqlite3_step(stmtMenu) != SQLITE_DONE) {
        sqlite3_finalize(stmtMenu);
        return false;
    }

    std::string sqlFood = "INSERT INTO FOOD (ID, COOK_TIME) VALUES (?,?);";
    sqlite3_stmt *stmtFood = nullptr;
    if (sqlite3_prepare_v2(database->getConnection(), sqlFood.c_str(), -1, &stmtFood, nullptr) != SQLITE_OK) {
        return false;
    }
    sqlite3_bind_int(stmtFood,1,food.get_ItemId());
    sqlite3_bind_int(stmtFood,2,food.get_cookTime());

    bool success = sqlite3_step(stmtFood) == SQLITE_DONE;
    sqlite3_finalize(stmtFood);
    return success;
}

bool MenuDAO::updateFood(const Food& food) {
    std::string sqlMenu = "UPDATE MENU SET NAME = ?, DESCRIPTION = ?, PRICE = ?, AVAILABLE = ? WHERE ID = ?;";
    sqlite3_stmt *stmtMenu = nullptr;
    if (sqlite3_prepare_v2(database->getConnection(), sqlMenu.c_str(), -1, &stmtMenu, nullptr) != SQLITE_OK) {
        return false;
    }
    sqlite3_bind_text(stmtMenu, 1, food.get_ItemName().c_str(), -1, SQLITE_TRANSIENT);
    sqlite3_bind_text(stmtMenu, 2, food.get_ItemDescription().c_str(), -1, SQLITE_TRANSIENT);
    sqlite3_bind_double(stmtMenu, 3, food.get_BasePrice());
    sqlite3_bind_int(stmtMenu, 4, food.get_available());
    sqlite3_bind_int(stmtMenu, 5, food.get_ItemId());

    if (sqlite3_step(stmtMenu) != SQLITE_DONE) {
        sqlite3_finalize(stmtMenu);
        return false;
    }
    sqlite3_finalize(stmtMenu);

    std::string sqlFood = "UPDATE FOOD SET COOK_TIME = ? WHERE ID = ?;";
    sqlite3_stmt *stmtFood = nullptr;
    if (sqlite3_prepare_v2(database->getConnection(), sqlFood.c_str(), -1, &stmtFood, nullptr) != SQLITE_OK) {
        return false;
    }
    sqlite3_bind_int(stmtFood, 1, food.get_cookTime());
    sqlite3_bind_int(stmtFood, 2, food.get_ItemId());

    bool success = (sqlite3_step(stmtFood) == SQLITE_DONE);
    sqlite3_finalize(stmtFood);
    return success;
}

bool MenuDAO::deleteFood(int id) {
    std::string sqlFood = "DELETE FROM FOOD WHERE ID = ?;";
    sqlite3_stmt *stmtFood = nullptr;
    if (sqlite3_prepare_v2(database->getConnection(), sqlFood.c_str(), -1, &stmtFood, nullptr) != SQLITE_OK) {
        return false;
    }
    sqlite3_bind_int(stmtFood, 1, id);
    sqlite3_step(stmtFood);
    sqlite3_finalize(stmtFood);

    std::string sqlMenu = "DELETE FROM MENU WHERE ID = ?;";
    sqlite3_stmt *stmtMenu = nullptr;
    if (sqlite3_prepare_v2(database->getConnection(), sqlMenu.c_str(), -1, &stmtMenu, nullptr) != SQLITE_OK) {
        return false;
    }
    sqlite3_bind_int(stmtMenu, 1, id);

    bool success = (sqlite3_step(stmtMenu) == SQLITE_DONE);
    sqlite3_finalize(stmtMenu);
    return success;
}

std::optional<Food> MenuDAO::getFoodById(int id) {
    std::string sql = "SELECT m.ID, m.NAME, m.DESCRIPTION, m.PRICE, m.AVAILABLE, f.COOK_TIME "
                      "FROM MENU m "
                      "INNER JOIN FOOD f ON m.ID = f.ID "
                      "WHERE m.ID = ?;";
    sqlite3_stmt *stmt = nullptr;
    if (sqlite3_prepare_v2(database->getConnection(), sql.c_str(), -1, &stmt, nullptr) != SQLITE_OK) {
        return std::nullopt;
    }
    sqlite3_bind_int(stmt, 1, id);
    if (sqlite3_step(stmt) == SQLITE_ROW) {
        Food food;
        food.set_ItemId(sqlite3_column_int(stmt, 0));
        food.set_ItemName(reinterpret_cast<const char*>(sqlite3_column_text(stmt, 1)));
        food.set_ItemDescription(reinterpret_cast<const char*>(sqlite3_column_text(stmt, 2)));
        food.set_BasePrice(sqlite3_column_double(stmt, 3));
        food.set_available(sqlite3_column_int(stmt, 4));
        food.set_cookTime(sqlite3_column_int(stmt, 5));

        sqlite3_finalize(stmt);
        return food;
    }
    sqlite3_finalize(stmt);
    return std::nullopt;
}

bool MenuDAO::addDrink(int restaurantId, const Drink &drink) {
    std::string sqlMenu = "INSERT INTO MENU ("
                      "ID, RESTAURANT_ID, NAME, DESCRIPTION, PRICE, AVAILABLE)"
                      " VALUES(?,?,?,?,?,?);";
    sqlite3_stmt *stmtMenu = nullptr;
    if (sqlite3_prepare_v2(database->getConnection(), sqlMenu.c_str(), -1, &stmtMenu, nullptr) != SQLITE_OK) {
        return false;
    }
    sqlite3_bind_int(stmtMenu,1,drink.get_ItemId());
    sqlite3_bind_int(stmtMenu,2,restaurantId);
    sqlite3_bind_text(stmtMenu,3,drink.get_ItemName().c_str(),-1,SQLITE_TRANSIENT);
    sqlite3_bind_text(stmtMenu,4,drink.get_ItemDescription().c_str(),-1,SQLITE_TRANSIENT);
    sqlite3_bind_double(stmtMenu,5,drink.get_BasePrice());
    sqlite3_bind_int(stmtMenu,6,drink.get_available());

    if (sqlite3_step(stmtMenu) != SQLITE_DONE) {
        sqlite3_finalize(stmtMenu);
        return false;
    }

    std::string sqlDrink = "INSERT INTO DRINK (ID, VOLUME) VALUES (?,?);";
    sqlite3_stmt *stmtDrink = nullptr;
    if (sqlite3_prepare_v2(database->getConnection(), sqlDrink.c_str(), -1, &stmtDrink, nullptr) != SQLITE_OK) {
        return false;
    }
    sqlite3_bind_int(stmtDrink,1,drink.get_ItemId());
    sqlite3_bind_int(stmtDrink,2,drink.get_volume());

    bool success = sqlite3_step(stmtDrink) == SQLITE_DONE;
    sqlite3_finalize(stmtDrink);
    return success;
}

bool MenuDAO::updateDrink(const Drink &drink) {
    std::string sqlMenu = "UPDATE MENU SET NAME = ?, DESCRIPTION = ?, PRICE = ?, AVAILABLE = ? WHERE ID = ?;";
    sqlite3_stmt *stmtMenu = nullptr;
    if (sqlite3_prepare_v2(database->getConnection(), sqlMenu.c_str(), -1, &stmtMenu, nullptr) != SQLITE_OK) {
        return false;
    }
    sqlite3_bind_text(stmtMenu, 1, drink.get_ItemName().c_str(), -1, SQLITE_TRANSIENT);
    sqlite3_bind_text(stmtMenu, 2, drink.get_ItemDescription().c_str(), -1, SQLITE_TRANSIENT);
    sqlite3_bind_double(stmtMenu, 3, drink.get_BasePrice());
    sqlite3_bind_int(stmtMenu, 4, drink.get_available());
    sqlite3_bind_int(stmtMenu, 5, drink.get_ItemId());

    if (sqlite3_step(stmtMenu) != SQLITE_DONE) {
        sqlite3_finalize(stmtMenu);
        return false;
    }
    sqlite3_finalize(stmtMenu);

    std::string sqlDrink = "UPDATE DRINK SET VOLUME = ? WHERE ID = ?;";
    sqlite3_stmt *stmtDrink = nullptr;
    if (sqlite3_prepare_v2(database->getConnection(), sqlDrink.c_str(), -1, &stmtDrink, nullptr) != SQLITE_OK) {
        return false;
    }
    sqlite3_bind_int(stmtDrink, 1, drink.get_volume());
    sqlite3_bind_int(stmtDrink, 2, drink.get_ItemId());

    bool success = (sqlite3_step(stmtDrink) == SQLITE_DONE);
    sqlite3_finalize(stmtDrink);
    return success;
}

bool MenuDAO::deleteDrink(int id) {
    std::string sqlDrink = "DELETE FROM DRINK WHERE ID = ?;";
    sqlite3_stmt *stmtDrink = nullptr;
    if (sqlite3_prepare_v2(database->getConnection(), sqlDrink.c_str(), -1, &stmtDrink, nullptr) != SQLITE_OK) {
        return false;
    }
    sqlite3_bind_int(stmtDrink, 1, id);
    sqlite3_step(stmtDrink);
    sqlite3_finalize(stmtDrink);

    std::string sqlMenu = "DELETE FROM MENU WHERE ID = ?;";
    sqlite3_stmt *stmtMenu = nullptr;
    if (sqlite3_prepare_v2(database->getConnection(), sqlMenu.c_str(), -1, &stmtMenu, nullptr) != SQLITE_OK) {
        return false;
    }
    sqlite3_bind_int(stmtMenu, 1, id);

    bool success = (sqlite3_step(stmtMenu) == SQLITE_DONE);
    sqlite3_finalize(stmtMenu);
    return success;
}

std::optional<Drink> MenuDAO::getDrinkById(int id) {
    std::string sql = "SELECT m.ID, m.NAME, m.DESCRIPTION, m.PRICE, m.AVAILABLE, d.VOLUME "
                      "FROM MENU m "
                      "INNER JOIN DRINK d ON m.ID = d.ID "
                      "WHERE m.ID = ?;";
    sqlite3_stmt *stmt = nullptr;
    if (sqlite3_prepare_v2(database->getConnection(), sql.c_str(), -1, &stmt, nullptr) != SQLITE_OK) {
        return std::nullopt;
    }
    sqlite3_bind_int(stmt, 1, id);
    if (sqlite3_step(stmt) == SQLITE_ROW) {
        Drink drink;
        drink.set_ItemId(sqlite3_column_int(stmt, 0));
        drink.set_ItemName(reinterpret_cast<const char*>(sqlite3_column_text(stmt, 1)));
        drink.set_ItemDescription(reinterpret_cast<const char*>(sqlite3_column_text(stmt, 2)));
        drink.set_BasePrice(sqlite3_column_double(stmt, 3));
        drink.set_available(sqlite3_column_int(stmt, 4));
        drink.set_volume(sqlite3_column_int(stmt, 5));

        sqlite3_finalize(stmt);
        return drink;
    }
    sqlite3_finalize(stmt);
    return std::nullopt;
}

std::vector<Menu *> MenuDAO::getRestaurantMenu(int restaurantId) {
    std::vector<Menu *> menuItems;

    std::string sqlFood = "SELECT m.ID, m.NAME, m.DESCRIPTION, m.PRICE, m.AVAILABLE, f.COOK_TIME "
                          "FROM MENU m "
                          "INNER JOIN FOOD f ON m.ID = f.ID "
                          "WHERE m.RESTAURANT_ID = ?;";
    sqlite3_stmt *stmtFood = nullptr;
    if (sqlite3_prepare_v2(database->getConnection(), sqlFood.c_str(), -1, &stmtFood, nullptr) == SQLITE_OK) {
        sqlite3_bind_int(stmtFood, 1, restaurantId);

        while (sqlite3_step(stmtFood) == SQLITE_ROW) {
            Food* food = new Food();
            food->set_ItemId(sqlite3_column_int(stmtFood,0));
            food->set_ItemName(reinterpret_cast<const char*>(sqlite3_column_text(stmtFood,1)));
            food->set_ItemDescription(reinterpret_cast<const char*>(sqlite3_column_text(stmtFood,2)));
            food->set_BasePrice(sqlite3_column_double(stmtFood,3));
            food->set_available(sqlite3_column_int(stmtFood,4));
            food->set_cookTime(sqlite3_column_int(stmtFood,5));
            menuItems.push_back(food);
        }
        sqlite3_finalize(stmtFood);
    }

    std::string sqlDrink = "SELECT m.ID, m.NAME, m.DESCRIPTION, m.PRICE, m.AVAILABLE, d.VOLUME "
                          "FROM MENU m "
                          "INNER JOIN DRINK ON m.ID = d.ID "
                          "WHERE m.RESTAURANT_ID = ?;";
    sqlite3_stmt *stmtDrink = nullptr;
    if (sqlite3_prepare_v2(database->getConnection(), sqlDrink.c_str(), -1, &stmtDrink, nullptr) == SQLITE_OK) {
        sqlite3_bind_int(stmtDrink, 1, restaurantId);

        while (sqlite3_step(stmtDrink) == SQLITE_ROW) {
            Drink* drink = new Drink();
            drink->set_ItemId(sqlite3_column_int(stmtDrink,0));
            drink->set_ItemName(reinterpret_cast<const char*>(sqlite3_column_text(stmtDrink,1)));
            drink->set_ItemDescription(reinterpret_cast<const char*>(sqlite3_column_text(stmtDrink,2)));
            drink->set_BasePrice(sqlite3_column_double(stmtDrink,3));
            drink->set_available(sqlite3_column_int(stmtDrink,4));
            drink->set_volume(sqlite3_column_int(stmtDrink,5));
            menuItems.push_back(drink);
        }
        sqlite3_finalize(stmtDrink);
    }
    return menuItems;
}
