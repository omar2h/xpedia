#ifndef __HOTELSMANAGER_H__
#define __HOTELSMANAGER_H__

#include "../model/hotelRequest.h"
#include "../model/hotelReservation.h"
#include "itineraryManager.h"
#include <vector>
class HotelsManager : public ItineraryManager
{
public:
    std::vector<ItineraryItem *> search_reservations() const override = 0;

    bool reserve(Reservation *) const override = 0;

    std::string getName() const override = 0;

    ItineraryManager *Clone() override = 0;

    ~HotelsManager() override = default;
};
#endif // __HOTELSMANAGER_H__