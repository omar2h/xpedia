#include "hotelRoom.h"
#include <sstream>
std::string HotelRoom::toString() const
{
    std::stringstream oss;
    oss << "Hotel: " << hotelName << " " << roomType << "(" << availableRooms << ") "
        << "Price per night: " << pricePerNight << " From: " << dateFrom << " To: " << dateTo;
    return oss.str();
}

ItineraryItem *HotelRoom::Clone()
{
    return new HotelRoom(*this);
}
