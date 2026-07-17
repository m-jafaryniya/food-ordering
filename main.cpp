#include <iostream>
#include <limits>
#include <string>
#include <cctype>

#include "dao/CustomerDAO.h"
#include "dao/Database.h"
#include "dao/RestaurantDAO.h"
#include "dao/SystemAdministratorDAO.h"
#include "services/CustomerService.h"
#include "services/RestaurateurService.h"
#include "services/Login.h"
#include "services/SystemAdministratorService.h"
#include "models/Address.h"
#include "models/Food.h"
#include "models/Drink.h"

void clearScreen() {
    #ifdef _WIN32
        system("cls");
    #endif
}

void waitForEnter() {
    std::cout << "Press Enter to continue...";
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    std::cin.get();
}

int getValidatedInt(const std::string& prompt, int min = 0, int max = 99999) {
    int value;
    bool valid = false;
    do {
        std::cout << prompt;
        if (std::cin >> value) {
            if (value >= min && value <= max) {
                valid = true;
            } else {
                std::cout << "Error: Please enter a number between " << min << " and " << max << "." << std::endl;
                std::cin.clear();
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            }
        } else {
            std::cout << "Error: Invalid input. Please enter a number." << std::endl;
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        }
    } while (!valid);
    return value;
}

double getValidatedDouble(const std::string& prompt, double min = 0) {
    double value;
    bool valid = false;
    do {
        std::cout << prompt;
        if (std::cin >> value) {
            if (value >= min) {
                valid = true;
            } else {
                std::cout << "Error: Price must be positive." << std::endl;
                std::cin.clear();
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            }
        } else {
            std::cout << "Error: Invalid input. Please enter a number." << std::endl;
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        }
    } while (!valid);
    return value;
}

std::string getValidatedString(const std::string& prompt, bool allowEmpty = false) {
    std::string value;
    bool valid = false;
    do {
        std::cout << prompt;
        std::getline(std::cin, value);
        size_t start = value.find_first_not_of(" \t\n\r");
        if (start != std::string::npos) {
            value = value.substr(start);
        } else {
            value = "";
        }

        if (allowEmpty || !value.empty()) {
            valid = true;
        } else {
            std::cout << "Error: Input cannot be empty. Please try again." << std::endl;
        }
    } while (!valid);
    return value;
}

int getMenuChoice(int min, int max) {
    return getValidatedInt("Enter choice: ", min, max);
}

// ============ منوهای اصلی ============

