#include "console_frontend.hpp"
#include "../exception.hpp"
#include "output.hpp"
#include "input.hpp"
#include <sstream>
#include "../domain/requests/flight_request.hpp"
#include "../domain/requests/hotel_request.hpp"
#include "../domain/entities/itinerary_item.hpp"
#include "../domain/entities/itinerary.hpp"
#include "../domain/entities/flight.hpp"
#include "../domain/entities/hotel_room.hpp"
#include "../domain/entities/flight_reservation.hpp"
#include "../domain/entities/hotel_reservation.hpp"
#include "../domain/entities/payment_card.hpp"
#include "login_handler.hpp"
#include "signup_handler.hpp"

// Formatters (presentation layer - moved out of domain)
namespace
{
    std::string formatItineraryItem(const ItineraryItem &item)
    {
        if (const Flight *flight = dynamic_cast<const Flight *>(&item))
        {
            std::ostringstream oss;
            oss << "Airline: " << flight->getAirline() << ", Cost: " << flight->getTotalCost() << ", Date: " << flight->getDate();
            return oss.str();
        }
        else if (const HotelRoom *hotel = dynamic_cast<const HotelRoom *>(&item))
        {
            std::ostringstream oss;
            oss << "Hotel: " << hotel->getHotelName() << ", " << hotel->getRoomType() << " (" << hotel->getAvailableRooms() << " available), "
                << "Price/night: " << hotel->getPricePerNight() << ", From: " << hotel->getDateFrom() << " To: " << hotel->getDateTo();
            return oss.str();
        }
        return "Unknown item";
    }

    std::string formatReservationSummary(const Reservation &res)
    {
        if (const FlightReservation *flight = dynamic_cast<const FlightReservation *>(&res))
        {
            std::ostringstream oss;
            oss << "Flight: " << flight->getAirline() << ", From " << flight->getFrom() << " to " << flight->getTo()
                << " on " << flight->getDate() << ", Adults: " << flight->getAdults()
                << ", Children: " << flight->getChildren() << ", Total Cost: " << flight->totalCost() << "\n";
            return oss.str();
        }
        else if (const HotelReservation *hotel = dynamic_cast<const HotelReservation *>(&res))
        {
            std::ostringstream oss;
            oss << "Hotel: " << hotel->getHotelName() << ", " << hotel->getCity() << ", Room: " << hotel->getRoomType()
                << " (" << hotel->getRooms() << " rooms), From " << hotel->getFromDate() << " to " << hotel->getToDate()
                << ", Adults: " << hotel->getAdults() << ", Children: " << hotel->getChildren()
                << ", Total Cost: " << hotel->totalCost() << "\n";
            return oss.str();
        }
        return "Unknown reservation";
    }

    std::string formatItinerarySummary(const Itinerary &itinerary)
    {
        std::ostringstream oss;
        const auto &reservations = itinerary.getReservations();
        int count = static_cast<int>(reservations.size());
        oss << "Itinerary of " << count << " reservations\n";
        for (const auto &resPtr : reservations)
        {
            oss << formatReservationSummary(*resPtr);
        }
        return oss.str();
    }

    std::string formatPaymentCard(const PaymentCard &card)
    {
        std::ostringstream oss;
        oss << "Card: " << card.getNumber() << ", Owner: " << card.getOwner() << ", Expiry: " << card.getExpiryDate();
        return oss.str();
    }
} // namespace

ConsoleFrontend::ConsoleFrontend(LoginHandler &loginHandler,
                                 SignupHandler &signupHandler, IOutput &output, IInput &input)
    : m_loginHandler(loginHandler), m_signupHandler(signupHandler),
      m_output(output), m_input(input) {}

static void printMenu(IOutput &out, const std::vector<std::string> &menu)
{
    int size = (int)menu.size();
    out.writeLine("Menu:");
    for (int i = 0; i < size; i++)
    {
        out.write("\t" + std::to_string(i + 1) + ": " + menu[i] + "\n");
    }
    out.write("\nYour Choice: ");
}

static void printOptions(IOutput &out, const std::vector<std::string> &options)
{
    int count = (int)options.size();
    for (int i = 0; i < count; i++)
    {
        out.write(std::to_string(i + 1) + ": " + options[i] + "\n");
    }
}

int ConsoleFrontend::displayCreateItineraryMenu()
{
    std::vector<std::string> menu{
        "Add Flight",
        "Add Hotel",
        "Check Out",
        "Cancel"};

    int menuCount{(int)menu.size()};

    while (true)
    {
        printMenu(m_output, menu);

        try
        {
            return m_input.readInt(1, menuCount);
        }
        catch (const AppException &e)
        {
            showError(e.what());
        }
    }
}

void ConsoleFrontend::readRequestData(ReservationRequest &request, RequestType type)
{
    if (type == RequestType::flight)
    {
        readFlightRequestData(dynamic_cast<FlightRequest &>(request));
    }
    else if (type == RequestType::hotel)
    {
        readHotelRequestData(dynamic_cast<HotelRequest &>(request));
    }
}

int ConsoleFrontend::readReservationChoice(const std::vector<std::unique_ptr<ItineraryItem>> &items)
{
    std::vector<std::string> options{};

    for (const auto &item : items)
    {
        options.push_back(formatItineraryItem(*item));
    }

    int itemsCount{(int)items.size()};

    while (true)
    {
        printOptions(m_output, options);

        m_output.write("Enter choice(-1 to cancel): ");

        try
        {
            return m_input.readInt(1, itemsCount);
        }
        catch (const AppException &e)
        {
            showError(e.what());
        }
    }
}

