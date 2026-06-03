#pragma once

#include "../results/list_itineraries_result.hpp"

class User;
class ICustomerRepository;
class IItineraryRepository;

class ListItinerariesUseCase
{
    ICustomerRepository& m_customerRepo;
    IItineraryRepository& m_itineraryRepo;

  public:
    ListItinerariesUseCase(ICustomerRepository& customerRepo, IItineraryRepository& itineraryRepo);

    [[nodiscard]] ListItinerariesResult execute(const User& user);
};
