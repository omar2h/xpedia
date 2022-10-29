#include "customersManager.h"
#include "database.h"
#include <iostream>
Customer CustomersManager::getCustomer(const User &user) const
{
    Customer customer{user};
    std::vector<std::string> customersIds{};
    try
    {
        customersIds = Database::get_database()->read_json_attribute_from_file(CUSTOMERS_JSON, "id");
    }
    catch (int e)
    {
        throw e;
    }
    std::cout << "line 8\n";
    auto it = std::find(customersIds.begin(), customersIds.end(), customer.getId());
    if (it != customersIds.end())
    {
        json jsonCustomer;
        try
        {
            jsonCustomer = Database::get_database()->get_object_with_id(CUSTOMERS_JSON, customer.getId());
        }
        catch (int e)
        {
            throw e;
        }
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
        try
        {
            Database::get_database()->write_json_to_file(CUSTOMERS_JSON, obj, true);
        }
        catch (int e)
        {
            throw e;
        }
    }
    return customer;
}

json CustomersManager::convert_card_to_json(const PaymentCard &card) const
{
    json obj;
    obj["owner"] = card.getOwner();
    obj["number"] = card.getNumber();
    obj["expiry_date"] = card.getExpiryDate();
    obj["ccv"] = card.getCcv();
    return obj;
}

json CustomersManager::convert_customer_to_json(const Customer &customer) const
{
    UsersManager manager;
    json obj = manager.convert_user_to_json(customer);
    obj["cards"] = json::array();
    std::vector<PaymentCard> cards = customer.getCards();
    std::vector<std::string> itineraries = customer.getItinerariesIds();
    obj["itineraries"] = json::array();
    json cardObj;
    json itObj;
    for (const PaymentCard &card : cards)
    {
        cardObj = convert_card_to_json(card);
        obj["cards"].push_back(cardObj);
    }

    for (const std::string &id : itineraries)
    {
        itObj["id"] = id;
        obj["itineraries"].push_back(itObj);
    }
    return obj;
}

bool CustomersManager::check_if_customer_exists(const std::string &uId) const
{
    json obj;
    try
    {
        obj = Database::get_database()->get_object_with_id(CUSTOMERS_JSON, uId);
    }
    catch (int e)
    {
        throw e;
    }
    if (obj.empty())
        return false;
    return true;
}

void CustomersManager::update_customer(const Customer &customer) const
{
    json obj = convert_customer_to_json(customer);
    try
    {
        Database::get_database()->delete_object_with_id(CUSTOMERS_JSON, customer.getId());
    }
    catch (int e)
    {
        throw e;
    }
    try
    {
        Database::get_database()->write_json_to_file(CUSTOMERS_JSON, obj, true);
    }
    catch (int e)
    {
        throw e;
    }
}