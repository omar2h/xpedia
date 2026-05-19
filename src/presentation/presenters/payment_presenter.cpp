#include "payment_presenter.hpp"
#include "../view/view_interface.hpp"
#include "../input.hpp"
#include "../presenter_helpers.hpp"
#include "../forms/card_input_form.hpp"
#include "../mappers/payment_card_mapper.hpp"
#include "../../domain/entities/user.hpp"
#include "../../domain/entities/itinerary.hpp"
#include "../../domain/entities/payment_card.hpp"
#include "../../application/use_cases/pay_itinerary_use_case.hpp"
#include "../../application/results/pay_itinerary_result.hpp"
#include "../../exception.hpp"

PaymentPresenter::PaymentPresenter(IView& view, IInput& input, PayItineraryUseCase& useCase)
    : m_view(view), m_input(input), m_payItineraryUseCase(useCase) {}

bool PaymentPresenter::run(User& user, const Itinerary& itinerary)
{
    auto cards = m_payItineraryUseCase.getCustomerCards(user);

    while (true)
    {
        std::vector<PaymentCardViewModel> viewModels;
        for (const auto& card : cards)
            viewModels.push_back(toPaymentCardViewModel(card));

        m_view.showPaymentOptions(viewModels);

        int choice = readChoice(m_view, m_input, "Enter choice(0 to add card, -1 to cancel): ", 0, static_cast<int>(cards.size()), true);

        if (choice == -1) return false;

        if (choice == 0)
        {
            auto input = CardInputForm::collect(m_view, m_input);
            PaymentCard newCard{input.number, input.owner, input.expiryDate, input.ccv};
            m_payItineraryUseCase.addCard(user, newCard);
            cards = m_payItineraryUseCase.getCustomerCards(user);
            continue;
        }

        PaymentCard selectedCard = cards[choice - 1];

        m_view.showPaymentServices();
        int serviceChoice = readChoice(m_view, m_input, "Enter choice(-1 to cancel): ", 1, 3, true);

        if (serviceChoice == -1) return false;

        auto result = m_payItineraryUseCase.execute(user, itinerary, selectedCard, serviceChoice);

        if (result.status == PayItineraryResult::Confirmed)
        {
            m_view.showMessage(result.message);
            return true;
        }

        m_view.showError(result.message);
        return false;
    }
}
