#include "sql_database.hpp"
#include "../../../domain/entities/user.hpp"
#include "../../../domain/entities/customer.hpp"
#include "../../../domain/entities/itinerary.hpp"
#include "../../../domain/entities/flight_reservation.hpp"
#include "../../../domain/entities/hotel_reservation.hpp"
#include "../../../infrastructure/serialization/reservation_serializer.hpp"
#include "../../../exception.hpp"
#include "../../../third_party/json.hpp"
#include "../../json_keys.hpp"

#include <sqlite3.h>
#include <sstream>

SqlDatabase::SqlDatabase(const std::string &path)
    : dbPath(path)
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

    exec(
        "CREATE TABLE IF NOT EXISTS users ("
        "  id TEXT PRIMARY KEY,"
        "  first_name TEXT NOT NULL,"
        "  last_name TEXT NOT NULL,"
        "  email TEXT NOT NULL UNIQUE,"
        "  phone TEXT NOT NULL,"
        "  password TEXT NOT NULL"
        ")");

    exec(
        "CREATE TABLE IF NOT EXISTS customer_cards ("
        "  id INTEGER PRIMARY KEY AUTOINCREMENT,"
        "  customer_id TEXT NOT NULL REFERENCES users(id),"
        "  owner TEXT NOT NULL,"
        "  number TEXT NOT NULL,"
        "  expiry_date TEXT NOT NULL,"
        "  ccv TEXT NOT NULL"
        ")");

    exec(
        "CREATE TABLE IF NOT EXISTS itineraries ("
        "  id TEXT PRIMARY KEY,"
        "  customer_id TEXT NOT NULL REFERENCES users(id),"
        "  cost REAL NOT NULL DEFAULT 0"
        ")");

    exec(
        "CREATE TABLE IF NOT EXISTS reservations ("
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

void SqlDatabase::exec(const std::string &sql)
{
    char *err = nullptr;
    if (sqlite3_exec(db, sql.c_str(), nullptr, nullptr, &err) != SQLITE_OK)
    {
        std::string msg = "SQL error: ";
        msg += err;
        sqlite3_free(err);
        throw PersistenceException(msg);
    }
}

sqlite3_stmt *SqlDatabase::prepare(const std::string &sql)
{
    sqlite3_stmt *stmt;
    if (sqlite3_prepare_v2(db, sql.c_str(), -1, &stmt, nullptr) != SQLITE_OK)
    {
        std::string msg = "SQL prepare error: ";
        msg += sqlite3_errmsg(db);
        throw PersistenceException(msg);
    }
    return stmt;
}

void SqlDatabase::bindText(sqlite3_stmt *stmt, int index, const std::string &value)
{
    sqlite3_bind_text(stmt, index, value.c_str(), -1, SQLITE_TRANSIENT);
}

void SqlDatabase::bindInt(sqlite3_stmt *stmt, int index, int value)
{
    sqlite3_bind_int(stmt, index, value);
}

void SqlDatabase::bindDouble(sqlite3_stmt *stmt, int index, double value)
{
    sqlite3_bind_double(stmt, index, value);
}

std::string SqlDatabase::columnText(sqlite3_stmt *stmt, int index) const
{
    auto text = sqlite3_column_text(stmt, index);
    return text ? reinterpret_cast<const char *>(text) : "";
}

int SqlDatabase::columnInt(sqlite3_stmt *stmt, int index) const
{
    return sqlite3_column_int(stmt, index);
}

double SqlDatabase::columnDouble(sqlite3_stmt *stmt, int index) const
{
    return sqlite3_column_double(stmt, index);
}

bool SqlDatabase::columnIsNull(sqlite3_stmt *stmt, int index) const
{
    return sqlite3_column_type(stmt, index) == SQLITE_NULL;
}

void SqlDatabase::step(sqlite3_stmt *stmt)
{
    int rc = sqlite3_step(stmt);
    sqlite3_finalize(stmt);
    if (rc != SQLITE_DONE && rc != SQLITE_ROW)
    {
        std::string msg = "SQL step error: ";
        msg += sqlite3_errmsg(db);
        throw PersistenceException(msg);
    }
}

void SqlDatabase::createUser(User &user)
{
    if (user.getId().empty())
    {
        auto stmt = prepare("SELECT COALESCE(MAX(CAST(id AS INTEGER)), 0) + 1 FROM users");
        int rc = sqlite3_step(stmt);
        if (rc == SQLITE_ROW)
            user.setId(std::to_string(columnInt(stmt, 0)));
        sqlite3_finalize(stmt);
    }

    auto stmt = prepare(
        "INSERT INTO users (id, first_name, last_name, email, phone, password) "
        "VALUES (?, ?, ?, ?, ?, ?)");
    bindText(stmt, 1, user.getId());
    bindText(stmt, 2, user.getFirstName());
    bindText(stmt, 3, user.getLastName());
    bindText(stmt, 4, user.getEmail());
    bindText(stmt, 5, user.getPhone());
    bindText(stmt, 6, user.getPassword());

    int rc = sqlite3_step(stmt);
    sqlite3_finalize(stmt);
    if (rc != SQLITE_DONE)
    {
        if (rc == SQLITE_CONSTRAINT)
            throw ValidationException("Email already in use");
        std::string msg = "Failed to create user: ";
        msg += sqlite3_errmsg(db);
        throw PersistenceException(msg);
    }
}

std::optional<User> SqlDatabase::findUserByEmail(const std::string &email) const
{
    auto stmt = const_cast<SqlDatabase *>(this)->prepare(
        "SELECT id, first_name, last_name, email, phone, password FROM users WHERE email = ?");
    const_cast<SqlDatabase *>(this)->bindText(stmt, 1, email);
    int rc = sqlite3_step(stmt);
    if (rc == SQLITE_ROW)
    {
        User user(
            columnText(stmt, 0),
            columnText(stmt, 1),
            columnText(stmt, 2),
            columnText(stmt, 3),
            columnText(stmt, 4),
            columnText(stmt, 5));
        sqlite3_finalize(stmt);
        return user;
    }
    sqlite3_finalize(stmt);
    return std::nullopt;
}

std::optional<Customer> SqlDatabase::findCustomerById(const std::string &userId) const
{
    auto userStmt = const_cast<SqlDatabase *>(this)->prepare(
        "SELECT id, first_name, last_name, email, phone, password FROM users WHERE id = ?");
    const_cast<SqlDatabase *>(this)->bindText(userStmt, 1, userId);
    if (sqlite3_step(userStmt) != SQLITE_ROW)
    {
        sqlite3_finalize(userStmt);
        return std::nullopt;
    }

    User user(
        columnText(userStmt, 0),
        columnText(userStmt, 1),
        columnText(userStmt, 2),
        columnText(userStmt, 3),
        columnText(userStmt, 4),
        columnText(userStmt, 5));
    sqlite3_finalize(userStmt);

    Customer customer(user);

    auto cardStmt = const_cast<SqlDatabase *>(this)->prepare(
        "SELECT owner, number, expiry_date, ccv FROM customer_cards WHERE customer_id = ?");
    const_cast<SqlDatabase *>(this)->bindText(cardStmt, 1, userId);
    while (sqlite3_step(cardStmt) == SQLITE_ROW)
    {
        PaymentCard card;
        card.setOwner(columnText(cardStmt, 0));
        card.setNumber(columnText(cardStmt, 1));
        card.setExpiryDate(columnText(cardStmt, 2));
        card.setCcv(columnText(cardStmt, 3));
        customer.addCard(card);
    }
    sqlite3_finalize(cardStmt);

    auto itStmt = const_cast<SqlDatabase *>(this)->prepare(
        "SELECT id FROM itineraries WHERE customer_id = ?");
    const_cast<SqlDatabase *>(this)->bindText(itStmt, 1, userId);
    while (sqlite3_step(itStmt) == SQLITE_ROW)
        customer.addItineraryId(columnText(itStmt, 0));
    sqlite3_finalize(itStmt);

    return customer;
}

void SqlDatabase::updateCustomer(const Customer &customer)
{
    auto delStmt = prepare("DELETE FROM customer_cards WHERE customer_id = ?");
    bindText(delStmt, 1, customer.getId());
    step(delStmt);

    for (const auto &card : customer.getCards())
    {
        auto insStmt = prepare(
            "INSERT INTO customer_cards (customer_id, owner, number, expiry_date, ccv) "
            "VALUES (?, ?, ?, ?, ?)");
        bindText(insStmt, 1, customer.getId());
        bindText(insStmt, 2, card.getOwner());
        bindText(insStmt, 3, card.getNumber());
        bindText(insStmt, 4, card.getExpiryDate());
        bindText(insStmt, 5, card.getCcv());
        step(insStmt);
    }
}

void SqlDatabase::saveItineraryForUser(const std::string &customerId, const Itinerary &itinerary)
{
    auto insIt = prepare(
        "INSERT OR REPLACE INTO itineraries (id, customer_id, cost) VALUES (?, ?, ?)");
    bindText(insIt, 1, itinerary.getId());
    bindText(insIt, 2, customerId);
    bindDouble(insIt, 3, itinerary.totalCost());
    step(insIt);

    auto delRes = prepare("DELETE FROM reservations WHERE itinerary_id = ?");
    bindText(delRes, 1, itinerary.getId());
    step(delRes);

    ReservationSerializer serializer;
    for (const auto &res : itinerary.getReservations())
    {
        json j = serializer.toJson(*res);
        std::ostringstream oss;
        oss << j;

        auto insRes = prepare(
            "INSERT INTO reservations (itinerary_id, json_data) VALUES (?, ?)");
        bindText(insRes, 1, itinerary.getId());
        bindText(insRes, 2, oss.str());
        step(insRes);
    }
}

bool SqlDatabase::customerExists(const std::string &userId) const
{
    auto stmt = const_cast<SqlDatabase *>(this)->prepare(
        "SELECT COUNT(*) FROM users WHERE id = ?");
    const_cast<SqlDatabase *>(this)->bindText(stmt, 1, userId);
    int rc = sqlite3_step(stmt);
    int count = (rc == SQLITE_ROW) ? columnInt(stmt, 0) : 0;
    sqlite3_finalize(stmt);
    return count > 0;
}

std::vector<Itinerary> SqlDatabase::findItinerariesByUserId(const std::string &customerId) const
{
    std::vector<Itinerary> itineraries;

    auto itStmt = const_cast<SqlDatabase *>(this)->prepare("SELECT id, cost FROM itineraries WHERE customer_id = ?");
    const_cast<SqlDatabase *>(this)->bindText(itStmt, 1, customerId);
    while (sqlite3_step(itStmt) == SQLITE_ROW)
    {
        Itinerary itinerary;
        itinerary.setId(columnText(itStmt, 0));
        itinerary.setCost(columnDouble(itStmt, 1));

        auto resStmt = const_cast<SqlDatabase *>(this)->prepare("SELECT json_data FROM reservations WHERE itinerary_id = ?");
        const_cast<SqlDatabase *>(this)->bindText(resStmt, 1, itinerary.getId());
        while (sqlite3_step(resStmt) == SQLITE_ROW)
        {
            json j = json::parse(columnText(resStmt, 0));
            itinerary.addItem(ReservationSerializer::fromJson(j));
        }
        sqlite3_finalize(resStmt);

        itineraries.push_back(std::move(itinerary));
    }
    sqlite3_finalize(itStmt);

    return itineraries;
}

// --- IUserRepository ---

void SqlDatabase::saveUser(const User &user)
{
    User copy = user;
    createUser(copy);
}

std::optional<User> SqlDatabase::findByUsername(const std::string &username) const
{
    return findUserByEmail(username);
}

// --- ICustomerRepository ---

std::optional<Customer> SqlDatabase::findById(const std::string &userId) const
{
    return findCustomerById(userId);
}

void SqlDatabase::update(const Customer &customer)
{
    updateCustomer(customer);
}

// --- IItineraryRepository ---

void SqlDatabase::save(const std::string &userId, const Itinerary &itinerary)
{
    saveItineraryForUser(userId, itinerary);
}

std::vector<Itinerary> SqlDatabase::findByUserId(const std::string &userId) const
{
    return findItinerariesByUserId(userId);
}
