
#include "dao/CustomerDAO.h"
#include "models/Customer.h"
#include "models/User.h"

CustomerDAO::CustomerDAO(Database* database) {
    this->database = database;
}

void CustomerDAO::insertCustomer(const Customer& customer) {
    std::string sql = "INSERT INTO CUSTOMER ( PHONE, PASSWORD, USERNAME, ID) VALUES ('" +
        customer.get_phoneNumber() + "', '" +
            customer.get_password() + "', '" +
                customer.get_userName() + "', '" +
                    std::to_string(customer.get_id()) + "');";
    char* messageError;
    int exit = sqlite3_exec(database->getConnection(), sql.c_str(), NULL, 0, &messageError);
    if (exit != SQLITE_OK) {
        std::cerr << "Error Insert : " << messageError << std::endl;
        sqlite3_free(messageError);
    } else {
        std::cout << "Records created successfully!" << std::endl;
    }
}

void CustomerDAO::deleteCustomer(const Customer& customer) {
    std::string sql_delete = "DELETE FROM CUSTOMER WHERE ID =" + std::to_string(customer.get_id()) + ";";
    char* messageError;
    sqlite3_exec(database->getConnection(), sql_delete.c_str(), nullptr, 0, &messageError);
}

bool CustomerDAO::updateCustomer(const Customer& customer) {
    std::string sql_update = "UPDATE CUSTOMER set PHONE='" +
        customer.get_phoneNumber() + "' " +
            ",PASSWORD='" + customer.get_password() + "' " +
                ",USERNAME='" + customer.get_userName() + "' " +
                    "WHERE ID=" + std::to_string(customer.get_id()) + ";";
    char* messageError;
    sqlite3_exec(database->getConnection(), sql_update.c_str(), nullptr, 0, &messageError);
}

static int callbackGetCustomer(void* data, int argc, char** argv, char** azColName) {
    Customer* customer = static_cast<Customer*>(data);
    if (argc>=4) {
        customer->set_phoneNumber(argv[0]);
        customer->set_password(argv[1]);
        customer->set_userName(argv[2]);
    }

    return 0;
}

Customer CustomerDAO::getCustomerById(int id) {
    Customer customer;
    char* messageError = nullptr;
    std::string sql = "SELECT PHONE, PASSWORD, USERNAME FROM CUSTOMER WHERE ID = " + std::to_string(id) + ";";

    int exit = sqlite3_exec(database->getConnection(), sql.c_str(), callbackGetCustomer, &customer, &messageError);
    if (exit != SQLITE_OK) {
        std::cerr << "Error Insert : " << messageError << std::endl;
        sqlite3_free(messageError);
    }
    return customer;
}

static int callbackGetCustomers(void* data, int argc, char** argv, char** azColName) {
    std::vector<Customer>* customers = static_cast<std::vector<Customer>*>(data);
    Customer customer;

    customer.set_phoneNumber(argv[0]);
    customer.set_password(argv[1]);
    customer.set_userName(argv[2]);
    customer.set_id(std::atoi(argv[3]));
    customers->push_back(customer);
    return 0;
}

std::vector<Customer> CustomerDAO::getCustomers() {
    std::vector<Customer> customers;
    char* messageError = nullptr;
    std::string sql = "SELECT * FROM CUSTOMERS;";
    int exit = sqlite3_exec(database->getConnection(), sql.c_str(), callbackGetCustomers, &customers, &messageError);
    if (exit != SQLITE_OK) {
        std::cerr << "Error Insert : " << messageError << std::endl;
        sqlite3_free(messageError);
    }
    return customers;
}

static int callbackExists(void* data, int argc, char** argv, char** azColName) {
    bool* exists = static_cast<bool*>(data);
    *exists = true;
    return 0;
}

bool CustomerDAO::existByphone(const std::string &phone) {
    bool exists = false;
    std::string sql = "SELECT ID FROM CUSTOMER WHERE PHONE='" + phone + "';";
    char *messageError;
    sqlite3_exec(database->getConnection(), sql.c_str(), callbackExists, &exists, &messageError);
    if (messageError) {
        sqlite3_free(messageError);
    }
    return exists;
}

static int callbackCustomerByPhone(void* data, int argc, char** argv, char** azColName) {
    Customer* customer = static_cast<Customer*>(data);
    customer->set_phoneNumber(argv[0]);
    customer->set_password(argv[1]);
    customer->set_userName(argv[2]);
    customer->set_id(std::atoi(argv[3]));
    return 0;
}

Customer CustomerDAO::getCustomerByPhone(const std::string& phone) {
    Customer customer;
    char* messageError = nullptr;
    std::string sql = "SELECT PHONE, PASSWORD, USERNAME, ID ""FROM CUSTOMER WHERE PHONE='" + phone + "';";
    sqlite3_exec(database->getConnection(), sql.c_str(), callbackCustomerByPhone, &customer, &messageError);
    if (messageError) {
        sqlite3_free(messageError);
    }
    return customer;
}

static int callbackPassword(void* data, int argc, char** argv, char** azColName) {
    std::string* password = static_cast<std::string*>(data);
    *password = argv[0];
    return 0;
}

bool CustomerDAO::checkPassword(const std::string &phone, const std::string &password) {
    std::string dbPassword;
    std::string sql = "SELECT PASSWORD FROM CUSTOMER ""WHERE PHONE='" + phone + "';";
    char *messageError;
    sqlite3_exec(database->getConnection(), sql.c_str(), callbackPassword, &dbPassword, &messageError);
    if (messageError) {
        sqlite3_free(messageError);
    }
    return dbPassword == password;
}
