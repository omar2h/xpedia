#include "customer_repository.hpp"
#include "../infrastructure/json_keys.hpp"
#include "storage/file_storage.hpp"
#include "user_repository.hpp"

CustomerRepository::CustomerRepository(FileStorage &storage) : m_storage(storage) {}

Customer CustomerRepository::getCustomer(const User &user) const
{
    Customer customer{user};

    std::vector<std::string> customersIds =
        m_storage.readJsonAttributeFromFile("customers.json", JsonKeys::id);

    auto it = std::find(customersIds.begin(), customersIds.end(), customer.getId());

    if (it != customersIds.end())
    {
        json jsonCustomer =
            m_storage.getObjectWithId("customers.json", customer.getId());

        nlohmann::json cardsArr = jsonCustomer[JsonKeys::cards];

        for (const json &card_ : cardsArr)
        {
            PaymentCard card;

            card.setOwner(card_.value(JsonKeys::owner, "not found"));
            card.setNumber(card_.value(JsonKeys::number, "not found"));
            card.setExpiryDate(card_.value(JsonKeys::expiryDate, "not found"));
            card.setCcv(card_.value(JsonKeys::ccv, "not found"));

            customer.addCard(card);
        }

        nlohmann::json itArr = jsonCustomer[JsonKeys::itineraries];

        for (const json &itineraryId : itArr)
        {
            customer.addItineraryId(itineraryId.value(JsonKeys::id, "not found"));
        }
    }
    else
    {
        json obj = convertUserToJson(user);

        obj[JsonKeys::cards] = json::array();
        obj[JsonKeys::itineraries] = json::array();

        m_storage.writeJsonToFile("customers.json", obj, true);
    }

    return customer;
}

json CustomerRepository::convertCardToJson(const PaymentCard &card) const
{
    json obj;

    obj[JsonKeys::owner] = card.getOwner();
    obj[JsonKeys::number] = card.getNumber();
    obj[JsonKeys::expiryDate] = card.getExpiryDate();
    obj[JsonKeys::ccv] = card.getCcv();

    return obj;
}

json CustomerRepository::convertCustomerToJson(const Customer &customer) const
{
    json obj = convertUserToJson(customer);

    obj[JsonKeys::cards] = json::array();
    obj[JsonKeys::itineraries] = json::array();

    std::vector<PaymentCard> cards = customer.getCards();
    std::vector<std::string> itineraries = customer.getItinerariesIds();

    json cardObj;
    json itObj;

    for (const PaymentCard &card : cards)
    {
        cardObj = convertCardToJson(card);
        obj[JsonKeys::cards].push_back(cardObj);
    }

    for (const std::string &id : itineraries)
    {
        itObj[JsonKeys::id] = id;
        obj[JsonKeys::itineraries].push_back(itObj);
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