#pragma once

#include <optional>
#include "../domain/entities/user.hpp"

enum class AppState { StartMenu, MainMenu, Exit };
enum class StartMenuChoice { Login = 1, SignUp = 2, Exit = 3 };
enum class MainMenuChoice { SearchFlights = 1, ViewItineraries = 2, ViewProfile = 3, Logout = 4 };
enum class CreateItineraryMenuChoice { AddFlight = 1, AddHotel = 2, CheckOut = 3, Cancel = 4 };

struct AuthResult {
    AppState state;
    std::optional<User> user;
};
