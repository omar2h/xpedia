#pragma once

class IView;
class IInput;
class User;
class IHotelSearchService;
class IItineraryRepository;

class HotelSearchPresenter
{
    IView &m_view;
    IInput &m_input;
    IHotelSearchService &m_hotelSearchService;
    IItineraryRepository &m_itineraryRepo;

public:
    HotelSearchPresenter(IView &view,
                         IInput &input,
                         IHotelSearchService &hotelSearchService,
                         IItineraryRepository &itineraryRepo);

    void run(User &user);
};