void showCustomerMenu(CustomerService& service, Customer* customer) {
    int choice;
    do {
        //clearScreen();
        std::cout << "===== CUSTOMER MENU =====" << std::endl;
        std::cout << "Welcome, " << customer->getUserName() << "!" << std::endl;
        std::cout << "Your Wallet: " << customer->getWallet() << std::endl;
        std::cout << "----------------------------------------" << std::endl;
        std::cout << "1. View All Restaurants" << std::endl;
        std::cout << "2. View Restaurant Menu" << std::endl;
        std::cout << "3. View Cart" << std::endl;
        std::cout << "4. Add Item to Cart" << std::endl;
        std::cout << "5. Remove Item from Cart" << std::endl;
        std::cout << "6. Clear Cart" << std::endl;
        std::cout << "7. Place Order" << std::endl;
        std::cout << "8. View Order History" << std::endl;
        std::cout << "0. Logout" << std::endl;
        std::cout << "----------------------------------------" << std::endl;
        choice = getMenuChoice(0, 8);

        switch (choice) {
            case 1: {
                //clearScreen();
                std::cout << "===== ALL RESTAURANTS =====" << std::endl;
                std::vector<Restaurant> restaurants = service.getAllRstaurants();
                if (restaurants.empty()) {
                    std::cout << "No restaurants available." << std::endl;
                } else {
                    std::cout << "----------------------------------------" << std::endl;
                    for (const auto& r : restaurants) {
                        std::cout << "ID: " << r.getID()
                                  << " Restaurant Name: " << r.getName()
                                  << " Active: " << (r.getActive() ? "Yes" : "No")
                                  << " Operation Time: " << r.getOperationTime() << "min" << std::endl;
                    }
                    std::cout << "----------------------------------------" << std::endl;
                }
                waitForEnter();
                break;
            }
            case 2: {
                //clearScreen();
                int restaurantId = getValidatedInt("Enter Restaurant ID: ",10000,1000000);

                std::vector<Menu*> menu = service.getRestaurantMenu(restaurantId);
                clearScreen();
                std::cout << "===== RESTAURANT MENU =====" << std::endl;
                if (menu.empty()) {
                    std::cout << "No menu items available for this restaurant." << std::endl;
                } else {
                    std::cout << "----------------------------------------" << std::endl;
                    for (Menu* item : menu) {
                        std::cout << "Menu Item ID: " << item->get_ItemId()
                                  << "Menu Item Name: " << item->get_ItemName()
                                  << "Price: " << item->get_BasePrice()
                                  << "Available: " << (item->get_available() ? "Yes" : "No") << std::endl;
                        if (Food* food = dynamic_cast<Food*>(item)) {
                            std::cout << "   Type: Food | Cook Time: " << food->get_cookTime() << "min" << std::endl;
                        } else if (Drink* drink = dynamic_cast<Drink*>(item)) {
                            std::cout << "   Type: Drink | Volume: " << drink->get_volume() << "ml" << std::endl;
                        }
                    }
                    std::cout << "----------------------------------------" << std::endl;
                }
                waitForEnter();
                break;
            }
            case 3: {
                //clearScreen();
                Cart cart = service.getCart();
                std::cout << "===== YOUR CART =====" << std::endl;
                if (cart.get_items().empty()) {
                    std::cout << "Cart is empty." << std::endl;
                } else {
                    std::cout << "----------------------------------------" << std::endl;
                    for (const auto& item : cart.get_items()) {
                        std::cout << "Item ID: " << item.get_itemId()
                                  << "Quantity: " << item.get_quantity()
                                  << "Unit Price: " << item.get_unitPrice()
                                  << "Item Total Price: " << item.get_totalPrice() << std::endl;
                    }
                    std::cout << "----------------------------------------" << std::endl;
                    std::cout << "Total Price: " << cart.get_totalPrice() << std::endl;
                    std::cout << "----------------------------------------" << std::endl;
                }
                waitForEnter();
                break;
            }
            case 4: {
                //clearScreen();
                std::cout << "===== ADD ITEM TO CART =====" << std::endl;
                int restaurantId = getValidatedInt("Enter Restaurant ID: ",10000,1000000);
                int itemId = getValidatedInt("Enter Item ID: ");
                int quantity = getValidatedInt("Enter Quantity: ", 1, 100);

                if (service.addToCart(restaurantId, itemId, quantity)) {
                    std::cout << "Item added to cart successfully!" << std::endl;
                } else {
                    std::cout << "Failed to add item to cart. Please check the item ID." << std::endl;
                }
                waitForEnter();
                break;
            }
            case 5: {
                //clearScreen();
                std::cout << "===== REMOVE ITEM FROM CART =====" << std::endl;
                int itemId = getValidatedInt("Enter Item ID to remove: ");
                service.removeFromCart(itemId);
                std::cout << "Item removed from cart." << std::endl;
                waitForEnter();
                break;
            }
            case 6: {
                service.clearCart();
                clearScreen();
                std::cout << "Cart cleared successfully." << std::endl;
                waitForEnter();
                break;
            }
            case 7: {
                //clearScreen();
                Cart cart = service.getCart();
                if (cart.get_items().empty()) {
                    std::cout << "Cart is empty! Cannot place order." << std::endl;
                    waitForEnter();
                    break;
                }
                std::cout << "===== PLACE ORDER =====" << std::endl;
                std::cout << "----------------------------------------" << std::endl;
                for (const auto& item : cart.get_items()) {
                    std::cout << "Item ID: " << item.get_itemId()
                              << "Quantity: " << item.get_quantity()
                              << "Total: " << item.get_totalPrice() << std::endl;
                }
                std::cout << "----------------------------------------" << std::endl;
                std::cout << "Total Amount: " << cart.get_totalPrice() << std::endl;
                std::cout << "----------------------------------------" << std::endl;

                int restaurantId = getValidatedInt("Enter Restaurant ID: ",10000,1000000);

                if (service.placeOrder(customer->getId(), restaurantId)) {
                    std::cout << "Order placed successfully!" << std::endl;
                } else {
                    std::cout << "Failed to place order." << std::endl;
                }
                waitForEnter();
                break;
            }
            case 8: {
                //clearScreen();
                std::cout << "===== ORDER HISTORY =====" << std::endl;
                std::vector<Order> orders = service.getOrders(customer->getId());
                if (orders.empty()) {
                    std::cout << "No orders found." << std::endl;
                } else {
                    std::cout << "----------------------------------------" << std::endl;
                    for (const auto& order : orders) {
                        std::cout << "Order ID: " << order.get_orderId()
                                  << "Restaurant: " << order.get_restaurantId()
                                  << "Total: " << order.get_totalPrice()
                                  << "Status: ";
                        switch (order.get_status()) {
                            case OrderStatus::pending: std::cout << "Pending"; break;
                            case OrderStatus::preparing: std::cout << "Preparing"; break;
                            case OrderStatus::ready: std::cout << "Ready"; break;
                            case OrderStatus::delivered: std::cout << "Delivered"; break;
                            case OrderStatus::cancelled: std::cout << "Cancelled"; break;
                        }
                        std::cout << std::endl;
                    }
                    std::cout << "----------------------------------------" << std::endl;
                }
                waitForEnter();
                break;
            }
            case 0:
                clearScreen();
                std::cout << "Logging out..." << std::endl;
                break;
            default:
                std::cout << "Invalid choice! Please try again." << std::endl;
                waitForEnter();
        }
    } while (choice != 0);
}

