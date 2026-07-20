#include "services//Login.h"
#include <iostream>
#include "models/Customer.h"
#include "models/Restaurateur.h"
#include "models/SystemAdministrator.h"
#include "models/IdMaker.h"

Login::Login(Database* database)
    : database(database),
      customerDAO(database),
      restaurateurDAO(database),
      systemAdministratorDAO(database) {}

User* Login::login() {
    std::string phone;
    std::cout << "---Welcome to Food Ordering System---" << std::endl;
    std::cout << "Enter your phone number: ";
    std::cin >> phone;

    bool isCustomer = customerDAO.existByphone(phone);
    bool isRestaurateur = restaurateurDAO.existByPhone(phone);
    bool isAdmin = systemAdministratorDAO.existByPhone(phone);

    if (isCustomer || isRestaurateur || isAdmin) {
        std::string password;
        std::cout << "User found." << std::endl <<  "Enter password: ";
        std::cin >> password;

        if (isCustomer && customerDAO.checkPassword(phone, password)) {
            Customer* c = new Customer();
            *c = customerDAO.getCustomerByPhone(phone);
            return c;
        }
        if (isRestaurateur && restaurateurDAO.checkPassword(phone, password)) {
            Restaurateur* r = new Restaurateur();
            *r = restaurateurDAO.getRestaurateurByPhone(phone);
            return r;
        }
        if (isAdmin && systemAdministratorDAO.checkPassword(phone, password)) {
            SystemAdministrator* a = new SystemAdministrator();
            *a = systemAdministratorDAO.getSystemAdministratorByPhone(phone);
            return a;
        }
        else {
            std::cout << "Invalid password!" << std::endl;
            return nullptr;
        }
    } else {
        std::cout << "Phone number not registered!" << std::endl;
        std::cout << "Let's create new account!" << std::endl;
        User* newUser = registerUser(phone);

        if (newUser == nullptr) {
            std::cout << "registration failed!" << std::endl;
            return  nullptr;
        }
        return newUser;
    }
}

User* Login::registerUser(const std::string& phone) {
    std::string username, password;
    std::cout << "Enter Username: ";
    std::cin >> username;
    std::cout << "Enter Password: ";
    std::cin >> password;

    std::cout << "Choose your role:" << std::endl;
    std::cout << "1. Customer" << std::endl;
    std::cout << "2. Restaurateur" << std::endl;
    std::cout << "3. System Administrator" << std::endl;
    int roleChoice;
    std::cin >> roleChoice;

    if (roleChoice == 1) {
        Customer customer;
        customer.setId(IdMaker::getUserID());
        customer.setPhoneNumber(phone);
        customer.setUserName(username);
        customer.setPassword(password);
        customer.setWallet(0.0);

        if (customerDAO.insertCustomer(customer)) {
            std::cout << "Registration successful as Customer!" << std::endl;
            Customer* c = new Customer();
            *c = customer;
            return c;
        }
    }
    else if (roleChoice == 2) {
        Restaurateur restaurateur;
        restaurateur.setId(IdMaker::getUserID());
        restaurateur.setPhoneNumber(phone);
        restaurateur.setUserName(username);
        restaurateur.setPassword(password);

        if (restaurateurDAO.insertRestaurateur(restaurateur)) {
            std::cout << "Registration successful as Restaurateur!" << std::endl;
            Restaurateur* r = new Restaurateur();
            *r = restaurateur;
            return r;
        }
    }
    else if (roleChoice == 3) {
        SystemAdministrator systemAdministrator;
        systemAdministrator.setId(IdMaker::getUserID());
        systemAdministrator.setPhoneNumber(phone);
        systemAdministrator.setUserName(username);
        systemAdministrator.setPassword(password);

        if (systemAdministratorDAO.insertSystemAdministrator(systemAdministrator)) {
            std::cout << "Registration successful as System Administrator!" << std::endl;
            SystemAdministrator* s = new SystemAdministrator();
            *s = systemAdministrator;
            return s;
        }
    }
    else {
        std::cout << "Invalid role choice!" << std::endl;
    }

    return nullptr;
}