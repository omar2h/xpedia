#ifndef __USER_H__
#define __USER_H__

#include <string>
class User
{
    std::string id{};
    std::string firstName{};
    std::string lastName{};
    std::string email{};
    std::string phone{};
    std::string password{};

public:
    User();
    User(const std::string &, const std::string &, const std::string &, const std::string &,
         const std::string &);

    User(const std::string &, const std::string &, const std::string &, const std::string &,
         const std::string &, const std::string &);

    std::string getId() const { return id; }
    void setId(const std::string &id_) { id = id_; }

    std::string getFirstName() const { return firstName; }
    void setFirstName(const std::string &firstName_) { firstName = firstName_; }

    std::string getLastName() const { return lastName; }
    void setLastName(const std::string &lastName_) { lastName = lastName_; }

    std::string getEmail() const { return email; }
    void setEmail(const std::string &email_) { email = email_; }

    std::string getPhone() const { return phone; }
    void setPhone(const std::string &phone_) { phone = phone_; }

    std::string getPassword() const { return password; }
    void setPassword(const std::string &password_) { password = password_; }
};
#endif // __USER_H__