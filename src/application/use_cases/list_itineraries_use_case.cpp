#include "list_itineraries_use_case.hpp"
#include "../database_interface.hpp"
#include "../../model/customer.hpp"
#include "../../model/user.hpp"
#include "../../model/itinerary.hpp"
#include <vector>

ListItinerariesUseCase::ListItinerariesUseCase(IDatabase &database)
    : m_database(database) {}

ListItinerariesResult ListItinerariesUseCase::execute(const User &user)
{
    bool isCustomer = m_database.checkUserIsCustomer(user);

    if (!isCustomer)
        return {false, "User has no itineraries", {}};

    Customer customer = m_database.getCustomer(user);

    if (customer.getItinerariesIds().empty())
        return {false, "User has no itineraries", {}};

    std::vector<Itinerary> customerItineraries = m_database.getCustomerItineraries(customer.getId());

    return {true, "", std::move(customerItineraries)};
}
