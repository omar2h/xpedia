#include "customer_repository.hpp"
#include "storage/file_storage.hpp"
#include "user_repository.hpp"
#include <iostream>

CustomerRepository::CustomerRepository(FileStorage &storage) : m_storage(storage) {}

Customer CustomerRepository::getCustomer(const User &user) const
{
    Customer customer{user};

    std::vector<std::string> customersIds =
        m_storage.readJsonAttributeFromFile("customers.json", "id");

    std::cout << "line 8\n";

    auto it = std::find(customersIds.begin(), customersIds.end(), customer.getId());

    if (it != customersIds.end())
    {
        json jsonCustomer =
            m_storage.getObjectWithId("customers.json", customer.getId());

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
        json obj = UserRepository::convertUserToJson(user);

        obj["cards"] = json::array();
        obj["itineraries"] = json::array();

        m_storage.writeJsonToFile("customers.json", obj, true);
    }

    return customer;
}

json CustomerRepository::convertCardToJson(const PaymentCard &card) const
{
    json obj;

    obj["owner"] = card.getOwner();
    obj["number"] = card.getNumber();
    obj["expiry_date"] = card.getExpiryDate();
    obj["ccv"] = card.getCcv();

    return obj;
}

json CustomerRepository::convertCustomerToJson(const Customer &customer) const
{
    json obj = UserRepository::convertUserToJson(customer);

    obj["cards"] = json::array();
    obj["itineraries"] = json::array();

    std::vector<PaymentCard> cards = customer.getCards();
    std::vector<std::string> itineraries = customer.getItinerariesIds();

    json cardObj;
    json itObj;

    for (const PaymentCard &card : cards)
    {
        cardObj = convertCardToJson(card);
        obj["cards"].push_back(cardObj);
    }

    for (const std::string &id : itineraries)
    {
        itObj["id"] = id;
        obj["itineraries"].push_back(itObj);
    }

    return obj;
}

bool CustomerRepository::customerExists(const std::string &uId) const
{
    json obj =
        m_storage.getObjectWithId("customers.json", uId);

    return !obj.empty();
}

void CustomerRepository::updateCustomer(const Customer &customer) const
{
    json obj = convertCustomerToJson(customer);

    m_storage.deleteObjectWithId("customers.json", customer.getId());

    m_storage.writeJsonToFile("customers.json", obj, true);
}