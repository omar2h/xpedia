#pragma once

#include "../../application/use_cases/search/search_hotels_use_case.hpp"

class IView;
class IInput;
class User;

class HotelSearchPresenter
{
    IView &m_view;
    IInput &m_input;
    SearchHotelsUseCase &m_useCase;

public:
    HotelSearchPresenter(IView &view, IInput &input, SearchHotelsUseCase &useCase);

    void run(User &user);
};
