#include "console_frontend.hpp"
#include "output.hpp"

ConsoleFrontend::ConsoleFrontend(IOutput &output) : m_output(output) {}

static void printMenu(IOutput &out, const std::vector<std::string> &menu)
{
    int size = static_cast<int>(menu.size());
    out.writeLine("Menu:");
    for (int i = 0; i < size; i++)
    {
        out.write("\t" + std::to_string(i + 1) + ": " + menu[i] + "\n");
    }
    out.write("\n");
}

static void printOptions(IOutput &out, const std::vector<std::string> &options)
{
    int count = static_cast<int>(options.size());
    for (int i = 0; i < count; i++)
    {
        out.write(std::to_string(i + 1) + ": " + options[i] + "\n");
    }
}

void ConsoleFrontend::showMessage(const std::string &msg) { m_output.writeLine(msg); }
void ConsoleFrontend::showError(const std::string &msg) { m_output.writeLine(msg); }
void ConsoleFrontend::showPrompt(const std::string &prompt) { m_output.write(prompt); }

void ConsoleFrontend::displayWelcomeMessage(const std::string &firstName, const std::string &lastName)
{
    m_output.writeLine("Welcome " + firstName + " " + lastName + "\n");
}

void ConsoleFrontend::displayUserProfile(const UserProfileViewModel &vm)
{
    m_output.write("\n");
    m_output.writeLine("Name: " + vm.fullName);
    m_output.writeLine("Email: " + vm.email);
    m_output.writeLine("Phone: " + vm.phone);
    m_output.write("\n");
}

void ConsoleFrontend::displayItinerary(const ItineraryViewModel &vm)
{
    m_output.writeLine(vm.summary);
}

void ConsoleFrontend::displayItineraries(const std::vector<ItineraryViewModel> &vms)
{
    int count = static_cast<int>(vms.size());
    m_output.writeLine(std::to_string(count) + " itineraries");
    for (int i = 0; i < count; i++)
    {
        m_output.write(std::to_string(i + 1) + "- ");
        displayItinerary(vms[i]);
        m_output.write("\n");
    }
}

void ConsoleFrontend::showStartMenu()
{
    std::vector<std::string> menu{"Login", "SignUp", "Exit"};
    printMenu(m_output, menu);
}

void ConsoleFrontend::showMainMenu()
{
    std::vector<std::string> menu{"Search Flights", "View Itineraries", "View Profile", "Logout"};
    printMenu(m_output, menu);
}

void ConsoleFrontend::showCreateItineraryMenu()
{
    std::vector<std::string> menu{"Add Flight", "Add Hotel", "Check Out", "Cancel"};
    printMenu(m_output, menu);
}

void ConsoleFrontend::showPaymentOptions(const std::vector<PaymentCardViewModel> &cards)
{
    if (cards.empty())
        m_output.writeLine("No saved cards");
    for (const auto &card : cards)
        m_output.writeLine(card.displayText);
    m_output.writeLine("0: Add card");
}

void ConsoleFrontend::showPaymentServices()
{
    m_output.writeLine("Payment Services:");
    std::vector<std::string> services{"Paypal", "Stripe", "Square"};
    printOptions(m_output, services);
}

void ConsoleFrontend::showSearchResults(const std::vector<SearchResultViewModel> &results)
{
    int count = static_cast<int>(results.size());
    for (int i = 0; i < count; i++)
        m_output.writeLine(std::to_string(i + 1) + ": " + results[i].displayText);
}

void ConsoleFrontend::displayFlightOffers(
    const FlightOfferListView &view)
{
    if (view.offers.empty())
    {
        m_output.writeLine("No flight offers found.");
        return;
    }

    m_output.writeLine("");
    m_output.writeLine("==================================================");
    m_output.writeLine("Flight Offers");
    m_output.writeLine("==================================================");

    for (const auto &offer : view.offers)
    {
        m_output.writeLine("");

        std::string title =
            "[" + std::to_string(offer.number) + "] " +
            offer.airline;

        if (!offer.flightNumber.empty())
            title += " " + offer.flightNumber;

        m_output.writeLine(title);

        m_output.writeLine(offer.route);

        m_output.writeLine("");

        if (!offer.departureTime.empty())
            m_output.writeLine(
                "Departure : " + offer.departureTime);

        if (!offer.arrivalTime.empty())
            m_output.writeLine(
                "Arrival   : " + offer.arrivalTime);

        if (!offer.duration.empty())
            m_output.writeLine(
                "Duration  : " + offer.duration);

        if (!offer.stops.empty())
            m_output.writeLine(
                "Stops     : " + offer.stops);

        if (!offer.aircraft.empty())
            m_output.writeLine(
                "Aircraft  : " + offer.aircraft);

        if (!offer.cabin.empty())
            m_output.writeLine(
                "Cabin     : " + offer.cabin);

        if (!offer.baggage.empty())
            m_output.writeLine(
                "Baggage   : " + offer.baggage);

        m_output.writeLine("");

        m_output.writeLine(
            "Price     : " + offer.price);

        m_output.writeLine(
            "--------------------------------------------------");
    }

    m_output.writeLine("");
}
