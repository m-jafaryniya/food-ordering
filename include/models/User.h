
#ifndef FOOD_ORDERING_SYSTEM_USER_H
#define FOOD_ORDERING_SYSTEM_USER_H
#include <string>

class User {
public:
    User();
    User(const std::string &phoneNumber, const std::string &password, const std::string &userName);
    virtual ~User();
    void setPhoneNumber(std::string phoneNumber);
    void setPassword(std::string password);
    void setUserName(std::string userName);
    int getId() const;
    std::string getPhoneNumber() const;
    std::string getPassword() const;
    std::string getUserName() const;
    void showInformation() const;
    void setId(int id);

private:
    int id;
    std::string userName;
    std::string phoneNumber;
    std::string password;
};

#endif //FOOD_ORDERING_SYSTEM_USER_H