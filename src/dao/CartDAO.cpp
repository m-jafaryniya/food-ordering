
#include "dao/CartDAO.h"

CartDAO::CartDAO(Database *database) {
    this->database=database;
}

bool CartDAO::addItem(int customerId, int itemId, const std::string &itemType, int quantity) {
    std::string sql = "INSERT INTO CART_ITEMS (CUSTOMER_ID, ITEM_ID, ITEM_TYPE, QUANTITY) VALUES (?,?,?,?);";
    sqlite3_stmt *stmt = nullptr;
    if (sqlite3_prepare_v2(database->getConnection(),sql.c_str(),-1,&stmt,nullptr) != SQLITE_OK) {
        return false;
    }
    sqlite3_bind_int(stmt,1,customerId);
    sqlite3_bind_int(stmt,2,itemId);
    sqlite3_bind_text(stmt,3,itemType.c_str(),-1,SQLITE_TRANSIENT);
    sqlite3_bind_int(stmt,4,quantity);

    bool success = (sqlite3_step(stmt) == SQLITE_DONE);
    sqlite3_finalize(stmt);
    return success;
}

bool CartDAO::deleteItem(int customerId, int itemId, const std::string &itemType) {
    std::string sql_delete = "DELETE FROM CART_ITEMS WHERE CUSTOMER_ID=? AND ITEM_ID=? AND ITEM_TYPE=?;";
    sqlite3_stmt *stmt = nullptr;
    if (sqlite3_prepare_v2(database->getConnection(),sql_delete.c_str(),-1,&stmt,nullptr) != SQLITE_OK) {
        return false;
    }
    sqlite3_bind_int(stmt,1,customerId);
    sqlite3_bind_int(stmt,2,itemId);
    sqlite3_bind_text(stmt,3,itemType.c_str(),-1,SQLITE_TRANSIENT);
    bool success = (sqlite3_step(stmt) == SQLITE_DONE);
    sqlite3_finalize(stmt);
    return success;
}

bool CartDAO::updateQuantity(int customerId, int itemId, const std::string &itemType, int quantity) {
    std::string sql_update = "UPDATE CART_ITEMS SET QUANTITY=? WHERE CUSTOMER_ID=? AND ITEM_ID=? AND ITEM_TYPE=?;";
    sqlite3_stmt *stmt = nullptr;
    if (sqlite3_prepare_v2(database->getConnection(),sql_update.c_str(),-1,&stmt,nullptr) != SQLITE_OK) {
        return false;
    }
    sqlite3_bind_int(stmt,1,quantity);
    sqlite3_bind_int(stmt,2,customerId);
    sqlite3_bind_int(stmt,3,itemId);
    sqlite3_bind_text(stmt,4,itemType.c_str(),-1,SQLITE_TRANSIENT);

    bool success = (sqlite3_step(stmt) == SQLITE_DONE);
    sqlite3_finalize(stmt);
    return success;
}

Cart CartDAO::get_cart(int customerId) {
    Cart cart(customerId);
    std::string sql = "SELECT * FROM CART_ITEMS WHERE CUSTOMER_ID=?;";
    sqlite3_stmt *stmt = nullptr;
    if (sqlite3_prepare_v2(database->getConnection(),sql.c_str(),-1,&stmt,nullptr) != SQLITE_OK) {
        return cart;
    }
    sqlite3_bind_int(stmt,1,customerId);

    while (sqlite3_step(stmt) == SQLITE_ROW) {
        int itemId=sqlite3_column_int(stmt,1);
        std::string itemType=reinterpret_cast<const char*>(sqlite3_column_text(stmt,2));
        double unitPrice=sqlite3_column_double(stmt,3);
        int quantity=sqlite3_column_int(stmt,4);
        cart.addItem(itemId,unitPrice,quantity);
    }
    sqlite3_finalize(stmt);
    return cart;
}

bool CartDAO::clear_cart(int customerId) {
    std::string sql_clear = "DELETE FROM CART_ITEMS WHERE CUSTOMER_ID=?;";
    sqlite3_stmt *stmt = nullptr;
    if (sqlite3_prepare_v2(database->getConnection(),sql_clear.c_str(),-1,&stmt,nullptr) != SQLITE_OK) {
        return false;
    }
    sqlite3_bind_int(stmt,1,customerId);
    bool success = (sqlite3_step(stmt) == SQLITE_DONE);
    sqlite3_finalize(stmt);
    return success;
}
