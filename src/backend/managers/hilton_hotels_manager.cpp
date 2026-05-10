#include "hilton_hotels_manager.hpp"
#include "../../apis/expedia_hotels_api.hpp"
#include "../../model/factories/reservation_request_factory.hpp"
#include "../../model/hotel_room.hpp"

std::vector<ItineraryItem *> HiltonHotelsManager::search_reservations() const
{
    HotelRequest *req = dynamic_cast<HotelRequest *>(getRequest());
    std::vector<ItineraryItem *> rooms;
    std::vector<HiltonRoom> hiltonRooms = HiltonHotelAPI::SearchRooms(req->getCity(), req->getFromDate(), req->getToDate(), req->getAdults(), req->getChildren(), req->getRooms());
    for (const auto &room : hiltonRooms)
    {
        HotelRoom hRoom{};
        hRoom.setDateFrom(room.date_from);
        hRoom.setDateTo(room.date_to);
        hRoom.setReqType(RequestType::hotel);
        hRoom.setType(ReservationType::hilton);
        hRoom.setAvailableRooms(room.available);
        hRoom.setPricePerNight(room.price_per_night);
        hRoom.setRoomType(room.room_type);
        hRoom.setHotelName(getName());
        rooms.push_back(hRoom.clone().release());
    }
    return rooms;
}

bool HiltonHotelsManager::reserve(Reservation *) const
{
    return HiltonHotelAPI::reserve();
}

std::string HiltonHotelsManager::getName() const
{
    return "Hilton";
}

ItineraryManager *HiltonHotelsManager::clone()
{
    return new HiltonHotelsManager(*this);
}
