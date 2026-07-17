
#ifndef FOOD_ORDERING_SYSTEM_CUSTOMERDAO_H
#define FOOD_ORDERING_SYSTEM_CUSTOMERDAO_H

#include <vector>

#include "models/Customer.h"
#include "dao/Database.h"

class CustomerDAO {
    public:
    CustomerDAO(Database* database);
    bool insertCustomer(const Customer& customer);
    bool deleteCustomer(const Customer& customer);
    bool updateCustomer(const Customer& customer);
    Customer getCustomerById(int Id);
    std::vector<Customer> getCustomers();
    bool existByphone(const std::string& phone);
    Customer getCustomerByPhone(const std::string& phone);
    bool checkPassword(const std::string& phone, const std::string& password);

    private:
    Database* database;
};

#endif //FOOD_ORDERING_SYSTEM_CUSTOMERDAO_H