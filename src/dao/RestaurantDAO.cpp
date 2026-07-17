
#include "dao/RestaurantDAO.h"
#include "models/Restaurant.h"

RestaurantDAO::RestaurantDAO(Database* database) {
    this->database = database;
}

void RestaurantDAO::insertRestaurant(const Restaurant& restaurant) {
    sqlite3_stmt* stmt = nullptr;
    std::string sql = "INSERT INTO RESTAURANT ( ID, NAME, CITY, STREET, ALLEY, BLOCK, ACTIVE, OPERATION_TIME, PHONE, INFORMATION, OWNER_ID )"
                      " VALUES (?,?,?,?,?,?,?,?,?,?,?)";
    int rc = sqlite3_prepare_v2(database->getConnection(), sql.c_str(), -1, &stmt, NULL);
    if (rc != SQLITE_OK) {
        std::cerr << "Error Insert : " << sqlite3_errcode(database->getConnection()) << std::endl;
    }
    sqlite3_bind_int(stmt,1,restaurant.getID());
    sqlite3_bind_text(stmt,2,restaurant.getName().c_str(),-1,SQLITE_TRANSIENT);
    sqlite3_bind_text(stmt,3,restaurant.getAddress().get_cityName().c_str(),-1,SQLITE_TRANSIENT);
    sqlite3_bind_text(stmt,4,restaurant.getAddress().get_streetName().c_str(),-1,SQLITE_TRANSIENT);
    sqlite3_bind_text(stmt,5,restaurant.getAddress().get_alleyName().c_str(),-1,SQLITE_TRANSIENT);
    sqlite3_bind_int(stmt,6,restaurant.getAddress().get_block());
    sqlite3_bind_int(stmt,7,restaurant.getActive());
    sqlite3_bind_int(stmt,8,restaurant.getOperationTime());
    sqlite3_bind_text(stmt,9,restaurant.getPhone().c_str(),-1,SQLITE_TRANSIENT);
    sqlite3_bind_text(stmt,10,restaurant.getInformation().c_str(),-1,SQLITE_TRANSIENT);
    sqlite3_bind_int(stmt,11,restaurant.getOwnerId());

    if (sqlite3_step(stmt) != SQLITE_DONE) {
        std::cout << "Error insert : " << sqlite3_errmsg(database->getConnection()) << std::endl;
    }
    sqlite3_finalize(stmt);
}

void RestaurantDAO::deleteRestaurant(const Restaurant& restaurant) {
    std::string sql_delete = "DELETE FROM RESTAURANT WHERE ID =" + std::to_string(restaurant.getID()) +";" ;
    sqlite3_stmt* stmt = nullptr;
    if (sqlite3_prepare_v2(database->getConnection(),sql_delete.c_str(),-1, &stmt, nullptr) != SQLITE_OK) {
        std::cout << "Error Delete : " << sqlite3_errmsg(database->getConnection()) << std::endl;
    }
    else {
        sqlite3_bind_int(stmt,1,restaurant.getID());
        if (sqlite3_step(stmt) != SQLITE_DONE) {
            std::cout << "Error Delete : " << sqlite3_errmsg(database->getConnection()) << std::endl;
        }
        sqlite3_finalize(stmt);
    }
}

bool RestaurantDAO::updateRestaurant(const Restaurant &restaurant) {
    std::string sql_update = "UPDATE RESTAURANT SET "
                             "NAME = ?,"
                             "CITY = ?,"
                             "STREET = ?,"
                             "ALLEY = ?,"
                             "BLOCK = ?,"
                             "ACTIVE = ?,"
                             "OPERATION_TIME = ?,"
                             "PHONE = ?,"
                             "INFORMATION = ?,"
                             "OWNER_ID = ?,"
                             "WHERE ID = ?;";

    sqlite3_stmt* stmt = nullptr;
    if (sqlite3_prepare_v2(database->getConnection(),sql_update.c_str(),-1, &stmt, NULL) != SQLITE_OK) {
        std::cout << "Error Insert : " << sqlite3_errcode(database->getConnection()) << std::endl;
        return false;
    }

    sqlite3_bind_text(stmt,1,restaurant.getName().c_str(),-1,SQLITE_TRANSIENT);
    sqlite3_bind_text(stmt,2,restaurant.getAddress().get_cityName().c_str(),-1,SQLITE_TRANSIENT);
    sqlite3_bind_text(stmt,3,restaurant.getAddress().get_streetName().c_str(),-1,SQLITE_TRANSIENT);
    sqlite3_bind_text(stmt,4,restaurant.getAddress().get_alleyName().c_str(),-1,SQLITE_TRANSIENT);
    sqlite3_bind_int(stmt,5,restaurant.getAddress().get_block());
    sqlite3_bind_int(stmt,6,restaurant.getActive());
    sqlite3_bind_int(stmt,7,restaurant.getOperationTime());
    sqlite3_bind_text(stmt,8,restaurant.getPhone().c_str(),-1,SQLITE_TRANSIENT);
    sqlite3_bind_text(stmt,9,restaurant.getInformation().c_str(),-1,SQLITE_TRANSIENT);
    sqlite3_bind_int(stmt,10,restaurant.getOwnerId());
    sqlite3_bind_int(stmt,11,restaurant.getID());

    bool success = (sqlite3_step(stmt) == SQLITE_DONE);
    sqlite3_finalize(stmt);
    return success;
}

