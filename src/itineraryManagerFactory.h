#ifndef __ITINERARYMANAGERFACTORY_H__
#define __ITINERARYMANAGERFACTORY_H__

enum class ReservationType;
class ItineraryManager;
class ItineraryManagerFactory
{
public:
    virtual ItineraryManager *getManager(ReservationType type);

    virtual ~ItineraryManagerFactory() = default;
};
#endif // __ITINERARYMANAGERFACTORY_H__