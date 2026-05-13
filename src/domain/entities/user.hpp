#pragma once

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

    [[nodiscard]] const std::string &getId() const { return id; }
    void setId(const std::string &id_) { id = id_; }

    [[nodiscard]] const std::string &getFirstName() const { return firstName; }
    void setFirstName(const std::string &firstName_) { firstName = firstName_; }

    [[nodiscard]] const std::string &getLastName() const { return lastName; }
    void setLastName(const std::string &lastName_) { lastName = lastName_; }

    [[nodiscard]] const std::string &getEmail() const { return email; }
    void setEmail(const std::string &email_) { email = email_; }

    [[nodiscard]] const std::string &getPhone() const { return phone; }
    void setPhone(const std::string &phone_) { phone = phone_; }

    [[nodiscard]] const std::string &getPassword() const { return password; }
    void setPassword(const std::string &password_) { password = password_; }
};
