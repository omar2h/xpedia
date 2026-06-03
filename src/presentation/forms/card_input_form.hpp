#pragma once

#include "dto/card_input.hpp"

class IView;
class IInput;

class CardInputForm
{
  public:
    static CardInput collect(IView& view, IInput& input);
};
