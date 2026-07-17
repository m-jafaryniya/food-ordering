
#include "services/CustomerService.h"

CustomerService::CustomerService(Database* database)
    : customerDAO(database), restaurantDAO(database), menuDAO(database), orderDAO(database){}

std::vector<Restaurant> CustomerService::getAllRstaurants() {
    return restaurantDAO.getRestaurants();
}

std::vector<Menu*> CustomerService::getRestaurantMenu(int restaurantId) {
    return menuDAO.getRestaurantMenu(restaurantId);
}

bool CustomerService::addToCart(int restaurantId, int itemId, int quantity) {
    auto foodOpt = menuDAO.getFoodById(itemId);
    auto drinkOpt = menuDAO.getDrinkById(itemId);

    double price = 0.0;
    bool found = false;

    if (foodOpt.has_value()) {
        price = foodOpt->get_BasePrice();
        found = true;
    }
    else if (drinkOpt.has_value()) {
        price = drinkOpt->get_BasePrice();
        found = true;
    }
    if (!found) {
        std::cout << "Item not found!" << std::endl;
        return false;
    }
    cart.addItem(itemId, price, quantity);
    return true;
}

void CustomerService::removeFromCart(int itemId) {
    cart.removeItem(itemId);
}

void CustomerService::clearCart() {
    cart.clear();
}

Cart CustomerService::getCart() {
    return cart;
}

double CustomerService::calculateCost() {
    double cost = 0;
    for (const CartItem& item : cart.get_items()) {
        cost += item.get_totalPrice();
    }
    return cost;
}

bool CustomerService::placeOrder(int customerId, int restaurantId) {
    if (cart.get_items().empty()) {
        std::cout << "Cart is empty!" << std::endl;
        return false;
    }
    double cost = cart.get_totalPrice();

    static int orderIdCounter = 100;
    Order order;
    order.set_orderId(orderIdCounter++);
    order.set_customerId(customerId);
    order.set_restaurantId(restaurantId);
    order.set_totalPrice(cost);
    order.set_status(OrderStatus::pending);

    for (const CartItem& item : cart.get_items()) {
        order.get_cartItems().push_back(item);
    }

    if ( !orderDAO.insertOrder(order) ) {
        std::cout << "Failed to insert order!" << std::endl;
        return false;
    }
    if (!orderDAO.insertOrderItems(order.get_orderId(), cart.get_items())) {
        std::cout << "Failed to insert order items!" << std::endl;
        orderDAO.deleteOrder(order.get_orderId());
        return false;
    }
    cart.clear();
    std::cout << "Successfully inserted order!" << std::endl;
    std::cout << "Order ID: " << order.get_orderId() << std::endl;
    return true;
}

std::vector<Order> CustomerService::getOrders(int customerId) {
    return orderDAO.getCustomerOrders(customerId);
}


