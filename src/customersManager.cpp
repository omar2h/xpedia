#include "customersManager.h"
#include "database.h"
#include <iostream>
Customer CustomersManager::getCustomer(const User &user)
{
    Customer customer{user};
    std::vector<std::string> customersIds = Database::get_database()->read_json_attribute_from_file(CUSTOMERS_JSON, "id");
    auto it = std::find(customersIds.begin(), customersIds.end(), customer.getId());
    if (it != customersIds.end())
    {
        json jsonCustomer = Database::get_database()->get_object_with_id(CUSTOMERS_JSON, customer.getId());
        nlohmann::json cardsArr = jsonCustomer["cards"];

        for (const json &card_ : cardsArr)
        {
            PaymentCard card;
            card.setOwner(card_.value("owner", "not found"));
            card.setNumber(card_.value("number", "not found"));
            card.setExpiryDate(card_.value("expiry_date", "not found"));
            card.setCcv(card_.value("ccv", "not found"));
            customer.addCard(card);
        }

        nlohmann::json itArr = jsonCustomer["itineraries"];
        for (const json &itineraryId : itArr)
        {
            customer.addItineraryId(itineraryId.value("id", "not found"));
        }
    }
    else
    {
        UsersManager manager;
        json obj = manager.convert_user_to_json(user);
        obj["cards"] = json::array();
        obj["itineraries"] = json::array();
        Database::get_database()->write_json_to_file(CUSTOMERS_JSON, obj, true);
    }
    return customer;
}
