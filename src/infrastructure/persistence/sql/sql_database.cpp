#include "sql_database.hpp"
#include "../../../domain/entities/customer.hpp"
#include "../../../domain/entities/flight_reservation.hpp"
#include "../../../domain/entities/hotel_reservation.hpp"
#include "../../../domain/entities/itinerary.hpp"
#include "../../../domain/entities/user.hpp"
#include "../../../exception.hpp"
#include "../../../infrastructure/serialization/reservation_serializer.hpp"
#include "../../../third_party/json.hpp"
#include "../../../util/id_generator.hpp"
#include "../../json_keys.hpp"

#include <sqlite3.h>
#include <sstream>

class SqlDatabase::Statement
{
    sqlite3_stmt* stmt_{};

  public:
    explicit Statement(sqlite3_stmt* stmt) : stmt_(stmt) {}

    Statement(const Statement&) = delete;
    Statement& operator=(const Statement&) = delete;

    Statement(Statement&& other) noexcept : stmt_(other.stmt_)
    {
        other.stmt_ = nullptr;
    }

    Statement& operator=(Statement&& other) noexcept
    {
        if (this != &other)
        {
            if (stmt_)
                sqlite3_finalize(stmt_);
            stmt_ = other.stmt_;
            other.stmt_ = nullptr;
        }
        return *this;
    }

    ~Statement()
    {
        if (stmt_)
            sqlite3_finalize(stmt_);
    }

    [[nodiscard]] sqlite3_stmt* get() const
    {
        return stmt_;
    }

    sqlite3_stmt* release()
    {
        sqlite3_stmt* stmt = stmt_;
        stmt_ = nullptr;
        return stmt;
    }
};

SqlDatabase::SqlDatabase(const std::string& path) : dbPath(path)
{
    if (sqlite3_open(path.c_str(), &db) != SQLITE_OK)
    {
        std::string msg = "Failed to open database: ";
        msg += sqlite3_errmsg(db);
        sqlite3_close(db);
        db = nullptr;
        throw PersistenceException(msg);
    }

    exec("PRAGMA journal_mode=WAL");
    exec("PRAGMA foreign_keys=ON");

    exec("CREATE TABLE IF NOT EXISTS users ("
         "  id TEXT PRIMARY KEY,"
         "  first_name TEXT NOT NULL,"
         "  last_name TEXT NOT NULL,"
         "  email TEXT NOT NULL UNIQUE,"
         "  phone TEXT NOT NULL,"
         "  password TEXT NOT NULL"
         ")");

    exec("CREATE TABLE IF NOT EXISTS customer_cards ("
         "  id INTEGER PRIMARY KEY AUTOINCREMENT,"
         "  customer_id TEXT NOT NULL REFERENCES users(id),"
         "  owner TEXT NOT NULL,"
         "  number TEXT NOT NULL,"
         "  expiry_date TEXT NOT NULL,"
         "  ccv TEXT NOT NULL"
         ")");

    exec("CREATE TABLE IF NOT EXISTS itineraries ("
         "  id TEXT PRIMARY KEY,"
         "  customer_id TEXT NOT NULL REFERENCES users(id),"
         "  cost REAL NOT NULL DEFAULT 0"
         ")");

    exec("CREATE TABLE IF NOT EXISTS reservations ("
         "  id INTEGER PRIMARY KEY AUTOINCREMENT,"
         "  itinerary_id TEXT NOT NULL REFERENCES itineraries(id),"
         "  json_data TEXT NOT NULL"
         ")");
}

SqlDatabase::~SqlDatabase()
{
    if (db)
        sqlite3_close(db);
}

void SqlDatabase::exec(const std::string& sql)
{
    char* err = nullptr;
    if (sqlite3_exec(db, sql.c_str(), nullptr, nullptr, &err) != SQLITE_OK)
    {
        std::string msg = "SQL error: ";
        msg += err;
        sqlite3_free(err);
        throw PersistenceException(msg);
    }
}

SqlDatabase::Statement SqlDatabase::prepare(const std::string& sql) const
{
    sqlite3_stmt* stmt{};
    if (sqlite3_prepare_v2(db, sql.c_str(), -1, &stmt, nullptr) != SQLITE_OK)
    {
        std::string msg = "SQL prepare error: ";
        msg += sqlite3_errmsg(db);
        throw PersistenceException(msg);
    }
    return Statement(stmt);
}

