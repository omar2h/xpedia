#include "customer_repository.hpp"
#include "storage/file_storage.hpp"
#include "user_repository.hpp"
#include <iostream>

CustomerRepository::CustomerRepository(FileStorage &storage) : m_storage(storage) {}

Customer CustomerRepository::getCustomer(const User &user) const
{
    Customer customer{user};

    std::vector<std::string> customersIds =
        m_storage.read_json_attribute_from_file("customers.json", "id");

    std::cout << "line 8\n";

    auto it = std::find(customersIds.begin(), customersIds.end(), customer.getId());

    if (it != customersIds.end())
    {
        json jsonCustomer =
            m_storage.get_object_with_id("customers.json", customer.getId());

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
        json obj = UserRepository::convert_user_to_json(user);

        obj["cards"] = json::array();
        obj["itineraries"] = json::array();

        m_storage.write_json_to_file("customers.json", obj, true);
    }

    return customer;
}

json CustomerRepository::convert_card_to_json(const PaymentCard &card) const
{
    json obj;

    obj["owner"] = card.getOwner();
    obj["number"] = card.getNumber();
    obj["expiry_date"] = card.getExpiryDate();
    obj["ccv"] = card.getCcv();

    return obj;
}

json CustomerRepository::convert_customer_to_json(const Customer &customer) const
{
    json obj = UserRepository::convert_user_to_json(customer);

    obj["cards"] = json::array();
    obj["itineraries"] = json::array();

    std::vector<PaymentCard> cards = customer.getCards();
    std::vector<std::string> itineraries = customer.getItinerariesIds();

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

bool CustomerRepository::check_if_customer_exists(const std::string &uId) const
{
    json obj =
        m_storage.get_object_with_id("customers.json", uId);

    return !obj.empty();
}

void CustomerRepository::update_customer(const Customer &customer) const
{
    json obj = convert_customer_to_json(customer);

    m_storage.delete_object_with_id("customers.json", customer.getId());

    m_storage.write_json_to_file("customers.json", obj, true);
}