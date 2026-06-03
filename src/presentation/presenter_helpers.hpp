#pragma once

#include <string>

#include "../exception.hpp"
#include "input.hpp"
#include "view/view_interface.hpp"

template <typename Func> auto retryOnError(IView& view, Func fn) -> decltype(fn())
{
    while (true)
    {
        try
        {
            return fn();
        }
        catch (const AppException& e)
        {
            view.showError(e.what());
        }
    }
}

inline int readChoice(IView& view, IInput& input, const std::string& prompt, int min, int max, bool allowCancel = false)
{
    while (true)
    {
        if (!prompt.empty())
        {
            view.showPrompt(prompt);
        }

        int choice = input.readInt();

        if (allowCancel && choice == -1)
        {
            return choice;
        }

        if (choice >= min && choice <= max)
        {
            return choice;
        }

        view.showError("Invalid choice");
    }
}
