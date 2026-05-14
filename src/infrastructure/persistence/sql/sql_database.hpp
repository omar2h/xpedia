#pragma once

#include "../../../application/database_interface.hpp"
#include <memory>

struct sqlite3;
struct sqlite3_stmt;

class SqlDatabase : public IDatabase
{
    sqlite3 *db{};
    std::string dbPath;

    void exec(const std::string &sql);
    sqlite3_stmt *prepare(const std::string &sql);
    void bindText(sqlite3_stmt *stmt, int index, const std::string &value);
    void bindInt(sqlite3_stmt *stmt, int index, int value);
    void bindDouble(sqlite3_stmt *stmt, int index, double value);
    std::string columnText(sqlite3_stmt *stmt, int index) const;
    int columnInt(sqlite3_stmt *stmt, int index) const;
    double columnDouble(sqlite3_stmt *stmt, int index) const;
    bool columnIsNull(sqlite3_stmt *stmt, int index) const;
    void step(sqlite3_stmt *stmt);

public:
    explicit SqlDatabase(const std::string &path = "travel.db");
    ~SqlDatabase() override;

    SqlDatabase(const SqlDatabase &) = delete;
    SqlDatabase &operator=(const SqlDatabase &) = delete;

    void saveUser(User &) override;
    [[nodiscard]] std::vector<User> getUsers(const std::string &) const override;
    [[nodiscard]] Customer getCustomer(const User &) override;
    void updateCustomerInfo(const Customer &) override;
    void saveItinerary(const std::string &, const Itinerary &) override;
    [[nodiscard]] bool checkUserIsCustomer(const User &) override;
    [[nodiscard]] std::vector<Itinerary> getCustomerItineraries(const std::string &) override;
};
