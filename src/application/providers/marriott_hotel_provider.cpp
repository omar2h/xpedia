#include "marriott_hotel_provider.hpp"
#include "../../apis/expedia_hotels_api.hpp"
#include "../../model/factories/reservation_request_factory.hpp"
#include "../../model/hotel_room.hpp"

std::vector<std::unique_ptr<ItineraryItem>> MarriottHotelProvider::search_reservations() const
{
    auto reqPtr = getRequest();
    HotelRequest *req = dynamic_cast<HotelRequest *>(reqPtr.get());
    std::vector<std::unique_ptr<ItineraryItem>> rooms;
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
        rooms.push_back(hRoom.clone());
    }
    return rooms;
}

bool MarriottHotelProvider::reserve(Reservation *) const
{
    return MarriottHotelAPI::reserve();
}

std::string MarriottHotelProvider::getName() const
{
    return "Marriott";
}

ReservationProvider *MarriottHotelProvider::clone()
{
    return new MarriottHotelProvider(*this);
}