void SqlDatabase::bindText(sqlite3_stmt* stmt, int index, const std::string& value) const
{
    sqlite3_bind_text(stmt, index, value.c_str(), -1, SQLITE_TRANSIENT);
}

void SqlDatabase::bindInt(sqlite3_stmt* stmt, int index, int value) const
{
    sqlite3_bind_int(stmt, index, value);
}

void SqlDatabase::bindDouble(sqlite3_stmt* stmt, int index, double value) const
{
    sqlite3_bind_double(stmt, index, value);
}

std::string SqlDatabase::columnText(sqlite3_stmt* stmt, int index) const
{
    auto text = sqlite3_column_text(stmt, index);
    return text ? reinterpret_cast<const char*>(text) : "";
}

int SqlDatabase::columnInt(sqlite3_stmt* stmt, int index) const
{
    return sqlite3_column_int(stmt, index);
}

double SqlDatabase::columnDouble(sqlite3_stmt* stmt, int index) const
{
    return sqlite3_column_double(stmt, index);
}

bool SqlDatabase::columnIsNull(sqlite3_stmt* stmt, int index) const
{
    return sqlite3_column_type(stmt, index) == SQLITE_NULL;
}

void SqlDatabase::step(sqlite3_stmt* stmt) const
{
    Statement owned(stmt);
    int rc = sqlite3_step(owned.get());
    if (rc != SQLITE_DONE && rc != SQLITE_ROW)
    {
        std::string msg = "SQL step error: ";
        msg += sqlite3_errmsg(db);
        throw PersistenceException(msg);
    }
}

void SqlDatabase::createUser(User& user)
{
    if (user.getId().empty())
        user.setId(generateId());

    auto stmt = prepare("INSERT INTO users (id, first_name, last_name, email, phone, password) "
                        "VALUES (?, ?, ?, ?, ?, ?)");
    bindText(stmt.get(), 1, user.getId());
    bindText(stmt.get(), 2, user.getFirstName());
    bindText(stmt.get(), 3, user.getLastName());
    bindText(stmt.get(), 4, user.getEmail());
    bindText(stmt.get(), 5, user.getPhone());
    bindText(stmt.get(), 6, user.getPassword());

    int rc = sqlite3_step(stmt.get());
    if (rc != SQLITE_DONE)
    {
        if (rc == SQLITE_CONSTRAINT)
            throw ValidationException("Email already in use");
        std::string msg = "Failed to create user: ";
        msg += sqlite3_errmsg(db);
        throw PersistenceException(msg);
    }
}

std::optional<User> SqlDatabase::findUserByEmail(const std::string& email) const
{
    auto stmt = prepare("SELECT id, first_name, last_name, email, phone, password FROM users WHERE email = ?");
    bindText(stmt.get(), 1, email);
    int rc = sqlite3_step(stmt.get());
    if (rc == SQLITE_ROW)
    {
        return User(columnText(stmt.get(), 0), columnText(stmt.get(), 1), columnText(stmt.get(), 2),
                    columnText(stmt.get(), 3), columnText(stmt.get(), 4), columnText(stmt.get(), 5));
    }
    return std::nullopt;
}

std::optional<Customer> SqlDatabase::findCustomerById(const std::string& userId) const
{
    auto userStmt = prepare("SELECT id, first_name, last_name, email, phone, password FROM users WHERE id = ?");
    bindText(userStmt.get(), 1, userId);
    if (sqlite3_step(userStmt.get()) != SQLITE_ROW)
        return std::nullopt;

    User user(columnText(userStmt.get(), 0), columnText(userStmt.get(), 1), columnText(userStmt.get(), 2),
              columnText(userStmt.get(), 3), columnText(userStmt.get(), 4), columnText(userStmt.get(), 5));

    Customer customer(user);

    auto cardStmt = prepare("SELECT owner, number, expiry_date, ccv FROM customer_cards WHERE customer_id = ?");
    bindText(cardStmt.get(), 1, userId);
    while (sqlite3_step(cardStmt.get()) == SQLITE_ROW)
    {
        PaymentCard card;
        card.setOwner(columnText(cardStmt.get(), 0));
        card.setNumber(columnText(cardStmt.get(), 1));
        card.setExpiryDate(columnText(cardStmt.get(), 2));
        card.setCcv(columnText(cardStmt.get(), 3));
        customer.addCard(card);
    }

    auto itStmt = prepare("SELECT id FROM itineraries WHERE customer_id = ?");
    bindText(itStmt.get(), 1, userId);
    while (sqlite3_step(itStmt.get()) == SQLITE_ROW)
        customer.addItineraryId(columnText(itStmt.get(), 0));

    return customer;
}

