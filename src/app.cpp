#include "app.hpp"
#include "application/frontend_interface.hpp"
#include "domain/entities/user.hpp"
#include "domain/entities/payment_card.hpp"
#include "domain/entities/itinerary.hpp"
#include "domain/entities/itinerary_item.hpp"
#include "domain/requests/reservation_request.hpp"
#include "application/use_cases/create_itinerary_use_case.hpp"
#include "application/use_cases/pay_itinerary_use_case.hpp"
#include "application/use_cases/list_itineraries_use_case.hpp"
#include "application/results/pay_itinerary_result.hpp"
#include "application/results/list_itineraries_result.hpp"
App::App(IFrontend &frontend,
         CreateItineraryUseCase &createItineraryUseCase,
         PayItineraryUseCase &payItineraryUseCase,
         ListItinerariesUseCase &listItinerariesUseCase)
    : m_frontend(frontend),
      m_createItineraryUseCase(createItineraryUseCase),
      m_payItineraryUseCase(payItineraryUseCase),
      m_listItinerariesUseCase(listItinerariesUseCase) {}

void App::run()
{
    User user;
    while (true)
    {
        while (true)
        {
            m_frontend.showMessage("\n");
            auto choice = static_cast<StartMenuChoice>(m_frontend.showStartMenu());

            switch (choice)
            {
            case StartMenuChoice::Login:
                user = m_frontend.login();
                m_frontend.displayWelcomeMessage(user.getFirstName(), user.getLastName());
                break;
            case StartMenuChoice::SignUp:
                m_frontend.signup();
                break;
            case StartMenuChoice::Exit:
                return;
            default:
                m_frontend.showError("Invalid choice");
                break;
            }

            if (choice == StartMenuChoice::Login)
                break;
        }

        bool loggedIn = true;
        while (loggedIn)
        {
            auto choice = static_cast<MainMenuChoice>(m_frontend.displayMainMenu());

            switch (choice)
            {
            case MainMenuChoice::ViewProfile:
                m_frontend.displayUserProfile(user);
                break;
            case MainMenuChoice::CreateItinerary:
                handleCreateItinerary(user);
                break;
            case MainMenuChoice::ListItineraries:
            {
                auto result = m_listItinerariesUseCase.execute(user);
                if (result.success)
                    m_frontend.displayItineraries(result.itineraries);
                else
                    m_frontend.showMessage(result.message);
                break;
            }
            case MainMenuChoice::Logout:
                loggedIn = false;
                break;
            default:
                m_frontend.showError("Invalid choice");
                break;
            }
        }
    }
}

void App::handleCreateItinerary(User &user)
{
    Itinerary itinerary = m_createItineraryUseCase.createItinerary();

    while (true)
    {
        auto choice = static_cast<CreateItineraryMenuChoice>(m_frontend.displayCreateItineraryMenu());

        switch (choice)
        {
        case CreateItineraryMenuChoice::AddFlight:
            addItemToItinerary(itinerary, RequestType::flight);
            break;
        case CreateItineraryMenuChoice::AddHotel:
            addItemToItinerary(itinerary, RequestType::hotel);
            break;
        case CreateItineraryMenuChoice::CheckOut:
        {
            if (itinerary.getReservations().empty())
            {
                m_frontend.showMessage("Cannot checkout: itinerary is empty");
                break;
            }
            m_frontend.displayItinerary(itinerary);
            handlePayment(user, itinerary);
            return;
        }
        case CreateItineraryMenuChoice::Cancel:
            return;
        default:
            m_frontend.showError("Invalid choice");
            break;
        }
    }
}

void App::addItemToItinerary(Itinerary &itinerary, RequestType type)
{
    auto request = m_createItineraryUseCase.makeRequest(type);
    if (!request)
    {
        m_frontend.showError("Unsupported reservation type");
        return;
    }

    m_frontend.readRequestData(*request, type);

    auto items = m_createItineraryUseCase.searchItems(type, *request);
    int sel = m_frontend.readReservationChoice(items);

    if (sel != -1 &&
        !m_createItineraryUseCase.addItemToItinerary(itinerary, type, std::move(request), *items[sel - 1]))
    {
        m_frontend.showError("Failed to add item to itinerary");
    }
}

bool App::handlePayment(User &user, const Itinerary &itinerary)
{
    auto cards = m_payItineraryUseCase.getCustomerCards(user);

    while (true)
    {
        int choice = m_frontend.displayPaymentOptions(cards);

        if (choice == -1)
            return false;

        if (choice == 0)
        {
            PaymentCard newCard = m_frontend.readCard();
            m_payItineraryUseCase.addCard(user, newCard);
            cards = m_payItineraryUseCase.getCustomerCards(user);
            continue;
        }

        PaymentCard selectedCard = cards[choice - 1];

        int serviceChoice = m_frontend.displayPaymentServices();
        if (serviceChoice == -1)
            return false;

        auto result = m_payItineraryUseCase.execute(user, itinerary, selectedCard, serviceChoice);

        if (result.status == PayItineraryResult::Confirmed)
        {
            m_frontend.showMessage(result.message);
            return true;
        }

        m_frontend.showError(result.message);
        return false;
    }
}
