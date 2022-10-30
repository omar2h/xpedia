#ifndef __HILTONHOTELSMANAGER_H__
#define __HILTONHOTELSMANAGER_H__
#include "hotelsManager.h"

class HiltonHotelsManager : public HotelsManager
{
public:
    std::vector<ItineraryItem *> search_reservations() const override;

    bool reserve(Reservation *) const override;

    std::string getName() const override;

    ItineraryManager *Clone() override;
};
#endif // __HILTONHOTELSMANAGER_H__