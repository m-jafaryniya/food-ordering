cmake_minimum_required(VERSION 4.1)
project(Food_ordering_system)

set(CMAKE_CXX_STANDARD 20)

add_executable(Food_ordering_system main.cpp
        include/models/User.h
        include/models/Customer.h
        include/models/Restaurateur.h
        include/models/SystemAdministrator.h
        include/models/Restaurant.h
        include/models/Menu.h
        src/models/User.cpp
        include/models/IdMaker.h
        src/models/IdMaker.cpp
        src/models/Menu.cpp
        include/models/Food.h
        include/models/Drink.h
        include/services/Cart.h
        src/models/Food.cpp
        src/models/Drink.cpp
        src/models/Restaurant.cpp
        include/models/Address.h
        src/models/Address.cpp
        src/models/Restaurateur.cpp
        src/models/SystemAdministrator.cpp
        src/models/Customer.cpp
        src/services/Cart.cpp
        include/services/CartItem.h
        src/services/CartItem.cpp
        include/dao/Database.h
        sqlite/sqlite3.h
        sqlite/sqlite3.c
        src/dao/Database.cpp
        include/dao/CustomerDAO.h
        src/dao/CustomerDAO.cpp
        include/dao/RestaurantDAO.h
        src/dao/RestaurantDAO.cpp
        include/dao/RestaurateurDAO.h
        src/dao/RestaurateurDAO.cpp
        include/dao/SystemAdministratorDAO.h
        src/dao/SystemAdministratorDAO.cpp
        include/services/Login.h
        src/services/Login.cpp
        include/services/CustomerService.h
        src/services/CustomerService.cpp
        include/dao/MenuDAO.h
        src/dao/MenuDAO.cpp
        include/services/Order.h
        src/services/Order.cpp
        include/dao/CartDAO.h
        src/dao/CartDAO.cpp
)

target_include_directories(Food_ordering_system PRIVATE include)
target_include_directories(Food_ordering_system PRIVATE sqlite)