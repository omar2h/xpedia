#include "marriottHotelsManager.h"
#include "../APIs/expedia_hotels_api.h"
#include "../db/factories/reservationRequestFactory.h"
#include "../model/hotelRoom.h"

std::vector<ItineraryItem *> MarriottHotelsManager::search_reservations() const
{
    HotelRequest *req = dynamic_cast<HotelRequest *>(getRequest());
    std::vector<ItineraryItem *> rooms;
    std::vector<MarriottFoundRoom> marriottRooms = MarriottHotelAPI::FindRooms(req->getFromDate(), req->getToDate(), req->getCity(), req->getRooms(), req->getAdults(), req->getChildren());
    for (const auto &room : marriottRooms)
    {
        HotelRoom hRoom{};
        hRoom.setDateFrom(room.date_from);
        hRoom.setDateTo(room.date_to);
        hRoom.setReqType(RequestType::hotel);
        hRoom.setType(ReservationType::marriott);
        hRoom.setAvailableRooms(room.available);
        hRoom.setPricePerNight(room.price_per_night);
        hRoom.setRoomType(room.room_type);
        hRoom.setHotelName(getName());
        rooms.push_back(hRoom.Clone());
    }
    return rooms;
}

bool MarriottHotelsManager::reserve(Reservation *) const
{
    return MarriottHotelAPI::reserve();
}

std::string MarriottHotelsManager::getName() const
{
    return "Marriott";
}

ItineraryManager *MarriottHotelsManager::Clone()
{
    return new MarriottHotelsManager(*this);
}
