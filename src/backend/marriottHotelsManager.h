#ifndef __MARRIOTTHOTELSMANAGER_H__
#define __MARRIOTTHOTELSMANAGER_H__
#include "hotelsManager.h"

class MarriottHotelsManager : public HotelsManager
{
public:
    std::vector<ItineraryItem *> search_reservations() const override;

    bool reserve(Reservation *) const override;

    std::string getName() const override;

    ItineraryManager *Clone() override;
};
#endif // __MARRIOTTHOTELSMANAGER_H__