void SqlDatabase::updateCustomer(const Customer& customer)
{
    auto delStmt = prepare("DELETE FROM customer_cards WHERE customer_id = ?");
    bindText(delStmt.get(), 1, customer.getId());
    step(delStmt.release());

    for (const auto& card : customer.getCards())
    {
        auto insStmt = prepare("INSERT INTO customer_cards (customer_id, owner, number, expiry_date, ccv) "
                               "VALUES (?, ?, ?, ?, ?)");
        bindText(insStmt.get(), 1, customer.getId());
        bindText(insStmt.get(), 2, card.getOwner());
        bindText(insStmt.get(), 3, card.getNumber());
        bindText(insStmt.get(), 4, card.getExpiryDate());
        bindText(insStmt.get(), 5, card.getCcv());
        step(insStmt.release());
    }
}

void SqlDatabase::saveItineraryForUser(const std::string& customerId, const Itinerary& itinerary)
{
    auto insIt = prepare("INSERT OR REPLACE INTO itineraries (id, customer_id, cost) VALUES (?, ?, ?)");
    bindText(insIt.get(), 1, itinerary.getId());
    bindText(insIt.get(), 2, customerId);
    bindDouble(insIt.get(), 3, itinerary.totalCost());
    step(insIt.release());

    auto delRes = prepare("DELETE FROM reservations WHERE itinerary_id = ?");
    bindText(delRes.get(), 1, itinerary.getId());
    step(delRes.release());

    ReservationSerializer serializer;
    for (const auto& res : itinerary.getReservations())
    {
        json j = serializer.toJson(*res);
        std::ostringstream oss;
        oss << j;

        auto insRes = prepare("INSERT INTO reservations (itinerary_id, json_data) VALUES (?, ?)");
        bindText(insRes.get(), 1, itinerary.getId());
        bindText(insRes.get(), 2, oss.str());
        step(insRes.release());
    }
}

bool SqlDatabase::customerExists(const std::string& userId) const
{
    auto stmt = prepare("SELECT COUNT(*) FROM users WHERE id = ?");
    bindText(stmt.get(), 1, userId);
    int rc = sqlite3_step(stmt.get());
    int count = (rc == SQLITE_ROW) ? columnInt(stmt.get(), 0) : 0;
    return count > 0;
}

std::vector<Itinerary> SqlDatabase::findItinerariesByUserId(const std::string& customerId) const
{
    std::vector<Itinerary> itineraries;

    auto itStmt = prepare("SELECT id, cost FROM itineraries WHERE customer_id = ?");
    bindText(itStmt.get(), 1, customerId);
    while (sqlite3_step(itStmt.get()) == SQLITE_ROW)
    {
        Itinerary itinerary;
        itinerary.setId(columnText(itStmt.get(), 0));
        itinerary.setCost(columnDouble(itStmt.get(), 1));

        auto resStmt = prepare("SELECT json_data FROM reservations WHERE itinerary_id = ?");
        bindText(resStmt.get(), 1, itinerary.getId());
        while (sqlite3_step(resStmt.get()) == SQLITE_ROW)
        {
            json j = json::parse(columnText(resStmt.get(), 0));
            itinerary.addItem(ReservationSerializer::fromJson(j));
        }

        itineraries.push_back(std::move(itinerary));
    }

    return itineraries;
}

// --- IUserRepository ---

void SqlDatabase::saveUser(const User& user)
{
    User copy = user;
    createUser(copy);
}

std::optional<User> SqlDatabase::findByUsername(const std::string& username) const
{
    return findUserByEmail(username);
}

// --- ICustomerRepository ---

std::optional<Customer> SqlDatabase::findById(const std::string& userId) const
{
    return findCustomerById(userId);
}

void SqlDatabase::update(const Customer& customer)
{
    updateCustomer(customer);
}

// --- IItineraryRepository ---

void SqlDatabase::save(const std::string& userId, const Itinerary& itinerary)
{
    saveItineraryForUser(userId, itinerary);
}

std::vector<Itinerary> SqlDatabase::findByUserId(const std::string& userId) const
{
    return findItinerariesByUserId(userId);
}
