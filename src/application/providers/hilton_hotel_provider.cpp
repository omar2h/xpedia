#include "hilton_hotel_provider.hpp"
#include "../../apis/expedia_hotels_api.hpp"
#include "../../model/factories/reservation_request_factory.hpp"
#include "../../model/hotel_room.hpp"

std::vector<std::unique_ptr<ItineraryItem>> HiltonHotelProvider::search_reservations() const
{
    HotelRequest *req = dynamic_cast<HotelRequest *>(getRequest());
    std::vector<std::unique_ptr<ItineraryItem>> rooms;
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
        rooms.push_back(hRoom.clone());
    }
    return rooms;
}

bool HiltonHotelProvider::reserve(Reservation *) const
{
    return HiltonHotelAPI::reserve();
}

std::string HiltonHotelProvider::getName() const
{
    return "Hilton";
}

ReservationProvider *HiltonHotelProvider::clone()
{
    return new HiltonHotelProvider(*this);
}