void showRestaurateurMenu(RestaurateurService& service, Restaurateur* restaurateur) {
    int choice;
    do {
        //clearScreen();
        std::cout << "===== RESTAURATEUR MENU =====" << std::endl;
        std::cout << "Welcome, " << restaurateur->getUserName() << "!" << std::endl;
        std::cout << "----------------------------------------" << std::endl;
        std::cout << "1. View My Restaurants" << std::endl;
        std::cout << "2. Add New Restaurant" << std::endl;
        std::cout << "3. Edit Restaurant" << std::endl;
        std::cout << "4. Change Restaurant Status" << std::endl;
        std::cout << "5. View Menu Items" << std::endl;
        std::cout << "6. Add Menu Item" << std::endl;
        std::cout << "7. Edit Menu Item" << std::endl;
        std::cout << "8. Delete Menu Item" << std::endl;
        std::cout << "9. View Orders" << std::endl;
        std::cout << "10. Update Order Status" << std::endl;
        std::cout << "0. Logout" << std::endl;
        std::cout << "----------------------------------------" << std::endl;
        choice = getMenuChoice(0, 10);

        switch (choice) {
            case 1: {
                //clearScreen();
                std::cout << "===== MY RESTAURANTS =====" << std::endl;
                std::vector<Restaurant> restaurants = service.getRestaurants(restaurateur->getId());
                if (restaurants.empty()) {
                    std::cout << "No restaurants found." << std::endl;
                } else {
                    std::cout << "----------------------------------------" << std::endl;
                    for (const auto& r : restaurants) {
                        std::cout << "ID: " << r.getID() << " | Name: " << r.getName()
                                  << "Active: " << (r.getActive() ? "Yes" : "No")
                                  << "Phone: " << r.getPhone() << std::endl;
                    }
                    std::cout << "----------------------------------------" << std::endl;
                }
                waitForEnter();
                break;
            }
            case 2: {
                //clearScreen();
                std::cout << "===== ADD NEW RESTAURANT =====" << std::endl;
                std::cin.ignore();
                std::string name = getValidatedString("Restaurant Name: ");
                std::string city = getValidatedString("City: ");
                std::string street = getValidatedString("Street: ");
                std::string alley = getValidatedString("Alley: ");
                int block = getValidatedInt("Block: ");
                std::string phone = getValidatedString("Phone: ");
                int operationTime = getValidatedInt("Operation Time (minutes): ", 1, 999);
                std::string info = getValidatedString("Information: ", true);

                Address address(city, street, alley, block);
                Restaurant restaurant(name, address, true, operationTime, phone, info);
                restaurant.setOwnerId(restaurateur->getId());

                if (service.insertRestaurant(*restaurateur, name)) {
                    std::cout << "Restaurant added successfully!" << std::endl;
                } else {
                    std::cout << "Failed to add restaurant." << std::endl;
                }
                waitForEnter();
                break;
            }
            case 3: {
                //clearScreen();
                int restaurantId = getValidatedInt("Enter Restaurant ID to edit: ",10000,1000000);

                Restaurant restaurant = service.getRestaurant(restaurantId);
                if (restaurant.getID() == 0) {
                    std::cout << "Restaurant not found!" << std::endl;
                    waitForEnter();
                    break;
                }

                std::cin.ignore();
                std::cout << "Current Name: " << restaurant.getName() << std::endl;
                std::string name = getValidatedString("New Name (press Enter to keep current): ", true);
                if (!name.empty()) restaurant.setName(name);

                std::cout << "Current Information: " << restaurant.getInformation() << std::endl;
                std::string info = getValidatedString("New Information (press Enter to keep current): ", true);
                if (!info.empty()) restaurant.setInformation(info);

                if (service.editRestaurant(restaurant)) {
                    std::cout << "Restaurant updated successfully!" << std::endl;
                } else {
                    std::cout << "Failed to update restaurant." << std::endl;
                }
                waitForEnter();
                break;
            }
            case 4: {
                //clearScreen();
                int restaurantId = getValidatedInt("Enter Restaurant ID: ",10000,1000000);
                std::cout << "1. Open Restaurant" << std::endl;
                std::cout << "2. Close Restaurant" << std::endl;
                int choice2 = getMenuChoice(1, 2);
                bool isOpen = (choice2 == 1);

                if (service.changeRestaurantStatus(restaurantId, isOpen)) {
                    std::cout << "Restaurant status updated successfully!" << std::endl;
                } else {
                    std::cout << "Failed to update status." << std::endl;
                }
                waitForEnter();
                break;
            }
            case 5: {
                //clearScreen();
                int restaurantId = getValidatedInt("Enter Restaurant ID: ");

                std::vector<Menu*> menu = service.getMenuItems(restaurantId);
                std::cout << "===== MENU ITEMS =====" << std::endl;
                if (menu.empty()) {
                    std::cout << "No items found." << std::endl;
                } else {
                    std::cout << "----------------------------------------" << std::endl;
                    for (Menu* item : menu) {
                        std::cout << "ID: " << item->get_ItemId()
                                  << "Name: " << item->get_ItemName()
                                  << "Price: " << item->get_BasePrice()
                                  << "Available: " << (item->get_available() ? "Yes" : "No") << std::endl;
                    }
                    std::cout << "----------------------------------------" << std::endl;
                }
                waitForEnter();
                break;
            }
            case 6: {
                //clearScreen();
                std::cout << "===== ADD MENU ITEM =====" << std::endl;
                int restaurantId = getValidatedInt("Enter Restaurant ID: ");
                std::cout << "1. Food" << std::endl;
                std::cout << "2. Drink" << std::endl;
                int type = getMenuChoice(1, 2);

                std::cin.ignore();
                std::string name = getValidatedString("Item Name: ");
                std::string description = getValidatedString("Description: ");
                double price = getValidatedDouble("Price: ");

                if (type == 1) {
                    int cookTime = getValidatedInt("Cook Time (minutes): ", 1, 360);
                    Food food(name, description, price, cookTime);
                    if (service.addMenuItem(restaurantId, food)) {
                        std::cout << "Food added successfully!" << std::endl;
                    } else {
                        std::cout << "Failed to add food." << std::endl;
                    }
                } else if (type == 2) {
                    int volume = getValidatedInt("Volume (ml): ", 1, 99999);
                    Drink drink(name, description, price, volume);
                    if (service.addMenuItem(restaurantId, drink)) {
                        std::cout << "Drink added successfully!" << std::endl;
                    } else {
                        std::cout << "Failed to add drink." << std::endl;
                    }
                }
                waitForEnter();
                break;
            }
            case 7: {
                //clearScreen();
                std::cout << "===== EDIT MENU ITEM =====" << std::endl;
                int itemId = getValidatedInt("Enter Item ID to edit: ");

                std::cout << "Feature: Edit item details" << std::endl;
                std::cout << "Note: In full implementation, you can modify name, price, etc." << std::endl;
                waitForEnter();
                break;
            }
            case 8: {
                //clearScreen();
                std::cout << "===== DELETE MENU ITEM =====" << std::endl;
                int itemId = getValidatedInt("Enter Item ID to delete: ");

                Menu* dummy = new Food("dummy", "dummy", 0, 0);
                dummy->set_ItemId(itemId);
                if (service.deleteMenuItem(*dummy)) {
                    std::cout << "Item deleted successfully!" << std::endl;
                } else {
                    std::cout << "Failed to delete item." << std::endl;
                }
                delete dummy;
                waitForEnter();
                break;
            }
            case 9: {
                //clearScreen();
                int restaurantId = getValidatedInt("Enter Restaurant ID: ",10000,1000000);

                std::vector<Order> orders = service.getRestaurantOrders(restaurantId);
                std::cout << "===== ORDERS =====" << std::endl;
                if (orders.empty()) {
                    std::cout << "No orders found." << std::endl;
                } else {
                    std::cout << "----------------------------------------" << std::endl;
                    for (const auto& order : orders) {
                        std::cout << "Order ID: " << order.get_orderId()
                                  << "Customer ID: " << order.get_customerId()
                                  << "Total price: " << order.get_totalPrice()
                                  << "Status: ";
                        switch (order.get_status()) {
                            case OrderStatus::pending: std::cout << "Pending"; break;
                            case OrderStatus::preparing: std::cout << "Preparing"; break;
                            case OrderStatus::ready: std::cout << "Ready"; break;
                            case OrderStatus::delivered: std::cout << "Delivered"; break;
                            case OrderStatus::cancelled: std::cout << "Cancelled"; break;
                        }
                        std::cout << std::endl;
                    }
                    std::cout << "----------------------------------------" << std::endl;
                }
                waitForEnter();
                break;
            }
            case 10: {
                //clearScreen();
                std::cout << "===== UPDATE ORDER STATUS =====" << std::endl;
                int orderId = getValidatedInt("Enter Order ID: ");
                std::cout << "1. Pending" << std::endl;
                std::cout << "2. Preparing" << std::endl;
                std::cout << "3. Ready" << std::endl;
                std::cout << "4. Delivered" << std::endl;
                std::cout << "5. Cancelled" << std::endl;
                int statusChoice = getMenuChoice(1, 5);

                OrderStatus status;
                switch (statusChoice) {
                    case 1: status = OrderStatus::pending; break;
                    case 2: status = OrderStatus::preparing; break;
                    case 3: status = OrderStatus::ready; break;
                    case 4: status = OrderStatus::delivered; break;
                    case 5: status = OrderStatus::cancelled; break;
                    default: status = OrderStatus::pending;
                }

                if (service.changeOrderStatus(orderId, status)) {
                    std::cout << "Order status updated successfully!" << std::endl;
                } else {
                    std::cout << "Failed to update order status." << std::endl;
                }
                waitForEnter();
                break;
            }
            case 0:
                clearScreen();
                std::cout << "Logging out..." << std::endl;
                break;
            default:
                std::cout << "Invalid choice! Please try again." << std::endl;
                waitForEnter();
        }
    } while (choice != 0);
}

