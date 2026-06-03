#include "list_itineraries_use_case.hpp"
#include "../../domain/entities/customer.hpp"
#include "../../domain/entities/itinerary.hpp"
#include "../../domain/entities/user.hpp"
#include "../repositories/i_customer_repository.hpp"
#include "../repositories/i_itinerary_repository.hpp"
#include <vector>

ListItinerariesUseCase::ListItinerariesUseCase(ICustomerRepository& customerRepo, IItineraryRepository& itineraryRepo)
    : m_customerRepo(customerRepo), m_itineraryRepo(itineraryRepo)
{
}

ListItinerariesResult ListItinerariesUseCase::execute(const User& user)
{
    auto customer = m_customerRepo.findById(user.getId());

    if (!customer || customer->getItinerariesIds().empty())
        return {false, "User has no itineraries", {}};

    std::vector<Itinerary> customerItineraries = m_itineraryRepo.findByUserId(customer->getId());

    return {true, "", std::move(customerItineraries)};
}
