
#include "services/Login.h"

User* Login::login() {
    std::string phone;
    std::string password;

    std::cout << "Phone Number :" << std::endl;
    std::cin >> phone;

    if (customerDAO.existByphone(phone)) {
        std::cout << "Password :" << std::endl;
        std::cin >> password;
        if (customerDAO.checkPassword(phone,password)) {
            Customer customer;
            customer = customerDAO.getCustomerByPhone(phone);
            std::cout << "Login successfully! " << std::endl;
            return new Customer(customer);
        }
        std::cout << "Wrong password!" << std::endl;
        return nullptr;
    }

    if (restaurateurDAO.existByPhone(phone)) {
        std::cout << "Password :" << std::endl;
        std::cin >> password;
        if (restaurateurDAO.checkPassword(phone,password)) {
            Restaurateur restaurateur;
            restaurateur = restaurateurDAO.getRestaurateurByPhone(phone);
            std::cout << "Login successfully! " << std::endl;
            return new Restaurateur(restaurateur);
        }
        std::cout << "Wrong password!" << std::endl;
        return nullptr;
    }

    if (systemAdministratorDAO.existByPhone(phone)) {
        std::cout << "Password :" << std::endl;
        std::cin >> password;
        if (systemAdministratorDAO.checkPassword(phone,password)) {
            SystemAdministrator systemAdministrator;
            systemAdministrator = systemAdministratorDAO.getSystemAdministratorByPhone(phone);
            std::cout << "Login successfully! " << std::endl;
            return new SystemAdministrator(systemAdministrator);
        }
        std::cout << "Wrong password!" << std::endl;
        return nullptr;
    }

    std::cout << "You don't have an account yet!" << std::endl;
    std::cout << "Register now!" << std::endl;
    return registerUser(phone);
}

User* Login::registerUser(const std::string& phone) {
    std::string password;
    std::string username;
    std::cout << "Password :" << std::endl;
    std::cin >> password;
    std::cout << "Username :" << std::endl;
    std::cin >> username;

    int role;
    std::cout << "---Choose your role (1/2/3)---" << std::endl;
    std::cout << "1 : Customer" << std::endl << "2 : Restaurateur" << std::endl << "3 : SystemAdministrator" << std::endl;
    std::cin >> role;

    switch (role) {
        case 1: {
            Customer customer(phone, password, username);
            customerDAO.insertCustomer(customer);
            return new Customer(customer);
        }

        case 2: {
            Restaurateur restaurateur(phone, password, username);
            restaurateurDAO.insertRestaurateur(restaurateur);
            return new Restaurateur(restaurateur);
        }

        case 3: {
            SystemAdministrator systemAdministrator(phone, password, username);
            systemAdministratorDAO.insertSystemAdministrator(systemAdministrator);
            return new SystemAdministrator(systemAdministrator);
        }
        default:
            std::cout << "Wrong role!" << std::endl;
            return nullptr;
    }
}