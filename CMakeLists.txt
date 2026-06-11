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
)

target_include_directories(Food_ordering_system PRIVATE include)
