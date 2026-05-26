#pragma once

#include "../../../application/repositories/i_user_repository.hpp"
#include "../../../application/repositories/i_customer_repository.hpp"
#include "../../../application/repositories/i_itinerary_repository.hpp"
#include <memory>

struct sqlite3;
struct sqlite3_stmt;

class SqlDatabase : public IUserRepository,
                    public ICustomerRepository,
                    public IItineraryRepository
{
    sqlite3 *db{};
    std::string dbPath;

    class Statement;

    void exec(const std::string &sql);
    [[nodiscard]] Statement prepare(const std::string &sql) const;
    void bindText(sqlite3_stmt *stmt, int index, const std::string &value) const;
    void bindInt(sqlite3_stmt *stmt, int index, int value) const;
    void bindDouble(sqlite3_stmt *stmt, int index, double value) const;
    [[nodiscard]] std::string columnText(sqlite3_stmt *stmt, int index) const;
    [[nodiscard]] int columnInt(sqlite3_stmt *stmt, int index) const;
    [[nodiscard]] double columnDouble(sqlite3_stmt *stmt, int index) const;
    [[nodiscard]] bool columnIsNull(sqlite3_stmt *stmt, int index) const;
    void step(sqlite3_stmt *stmt) const;

public:
    explicit SqlDatabase(const std::string &path = "travel.db");
    ~SqlDatabase() override;

    SqlDatabase(const SqlDatabase &) = delete;
    SqlDatabase &operator=(const SqlDatabase &) = delete;

    // --- Public API (used directly by tests) ---
    void createUser(User &);
    [[nodiscard]] std::optional<User> findUserByEmail(const std::string &email) const;
    [[nodiscard]] std::optional<Customer> findCustomerById(const std::string &userId) const;
    [[nodiscard]] bool customerExists(const std::string &userId) const;
    void updateCustomer(const Customer &);
    void saveItineraryForUser(const std::string &userId, const Itinerary &);
    [[nodiscard]] std::vector<Itinerary> findItinerariesByUserId(const std::string &userId) const;

    // --- IUserRepository ---
    void saveUser(const User &) override;
    [[nodiscard]] std::optional<User> findByUsername(const std::string &username) const override;

    // --- ICustomerRepository ---
    [[nodiscard]] std::optional<Customer> findById(const std::string &userId) const override;
    void update(const Customer &) override;

    // --- IItineraryRepository ---
    void save(const std::string &userId, const Itinerary &) override;
    [[nodiscard]] std::vector<Itinerary> findByUserId(const std::string &userId) const override;
};