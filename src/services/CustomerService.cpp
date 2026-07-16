
#include "services/CustomerService.h"

CustomerService::CustomerService() {
}

std::vector<Restaurant> CustomerService::getAllRstaurants() {
    return restaurantDAO.getRestaurants();
}

std::vector<Menu*> CustomerService::getRestaurantMenu(int restaurantId) {
    return menuDAO.getRestaurantMenu(restaurantId);
}

bool CustomerService::addToCart(int restaurantId, int itemId, int quantity) {
    if (quantity <= 0) return false;
    Menu* menu = menuDAO.getFoodById(itemId);
    if (menu == nullptr) {
        menu = menuDAO.getDrinkById(itemId);
        if (menu == nullptr) {
            return false;
        }
    }
    if (cart.get_items().empty()) {
        cart.
    }
    if (cart.get_restaurantId() != restaurantId) {
        return false;
    }
    CartItem item;
    item.set_itemId(itemId);
    item.set_quantity(quantity);
    item.set_unitPrice(menu->get_BasePrice());
    cart.addItem(item);
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
    order.set_orderId(orderDAO);
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


