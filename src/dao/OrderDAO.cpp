
#include "dao/OrderDAO.h"
#include "services/Order.h"

OrderDAO::OrderDAO(Database *database) {
    this->database = database;
}

OrderStatus OrderDAO::stringToStatus(const std::string& status) {
    if (status == "Pending") {
        return OrderStatus::pending;
    }
    if (status == "Preparing") {
        return OrderStatus::preparing;
    }
    if (status == "Ready") {
        return OrderStatus::ready;
    }
    if (status == "Delivered") {
        return OrderStatus::delivered;
    }
    if (status == "Cancelled") {
        return OrderStatus::cancelled;
    }
}

std::string OrderDAO::statusToString(OrderStatus status) {
    switch (status) {
        case OrderStatus::pending :
            return "Pending";

        case OrderStatus::preparing :
            return "Prepared";

        case OrderStatus::ready :
            return "Ready";

        case OrderStatus::delivered :
            return "Delivered";

        case OrderStatus::cancelled :
            return "Cancelled";
    }
    return "Pending";
}

bool OrderDAO::insertOrder(const Order& order) {
    std::string sql = "INSERT INTO ORDERS (ORDER_ID, CUSTOMER_ID, RESTAURANT_ID, TOTAL_PRICE, STATUS) VALUES (?,?,?,?,?);";
    sqlite3_stmt *stmt = nullptr;
    if (sqlite3_prepare_v2(database->getConnection(), sql.c_str(), -1, &stmt, nullptr) != SQLITE_OK) {
        return false;
    }
    sqlite3_bind_int(stmt,1,order.get_orderId());
    sqlite3_bind_int(stmt,2,order.get_customerId());
    sqlite3_bind_int(stmt,3,order.get_restaurantId());
    sqlite3_bind_double(stmt,4,order.get_totalPrice());
    sqlite3_bind_text(stmt,5,statusToString(order.get_status()).c_str(),-1,SQLITE_TRANSIENT);

    bool success = sqlite3_step(stmt) == SQLITE_DONE;
    sqlite3_finalize(stmt);
    return success;
}

bool OrderDAO::insertOrderItems(int orderId, const std::vector<CartItem>& items) {
    std::string sql = "INSERT INTO CART_ITEM (ORDER_ID, ITEM_ID, QUANTITY, UNIT_PRICE) VALUES (?,?,?,?);";
    sqlite3_stmt *stmt = nullptr;
    if (sqlite3_prepare_v2(database->getConnection(), sql.c_str(), -1, &stmt, nullptr) != SQLITE_OK) {
        return false;
    }
    for (const CartItem &item : items) {
        sqlite3_bind_int(stmt,1,orderId);
        sqlite3_bind_int(stmt,2,item.get_itemId());
        sqlite3_bind_int(stmt,3,item.get_quantity());
        sqlite3_bind_double(stmt,4,item.get_unitPrice());

        if (sqlite3_step(stmt) != SQLITE_DONE) {
            sqlite3_finalize(stmt);
            return false;
        }
        sqlite3_reset(stmt);
        sqlite3_clear_bindings(stmt);
    }
    sqlite3_finalize(stmt);
    return true;
}

bool OrderDAO::deleteOrderItems(int orderId) {
    std::string sql = "DELETE FROM CART_ITEM WHERE ORDER_ID = ?;";
    sqlite3_stmt *stmt = nullptr;
    if (sqlite3_prepare_v2(database->getConnection(), sql.c_str(), -1, &stmt, nullptr) != SQLITE_OK) {
        return false;
    }
    sqlite3_bind_int(stmt,1,orderId);
    if (sqlite3_step(stmt) != SQLITE_DONE) {
        sqlite3_finalize(stmt);
        return false;
    }
    sqlite3_finalize(stmt);
    return true;
}

bool OrderDAO::deleteOrder(int orderId) {
    deleteOrderItems(orderId);
    std::string sql = "DELETE FROM ORDERS WHERE ORDER_ID = ?;";
    sqlite3_stmt *stmt = nullptr;
    if (sqlite3_prepare_v2(database->getConnection(), sql.c_str(), -1, &stmt, nullptr) != SQLITE_OK) {
        return false;
    }
    sqlite3_bind_int(stmt,1,orderId);
    if (sqlite3_step(stmt) != SQLITE_DONE) {
        sqlite3_finalize(stmt);
        return false;
    }
    sqlite3_finalize(stmt);
    return true;
}

