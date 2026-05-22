#include "app.hpp"

#include "composition/auth/auth_module.hpp"
#include "composition/flight/flight_module.hpp"

#include "application/use_cases/list_itineraries_use_case.hpp"

#include "infrastructure/persistence/sql/sql_database.hpp"

#include "presentation/console_frontend.hpp"
#include "presentation/input.hpp"
#include "presentation/output.hpp"

#include <exception>
#include <iostream>

int main()
{
    try
    {
        SqlDatabase database;

        ConsoleOutput output;
        ConsoleInput input;
        ConsoleFrontend view{output};

        auto authModule = createAuthModule(view, input, database);
        auto flightModule = createFlightModule(view, input, database);
        ListItinerariesUseCase listItinerariesUseCase{database, database};

        App app{
            view,
            input,
            *authModule.presenter,
            *flightModule.presenter,
            listItinerariesUseCase};

        app.run();
    }
    catch (const std::exception &e)
    {
        std::cerr << "Fatal error: " << e.what() << "\n";
        return 1;
    }
}
