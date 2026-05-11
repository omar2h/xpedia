#pragma once

class User;
class Itinerary;
class IFrontend;
class IDatabase;
class PaymentProcessor;

class PayItineraryUseCase
{
    IDatabase &m_database;
    PaymentProcessor &m_paymentProcessor;

public:
    PayItineraryUseCase(IDatabase &database, PaymentProcessor &paymentProcessor);

    void execute(const Itinerary &currItinerary, const User &user, IFrontend &frontend);
};
