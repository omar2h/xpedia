#include "card_input_form.hpp"
#include "../view/view_interface.hpp"
#include "../input.hpp"

CardInput CardInputForm::collect(IView &view, IInput &input)
{
    CardInput result;
    view.showPrompt("Enter Card Number: ");
    result.number = input.readLine();
    view.showPrompt("Enter Card Owner: ");
    result.owner = input.readLine();
    view.showPrompt("Enter Card Expiry Date: ");
    result.expiryDate = input.readLine();
    view.showPrompt("Enter Card CCV: ");
    result.ccv = input.readLine();
    return result;
}