bool OrderDAO::updateOrderStatus(int orderId, OrderStatus status) {
    std::string sql = "UPDATE ORDERS SET STATUS = ? WHERE ORDER_ID=? ;";
    sqlite3_stmt *stmt = nullptr;
    if (sqlite3_prepare_v2(database->getConnection(), sql.c_str(), -1, &stmt, nullptr) != SQLITE_OK) {
        return false;
    }
    sqlite3_bind_text(stmt,1,statusToString(status).c_str(),-1,SQLITE_TRANSIENT);
    sqlite3_bind_int(stmt,2,orderId);
    if (sqlite3_step(stmt) != SQLITE_DONE) {
        sqlite3_finalize(stmt);
        return false;
    }
    sqlite3_finalize(stmt);
    return true;
}

std::vector<CartItem> OrderDAO::getOrderItems(int orderId) {
    std::vector<CartItem> items;
    std::string sql ="SELECT ITEM_ID, QUANTITY, UNIT_PRICE FROM CART_ITEM WHERE ORDER_ID=? ;";
    sqlite3_stmt *stmt = nullptr;
    if (sqlite3_prepare_v2(database->getConnection(), sql.c_str(), -1, &stmt, nullptr) != SQLITE_OK) {
        return items;
    }
    sqlite3_bind_int(stmt,1,orderId);
    while (sqlite3_step(stmt)==SQLITE_ROW) {
        CartItem item;
        item.set_itemId(sqlite3_column_int(stmt,0));
        item.set_quantity(sqlite3_column_int(stmt,1));
        item.set_unitPrice(sqlite3_column_double(stmt,2));
        items.push_back(item);
    }
    sqlite3_finalize(stmt);
    return items;
}

Order OrderDAO::getOrderById(int id) {
    Order order;
    std::string sql = "SELECT * FROM ORDERS WHERE ITEM_ID=? ;";
    sqlite3_stmt *stmt = nullptr;
    if (sqlite3_prepare_v2(database->getConnection(), sql.c_str(), -1, &stmt, nullptr) != SQLITE_OK) {
        return order;
    }
    sqlite3_bind_int(stmt,1,id);
    if (sqlite3_step(stmt) == SQLITE_ROW) {
        order.set_orderId(sqlite3_column_int(stmt,0));
        order.set_customerId(sqlite3_column_int(stmt,1));
        order.set_restaurantId(sqlite3_column_int(stmt,2));
        order.set_totalPrice(sqlite3_column_double(stmt,3));
        std::string status = reinterpret_cast<const char*>(sqlite3_column_text(stmt,4));
        order.set_status(stringToStatus(status));
    }
    sqlite3_finalize(stmt);
    return order;
}

std::vector<Order> OrderDAO::getCustomerOrders(int customerId) {
    std::string sql = "SELECT * FROM ORDERS WHERE CUSTOMER_ID=? ;";
    std::vector<Order> orders;
    sqlite3_stmt *stmt = nullptr;
    if (sqlite3_prepare_v2(database->getConnection(), sql.c_str(), -1, &stmt, nullptr) != SQLITE_OK) {
        return orders;
    }
    sqlite3_bind_int(stmt,1,customerId);
    while (sqlite3_step(stmt) == SQLITE_ROW) {
        Order order;
        order.set_orderId(sqlite3_column_int(stmt,0));
        order.set_customerId(sqlite3_column_int(stmt,1));
        order.set_restaurantId(sqlite3_column_int(stmt,2));
        order.set_totalPrice(sqlite3_column_double(stmt,3));
        std::string status = reinterpret_cast<const char*>(sqlite3_column_text(stmt,4));
        order.set_status(stringToStatus(status));
        orders.push_back(order);
    }
    sqlite3_finalize(stmt);
    return orders;
}

std::vector<Order> OrderDAO::getRestaurantOrders(int restaurantId) {
    std::string sql = "SELECT * FROM ORDERS WHERE RESTAURANT_ID=? ;";
    std::vector<Order> orders;
    sqlite3_stmt *stmt = nullptr;
    if (sqlite3_prepare_v2(database->getConnection(), sql.c_str(), -1, &stmt, nullptr) != SQLITE_OK) {
        return orders;
    }
    sqlite3_bind_int(stmt,1,restaurantId);
    while (sqlite3_step(stmt) == SQLITE_ROW) {
        Order order;
        order.set_orderId(sqlite3_column_int(stmt,0));
        order.set_customerId(sqlite3_column_int(stmt,1));
        order.set_restaurantId(sqlite3_column_int(stmt,2));
        order.set_totalPrice(sqlite3_column_double(stmt,3));
        std::string status = reinterpret_cast<const char*>(sqlite3_column_text(stmt,4));
        order.set_status(stringToStatus(status));
        orders.push_back(order);
    }
    sqlite3_finalize(stmt);
    return orders;
}