int ConsoleFrontend::displayPaymentOptions(const std::vector<PaymentCard> &cards)
{
    std::vector<std::string> options;

    for (const auto &card : cards)
    {
        options.push_back(formatPaymentCard(card));
    }

    int cardsCount{(int)cards.size()};

    while (true)
    {
        printOptions(m_output, options);

        m_output.write("Enter choice(0 to add card, -1 to cancel): ");

        try
        {
            return m_input.readInt(0, cardsCount);
        }
        catch (const AppException &e)
        {
            showError(e.what());
        }
    }
}

PaymentCard ConsoleFrontend::readCard()
{
    m_output.write("Enter Card Number: ");
    std::string number = m_input.readString();
    m_output.write("Enter Card Owner: ");
    std::string owner = m_input.readString();
    m_output.write("Enter Card Expiry Date: ");
    std::string date = m_input.readString();
    m_output.write("Enter Card CCV: ");
    std::string ccv = m_input.readString();

    return {number, owner, date, ccv};
}

int ConsoleFrontend::displayPaymentServices()
{
    std::vector<std::string> services{
        "Paypal",
        "Stripe",
        "Square"};

    int count{(int)services.size()};

    while (true)
    {
        m_output.writeLine("Payment Services:");
        printOptions(m_output, services);
        m_output.write("Enter choice(-1 to cancel): ");

        try
        {
            return m_input.readInt(1, count);
        }
        catch (const AppException &e)
        {
            showError(e.what());
        }
    }
}

void ConsoleFrontend::displayItineraries(const std::vector<Itinerary> &itineraries)
{
    int count{(int)itineraries.size()};
    m_output.writeLine(std::to_string(count) + " itineraries");
    for (int i = 0; i < count; i++)
    {
        m_output.write(std::to_string(i + 1) + "- ");
        displayItinerary(itineraries[i]);
        m_output.write("\n");
    }
}

void ConsoleFrontend::displayItinerary(const Itinerary &itinerary)
{
    const auto &reservations = itinerary.getReservations();
    int count{(int)reservations.size()};
    m_output.writeLine("Itinerary of " + std::to_string(count) + " reservations");
    m_output.writeLine(formatItinerarySummary(itinerary));
}

void ConsoleFrontend::readFlightRequestData(FlightRequest &request)
{
    m_output.write("Enter From City: ");
    std::string from = m_input.readString();
    m_output.write("Enter To City: ");
    std::string to = m_input.readString();
    m_output.write("Enter Date: ");
    std::string date = m_input.readString();
    m_output.write("Enter Adults: ");
    int adults = m_input.readInt();
    m_output.write("Enter Children: ");
    int children = m_input.readInt();

    request.setFromCity(from);
    request.setToCity(to);
    request.setDate(date);
    request.setAdults(adults);
    request.setChildren(children);
}

void ConsoleFrontend::readHotelRequestData(HotelRequest &request)
{
    m_output.write("Enter City: ");
    std::string city = m_input.readString();
    m_output.write("Enter From Date: ");
    std::string fromDate = m_input.readString();
    m_output.write("Enter To Date: ");
    std::string toDate = m_input.readString();
    m_output.write("Enter Adults: ");
    int adults = m_input.readInt();
    m_output.write("Enter Children: ");
    int children = m_input.readInt();
    m_output.write("Enter Rooms: ");
    int rooms = m_input.readInt();

    request.setCity(city);
    request.setFromDate(fromDate);
    request.setToDate(toDate);
    request.setAdults(adults);
    request.setChildren(children);
    request.setRooms(rooms);
}

int ConsoleFrontend::showStartMenu()
{
    std::vector<std::string> startMenu{
        "Login",
        "SignUp",
        "Exit"};

    while (true)
    {
        printMenu(m_output, startMenu);

        try
        {
            return m_input.readInt(1, 3);
        }
        catch (const AppException &e)
        {
            showError(e.what());
        }
    }
}

void ConsoleFrontend::displayWelcomeMessage(const std::string &firstName, const std::string &lastName)
{
    m_output.writeLine("Welcome " + firstName + " " + lastName + "\n");
}

int ConsoleFrontend::displayMainMenu()
{
    std::vector<std::string> startMenu{
        "View Profile",
        "Create Itinerary",
        "List My Itineraries",
        "Logout"};

    int menuCount{(int)startMenu.size()};

    while (true)
    {
        printMenu(m_output, startMenu);

        try
        {
            return m_input.readInt(1, menuCount);
        }
        catch (const AppException &e)
        {
            showError(e.what());
        }
    }
}

void ConsoleFrontend::displayUserProfile(const User &user)
{
    m_output.write("\n");
    m_output.writeLine("Name: " + user.getFirstName() + " " + user.getLastName());
    m_output.writeLine("Email: " + user.getEmail());
    m_output.writeLine("Phone: " + user.getPhone());
    m_output.write("\n");
}

User ConsoleFrontend::login()
{
    while (true)
    {
        try
        {
            return m_loginHandler.login();
        }
        catch (const AppException &e)
        {
            showError(e.what());
        }
    }
}

void ConsoleFrontend::signup()
{
    while (true)
    {
        try
        {
            m_signupHandler.signup();
            return;
        }
        catch (const AppException &e)
        {
            showError(e.what());
        }
    }
}

void ConsoleFrontend::showMessage(const std::string &msg)
{
    m_output.writeLine(msg);
}

void ConsoleFrontend::showError(const std::string &msg)
{
    m_output.writeLine(msg);
}