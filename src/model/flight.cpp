#include "flight.h"

#include <sstream>

std::string Flight::toString() const
{
    std::ostringstream oss;
    oss << "Airline: " << airline << " Cost: " << totalCost << " Date: " << date << "\n";
    return oss.str();
}
