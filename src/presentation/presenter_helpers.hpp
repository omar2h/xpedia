#pragma once

#include "view/view_interface.hpp"
#include "input.hpp"
#include "../exception.hpp"

template<typename Func>
auto retryOnError(IView& view, Func fn) -> decltype(fn())
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

inline int readChoice(IView& view, IInput& input, const std::string& prompt, int low, int high, bool allowCancel = false)
{
    return retryOnError(view, [&] {
        view.showPrompt(prompt);
        return input.readInt(low, high, allowCancel);
    });
}
