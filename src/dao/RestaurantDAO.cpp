
#include "dao/RestaurantDAO.h"
#include "models/Restaurant.h"

RestaurantDAO::RestaurantDAO(Database* database) {
    this->database = database;
}

void RestaurantDAO::insertRestaurant(const Restaurant& restaurant) {
    sqlite3_stmt* stmt = nullptr;
    std::string sql = "INSERT INTO RESTAURANT ( ID, NAME, CITY, STREET, ALLEY, BLOCK, ACTIVE, OPERATION_TIME, PHONE, INFORMATION )"
                      " VALUES (?,?,?,?,?,?,?,?,?,?)";
    int rc = sqlite3_prepare_v2(database->getConnection(), sql.c_str(), -1, &stmt, NULL);
    if (rc != SQLITE_OK) {
        std::cerr << "Error Insert : " << sqlite3_errcode(database->getConnection()) << std::endl;
    }
    sqlite3_bind_int(stmt,1,restaurant.get_ID());
    sqlite3_bind_text(stmt,2,restaurant.get_name().c_str(),-1,SQLITE_TRANSIENT);
    sqlite3_bind_text(stmt,3,restaurant.get_address().get_cityName().c_str(),-1,SQLITE_TRANSIENT);
    sqlite3_bind_text(stmt,4,restaurant.get_address().get_streetName().c_str(),-1,SQLITE_TRANSIENT);
    sqlite3_bind_text(stmt,5,restaurant.get_address().get_alleyName().c_str(),-1,SQLITE_TRANSIENT);
    sqlite3_bind_int(stmt,6,restaurant.get_address().get_block());
    sqlite3_bind_int(stmt,7,restaurant.get_active());
    sqlite3_bind_int(stmt,8,restaurant.get_operationTime());
    sqlite3_bind_text(stmt,9,restaurant.get_phone().c_str(),-1,SQLITE_TRANSIENT);
    sqlite3_bind_text(stmt,10,restaurant.get_information().c_str(),-1,SQLITE_TRANSIENT);

    char* messageError;
    int exit = sqlite3_exec(database->getConnection(), sql.c_str(), NULL, 0, &messageError);
    if (exit != SQLITE_OK) {
        std::cerr << "Error Insert : " << messageError << std::endl;
        sqlite3_free(messageError);
    } else {
        std::cout << "Records created successfully!" << std::endl;
    }
}

void RestaurantDAO::deleteRestaurant(const Restaurant& restaurant) {
    std::string sql_delete = "DELETE FROM RESTAURANT WHERE ID =" + std::to_string(restaurant.get_ID()) +";" ;
    char* messageError;
    sqlite3_exec(database->getConnection(), sql_delete.c_str(), NULL, 0, &messageError);
}

bool RestaurantDAO::updateRestaurant(const Restaurant &restaurant) {}

std::vector<Restaurant> RestaurantDAO::getRestaurants() {
    std::vector<Restaurant> restaurants;
    std::string sql = "SELECT * FROM RESTAURANTS;";
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
        restaurant.set_id(sqlite3_column_int(stmt,0));
        restaurant.set_name(reinterpret_cast<const char*>(sqlite3_column_text(stmt,1)));
        restaurant.set_address(address);
        restaurant.set_active(sqlite3_column_int(stmt,6));
        restaurant.set_operationTime(sqlite3_column_int(stmt,7));
        restaurant.set_phone(reinterpret_cast<const char*>(sqlite3_column_text(stmt,8)));
        restaurant.set_information(reinterpret_cast<const char*>(sqlite3_column_text(stmt,9)));
        restaurants.push_back(restaurant);
    }
    sqlite3_finalize(stmt);
    return restaurants;
}
