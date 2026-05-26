#include "itinerary_presenter.hpp"
#include "payment_presenter.hpp"
#include "../view/view_interface.hpp"
#include "../input.hpp"
#include "../presenter_helpers.hpp"
#include "../mappers/itinerary_mapper.hpp"
#include "../itinerary_item_flows/itinerary_item_flow.hpp"
#include "../../domain/entities/itinerary.hpp"
#include "application/use_cases/create_empty_itinerary_use_case.hpp"

ItineraryPresenter::ItineraryPresenter(
    IView& view,
    IInput& input,
    CreateEmptyItineraryUseCase& createItineraryUseCase,
    std::vector<std::unique_ptr<ItineraryItemFlow>> itemFlows,
    PaymentPresenter& paymentPresenter)
    : m_view(view), m_input(input),
      m_createItineraryUseCase(createItineraryUseCase),
      m_itemFlows(std::move(itemFlows)),
      m_paymentPresenter(paymentPresenter) {}

void ItineraryPresenter::run(User& user)
{
    Itinerary itinerary = m_createItineraryUseCase.execute();

    while (true)
    {
        m_view.showMessage("Menu:");
        int flowCount = static_cast<int>(m_itemFlows.size());
        for (int i = 0; i < flowCount; i++)
        {
            m_view.showMessage("\t" + std::to_string(i + 1) + ": " + m_itemFlows[i]->label());
        }
        int checkoutChoice = flowCount + 1;
        int cancelChoice = flowCount + 2;
        m_view.showMessage("\t" + std::to_string(checkoutChoice) + ": Check Out");
        m_view.showMessage("\t" + std::to_string(cancelChoice) + ": Cancel");
        m_view.showPrompt("");

        int choice = readChoice(m_view, m_input, "", 1, cancelChoice);

        if (choice >= 1 && choice <= flowCount)
        {
            m_itemFlows[choice - 1]->execute(itinerary);
        }
        else if (choice == checkoutChoice)
        {
            if (itinerary.getReservations().empty())
            {
                m_view.showMessage("Cannot checkout: itinerary is empty");
                continue;
            }
            m_view.displayItinerary(toItineraryViewModel(itinerary));
            bool confirmed = m_paymentPresenter.run(user, itinerary);
            if (confirmed)
                return;
            m_view.showMessage("Checkout cancelled or failed");
        }
        else if (choice == cancelChoice)
        {
            return;
        }
    }
}
