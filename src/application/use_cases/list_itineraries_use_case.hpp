#pragma once

#include "../results/list_itineraries_result.hpp"

class User;
class IDatabase;

class ListItinerariesUseCase
{
    IDatabase &m_database;

public:
    explicit ListItinerariesUseCase(IDatabase &database);

    [[nodiscard]] ListItinerariesResult execute(const User &user);
};
