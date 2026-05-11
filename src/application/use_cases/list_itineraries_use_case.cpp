#include "list_itineraries_use_case.hpp"
#include "../database_interface.hpp"
#include "../frontend_interface.hpp"
#include "../../model/customer.hpp"
#include "../../model/user.hpp"
#include "../../model/itinerary.hpp"
#include <vector>

ListItinerariesUseCase::ListItinerariesUseCase(IDatabase &database)
    : m_database(database) {}

void ListItinerariesUseCase::execute(const User &user, IFrontend &frontend)
{
    bool isCustomer = m_database.checkUserIsCustomer(user);

    if (!isCustomer)
    {
        frontend.showMessage("User has no itineraries");
        return;
    }

    Customer customer = m_database.getCustomer(user);

    if (customer.getItinerariesIds().empty())
    {
        frontend.showMessage("User has no itineraries");
        return;
    }

    std::vector<Itinerary> customerItineraries = m_database.getCustomerItineraries(customer.getId());

    frontend.displayItineraries(customerItineraries);
}
