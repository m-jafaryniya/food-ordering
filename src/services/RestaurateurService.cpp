
#include "services/RestaurateurService.h"

RestaurateurService::RestaurateurService(Database* database)
    :restaurantDAO(database),menuDAO(database),orderDAO(database){}

bool RestaurateurService::insertRestaurant(const Restaurateur &owner, const std::string name) {
    Restaurant restaurant;
    restaurant.setOwnerId(owner.getId());
    restaurant.setName(name);
    restaurant.setActive(true);
    restaurant.setOperationTime(30);
    restaurant.setPhone("");
    restaurant.setInformation("");
    Address address("", "", "", 0);
    restaurant.setAddress(address);

    restaurantDAO.insertRestaurant(restaurant);
    return true;
}

bool RestaurateurService::editRestaurant(const Restaurant &restaurant) {
    restaurantDAO.updateRestaurant(restaurant);
    return true;
}

bool RestaurateurService::deleteRestaurant(int restaurantId) {
    menuDAO.deleteDrink(restaurantId);
    menuDAO.deleteFood(restaurantId);

    Restaurant restaurant;
    restaurant.setId(restaurantId);
    restaurantDAO.deleteRestaurant(restaurant);
    return true;
}

bool RestaurateurService::changeRestaurantStatus(int restaurantId, bool isOpen) {
    Restaurant restaurant = restaurantDAO.getRestaurantById(restaurantId);
    restaurant.setActive(isOpen);
    return restaurantDAO.updateRestaurant(restaurant);
}

Restaurant RestaurateurService::getRestaurant(int restaurantId) {
    return restaurantDAO.getRestaurantById(restaurantId);
}

std::vector<Restaurant> RestaurateurService::getRestaurants(int ownerId) {
    std::vector<Restaurant> allRestaurants = restaurantDAO.getRestaurants();
    std::vector<Restaurant> ownerRestaurants;

    for (const Restaurant& restaurant : allRestaurants) {
        if (restaurant.getOwnerId() == ownerId) {
            ownerRestaurants.push_back(restaurant);
        }
    }
    return ownerRestaurants;
}

bool RestaurateurService::addMenuItem(int restaurantId, const Menu &item) {
    if (dynamic_cast<const Food*>(&item)) {
        const Food *food = dynamic_cast<const Food*>(&item);
        return menuDAO.addFood(restaurantId, *food);
    }
    if (dynamic_cast<const Drink*>(&item)) {
        const Drink *drink = dynamic_cast<const Drink*>(&item);
        return menuDAO.addDrink(restaurantId, *drink);
    }
    return false;
}

bool RestaurateurService::editMenuItem(const Menu &item) {
    if (dynamic_cast<const Food*>(&item)) {
        const Food *food = dynamic_cast<const Food*>(&item);
        return menuDAO.updateFood(*food);
    }
    if (dynamic_cast<const Drink*>(&item)) {
        const Drink *drink = dynamic_cast<const Drink*>(&item);
        return menuDAO.updateDrink(*drink);
    }
    return false;
}

bool RestaurateurService::deleteMenuItem(const Menu &item) {
    if (dynamic_cast<const Food*>(&item)) {
        return menuDAO.deleteFood(item.get_ItemId());
    }
    if (dynamic_cast<const Drink*>(&item)) {
        return menuDAO.deleteDrink(item.get_ItemId());
    }
    return false;
}

bool RestaurateurService::changeMenuItemPrice(int itemId, double newPrice) {
    auto foodOpt = menuDAO.getFoodById(itemId);
    if (foodOpt.has_value()) {
        Food food = foodOpt.value();
        food.set_BasePrice(newPrice);
        return menuDAO.updateFood(food);
    }

    auto DrinkOpt = menuDAO.getDrinkById(itemId);
    if (DrinkOpt.has_value()) {
        Drink drink = DrinkOpt.value();
        drink.set_BasePrice(newPrice);
        return menuDAO.updateDrink(drink);
    }
    return false;
}

bool RestaurateurService::changeMenuItemAvailability(int itemId, bool available) {
    auto foodOpt = menuDAO.getFoodById(itemId);
    if (foodOpt.has_value()) {
        Food food = foodOpt.value();
        food.set_available(available);
        return menuDAO.updateFood(food);
    }

    auto DrinkOpt = menuDAO.getDrinkById(itemId);
    if (DrinkOpt.has_value()) {
        Drink drink = DrinkOpt.value();
        drink.set_available(available);
        return menuDAO.updateDrink(drink);
    }
    return false;
}

std::vector<Menu *> RestaurateurService::getMenuItems(int restaurantId) {
    return menuDAO.getRestaurantMenu(restaurantId);
}

std::vector<Order> RestaurateurService::getRestaurantOrders(int restaurantId) {
    return  orderDAO.getRestaurantOrders(restaurantId);
}

std::vector<Order> RestaurateurService::getPendingOrders(int restaurantId) {
    std::vector<Order> allOrders = orderDAO.getRestaurantOrders(restaurantId);
    std::vector<Order> pendingOrders;

    for (const Order &order : allOrders) {
        if (order.get_status() == OrderStatus::pending) {
            pendingOrders.push_back(order);
        }
    }
    return pendingOrders;
}

bool RestaurateurService::changeOrderStatus(int orderId, OrderStatus status) {
    orderDAO.updateOrderStatus(orderId, status);
    return true;
}

bool RestaurateurService::acceptOrder(int orderId) {
    changeOrderStatus(orderId, OrderStatus::preparing);
    return true;
}

bool RestaurateurService::cancelOrder(int orderId) {
    changeOrderStatus(orderId, OrderStatus::cancelled);
    return true;
}

bool RestaurateurService::readyOrder(int orderId) {
    changeOrderStatus(orderId, OrderStatus::ready);
    return true;
}

bool RestaurateurService::deliveredOrder(int orderId) {
    changeOrderStatus(orderId, OrderStatus::delivered);
    return true;
}


