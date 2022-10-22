#include "backEnd.h"
#include "database.h"
#include "flightRequest.h"
#include "frontEnd.h"
#include "flightsManagerFactory.h"
#include "reservationRequestFactory.h"

std::vector<FlightsManager *> BackEnd::flightsManagers = FlightsManagerFactory::getManagers();

void BackEnd::save_user_in_db(User &user)
{
    try
    {
        Database::get_database()->save_user(user);
    }
    catch (int e)
    {
        throw e;
    }
}

User BackEnd::user_login(const std::string &email, const std::string &password)
{
    std::vector<User> users{};
    users = Database::get_database()->get_users(USERS_JSON);

    for (const auto &usr : users)
    {
        if (usr.getEmail() == email && usr.getPassword() == password)
            return usr;
    }
    throw 5;
}

// std::vector<Flight> BackEnd::get_available_flights(const FlightRequest &request)
// {
//     std::vector<Flight> flights;

//     for (FlightsManager *manager : flightsManagers)
//     {
//         manager->setFlightRequest(request);
//         std::vector<Flight> airlineFlights = manager->search_flights();

//         flights.insert(flights.end(), airlineFlights.begin(), airlineFlights.end());
//     }
//     return flights;
// }

void BackEnd::add_flight()
{
    ReservationRequest *request = ReservationRequestFactory::getRequest(RequestType::flight);
    FrontEnd::read_request_data(request, RequestType::flight);
    // std::vector<Flight> flights = get_available_flights(request);
    // int choice = FrontEnd::read_flight_choice(flights);
}

void BackEnd::create_itinerary(int choice)
{
    if (choice == 1)
    {
        add_flight();
    }
    else if (choice == 2)
    {
        // add hotel
        ;
    }
    else if (choice == 3)
    {
        // Checkout
    }
    else if (choice == 4)
    {
        // cancel
        return;
    }
}
