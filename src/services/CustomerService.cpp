
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
        return false;
    }
    double cost = calculateCost();
    Order order;
    order.set_orderId(1001);
    order.set_customerId(customerId);
    order.set_restaurantId(restaurantId);
    order.set_totalPrice(cost);
    order.set_status(OrderStatus::pending);

    if ( !orderDAO.insertOrder(order) ) {
        return false;
    }
    if (!orderDAO.deleteOrderItems(order.get_orderId())) {
        orderDAO.deleteOrder(order.get_orderId());
        return false;
    }
    cart.clear();
    return true;
}

std::vector<Order> CustomerService::getOrders(int customerId) {
    return orderDAO.getCustomerOrders(customerId);
}


