#pragma once

class User;
class IFrontend;
class IDatabase;

class ListItinerariesUseCase
{
    IDatabase &m_database;

public:
    explicit ListItinerariesUseCase(IDatabase &database);

    void execute(const User &user, IFrontend &frontend);
};