void showAdminMenu(SystemAdministratorService& service) {
    int choice;
    do {
        //clearScreen();
        std::cout << "===== ADMIN MENU =====" << std::endl;
        std::cout << "----------------------------------------" << std::endl;
        std::cout << "1. View All Restaurants" << std::endl;
        std::cout << "2. Add New Restaurant" << std::endl;
        std::cout << "3. Activate/Deactivate Restaurant" << std::endl;
        std::cout << "4. View System Report" << std::endl;
        std::cout << "0. Logout" << std::endl;
        std::cout << "----------------------------------------" << std::endl;
        choice = getMenuChoice(0, 4);

        switch (choice) {
            case 1: {
                //clearScreen();
                std::cout << "===== ALL RESTAURANTS =====" << std::endl;
                std::vector<Restaurant> restaurants = service.getRestaurants();
                if (restaurants.empty()) {
                    std::cout << "No restaurants found." << std::endl;
                } else {
                    std::cout << "----------------------------------------" << std::endl;
                    for (const auto& r : restaurants) {
                        std::cout << "ID: " << r.getID() << " Name: " << r.getName()
                                  << "Active: " << (r.getActive() ? "Yes" : "No")
                                  << "Owner ID: " << r.getOwnerId() << std::endl;
                    }
                    std::cout << "----------------------------------------" << std::endl;
                }
                waitForEnter();
                break;
            }
            case 2: {
                //clearScreen();
                std::cout << "===== ADD NEW RESTAURANT =====" << std::endl;
                std::cin.ignore();
                std::string name = getValidatedString("Restaurant Name: ");
                std::string city = getValidatedString("City: ");
                std::string street = getValidatedString("Street: ");
                std::string alley = getValidatedString("Alley: ");
                int block = getValidatedInt("Block: ");
                std::string phone = getValidatedString("Phone: ");
                int operationTime = getValidatedInt("Operation Time (minutes): ", 1, 999);
                int ownerId = getValidatedInt("Owner ID: ");
                std::string info = getValidatedString("Information: ", true);

                Address address(city, street, alley, block);
                Restaurant restaurant(name, address, true, operationTime, phone, info);
                restaurant.setOwnerId(ownerId);

                if (service.addRestaurant(restaurant)) {
                    std::cout << "Restaurant added successfully!" << std::endl;
                } else {
                    std::cout << "Failed to add restaurant." << std::endl;
                }
                waitForEnter();
                break;
            }
            case 3: {
                //clearScreen();
                std::cout << "===== ACTIVATE/DEACTIVATE RESTAURANT =====" << std::endl;
                int restaurantId = getValidatedInt("Enter Restaurant ID: ",10000,1000000);
                std::cout << "1. Activate" << std::endl;
                std::cout << "2. Deactivate" << std::endl;
                int choice2 = getMenuChoice(1, 2);

                bool success = false;
                if (choice2 == 1) {
                    success = service.activeRestaurant(restaurantId);
                } else if (choice2 == 2) {
                    success = service.deActiveRestaurant(restaurantId);
                }

                if (success) {
                    std::cout << "Restaurant status updated successfully!" << std::endl;
                } else {
                    std::cout << "Failed to update status." << std::endl;
                }
                waitForEnter();
                break;
            }
            case 4: {
                //clearScreen();
                service.systemReport();
                waitForEnter();
                break;
            }
            case 0:
                clearScreen();
                std::cout << "Logging out..." << std::endl;
                break;
            default:
                std::cout << "Invalid choice! Please try again." << std::endl;
                waitForEnter();
        }
    } while (choice != 0);
}

// ============ تابع اصلی ============

int main() {
    try {
        Database db("food_ordering_system.db");
        Login loginManager(&db);

        User* loggedInUser = loginManager.login();
        if (loggedInUser == nullptr) {
            std::cout << "Login Failed" << std::endl;
            return 1;
        }

        std::cout << "\nWelcome " << loggedInUser->getUserName() << "!" << std::endl;
        waitForEnter();

        if (Customer* customer = dynamic_cast<Customer*>(loggedInUser)) {
            CustomerService customerService(&db);
            showCustomerMenu(customerService, customer);
        }
        else if (Restaurateur* restaurateur = dynamic_cast<Restaurateur*>(loggedInUser)) {
            RestaurateurService restaurateurService(&db);
            showRestaurateurMenu(restaurateurService, restaurateur);
        }
        else if (SystemAdministrator* administrator = dynamic_cast<SystemAdministrator*>(loggedInUser)) {
            SystemAdministratorService systemAdministratorService(&db);
            showAdminMenu(systemAdministratorService);
        }

        delete loggedInUser;
        clearScreen();
        std::cout << "Thank you for using Food Ordering System!" << std::endl;
        return 0;
    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
        return 1;
    }
}