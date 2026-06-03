#pragma once

#include <cstdint>
#include <stdexcept>
#include <string>
#include <vector>

namespace PasswordUtils
{

// Simple hash function for demonstration purposes
// NOTE: This is NOT suitable for production use!
// In a real application, use a proper password hashing library like bcrypt or Argon2
[[nodiscard]] std::string hashPassword(const std::string& password);

// Verify a password against its hash
// NOTE: This is NOT suitable for production use!
bool verifyPassword(const std::string& password, const std::string& hashedPassword);

} // namespace PasswordUtils