Restaurant RestaurantDAO::getRestaurantById(int Id) {
    std::string sql = "SELECT * FROM RESTAURANT WHERE ID = ?;";
    Restaurant restaurant;
    sqlite3_stmt* stmt;
    if (sqlite3_prepare_v2(database->getConnection(), sql.c_str(), -1, &stmt, nullptr) != SQLITE_OK) {
        throw std::runtime_error(sqlite3_errmsg(database->getConnection()));
    }
    sqlite3_bind_int(stmt,1,Id);
    if (sqlite3_step(stmt) == SQLITE_ROW) {
        restaurant.setId(sqlite3_column_int(stmt,0));
        restaurant.setName(reinterpret_cast<const char*>(sqlite3_column_text(stmt,1)));

        Address address;
        address.set_cityName(reinterpret_cast<const char*>(sqlite3_column_text(stmt,2)));
        address.set_streetName(reinterpret_cast<const char*>(sqlite3_column_text(stmt,3)));
        address.set_alleyName(reinterpret_cast<const char*>(sqlite3_column_text(stmt,4)));
        address.set_block(sqlite3_column_int(stmt,5));

        restaurant.setAddress(address);
        restaurant.setActive(sqlite3_column_int(stmt,6));
        restaurant.setOperationTime(sqlite3_column_int(stmt,7));
        restaurant.setPhone(reinterpret_cast<const char*>(sqlite3_column_text(stmt,8)));
        restaurant.setInformation(reinterpret_cast<const char*>(sqlite3_column_text(stmt,9)));
        restaurant.setOwnerId(sqlite3_column_int(stmt,10));
    }
    sqlite3_finalize(stmt);
    return restaurant;
}

std::vector<Restaurant> RestaurantDAO::getRestaurants() {
    std::vector<Restaurant> restaurants;
    std::string sql = "SELECT * FROM RESTAURANT;";
    sqlite3_stmt* stmt = nullptr;
    if (sqlite3_prepare_v2(database->getConnection(), sql.c_str(), -1, &stmt, nullptr) != SQLITE_OK) {
        return restaurants;
    }

    while (sqlite3_step(stmt) == SQLITE_ROW) {
        Address address;
        address.set_cityName(reinterpret_cast<const char*>(sqlite3_column_text(stmt,2)));
        address.set_streetName(reinterpret_cast<const char*>(sqlite3_column_text(stmt,3)));
        address.set_alleyName(reinterpret_cast<const char*>(sqlite3_column_text(stmt,4)));
        address.set_block(sqlite3_column_int(stmt,5));

        Restaurant restaurant;
        restaurant.setId(sqlite3_column_int(stmt,0));
        restaurant.setName(reinterpret_cast<const char*>(sqlite3_column_text(stmt,1)));
        restaurant.setAddress(address);
        restaurant.setActive(sqlite3_column_int(stmt,6));
        restaurant.setOperationTime(sqlite3_column_int(stmt,7));
        restaurant.setPhone(reinterpret_cast<const char*>(sqlite3_column_text(stmt,8)));
        restaurant.setInformation(reinterpret_cast<const char*>(sqlite3_column_text(stmt,9)));
        restaurant.setOwnerId(sqlite3_column_int(stmt,10));
        restaurants.push_back(restaurant);
    }
    sqlite3_finalize(stmt);
    return restaurants;
}
