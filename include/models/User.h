
#ifndef FOOD_ORDERING_SYSTEM_USER_H
#define FOOD_ORDERING_SYSTEM_USER_H
#include <string>

class User {
public:
    User();
    User(const std::string &phoneNumber, const std::string &password, const std::string &userName);
    virtual ~User();
    void set_phoneNumber(std::string phoneNumber);
    void set_password(std::string password);
    void set_userName(std::string userName);
    int get_id() const;
    std::string get_phoneNumber() const;
    std::string get_password() const;
    std::string get_userName() const;
    void showInformation() const;
    void set_id(int id);

private:
    int id;
    std::string userName;
    std::string phoneNumber;
    std::string password;
};

#endif //FOOD_ORDERING_SYSTEM_USER_H