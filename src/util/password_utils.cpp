#include "password_utils.hpp"
#include <algorithm>
#include <iomanip>
#include <sstream>

namespace PasswordUtils
{

// Simple hash function for demonstration purposes
// NOTE: This is NOT suitable for production use!
// In a real application, use a proper password hashing library like bcrypt or Argon2
std::string hashPassword(const std::string& password)
{
    // Simple hash: sum of character values with some mixing
    uint32_t hash = 0;
    for (char c : password)
    {
        hash = (hash * 31) + static_cast<uint8_t>(c);
    }

    // Convert to hex string
    std::ostringstream oss;
    oss << std::hex << std::setfill('0') << std::setw(8) << hash;
    return oss.str();
}

// Verify a password against its hash
// NOTE: This is NOT suitable for production use!
bool verifyPassword(const std::string& password, const std::string& hashedPassword)
{
    std::string hashedInput = hashPassword(password);
    return hashedInput == hashedPassword;
}

} // namespace PasswordUtils