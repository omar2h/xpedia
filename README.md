# Travel Booking System

Travel Booking System is a modular C++ console application for creating travel itineraries that combine flight and hotel reservations. The project is structured around layered architecture, SQLite persistence, provider integrations, and automated tests so it can be discussed as an engineering project rather than only a UI demo.

## Demo

Video walkthrough: https://youtu.be/4njfqKla5yE

## Features

- User registration and login flow
- Create itineraries and add flight or hotel reservations
- Persist users, cards, itineraries, and reservations in SQLite
- Payment processing through strategy-based payment providers
- Reservation serialization and database integration tests
- Composition-root style dependency wiring for the application modules

## Tech Stack

- C++17
- CMake
- SQLite3
- GoogleTest
- CPR
- nlohmann/json

## Architecture

The codebase is organized into focused layers under `src/`:

- `domain/` core entities such as `User`, `Customer`, `Itinerary`, and reservations
- `application/` use cases, services, repository interfaces, and provider abstractions
- `infrastructure/` persistence, serialization, API clients, payment strategies, and factories
- `presentation/` console views, presenters, mappers, and input/output handling
- `composition/` application wiring and module assembly
- `tests/` unit and integration coverage

This separation keeps business rules independent from the console UI and allows persistence and external integrations to be swapped more easily.

## Project Layout

- `src/main.cpp` application entry point
- `src/app.cpp` top-level app flow and menu orchestration
- `src/infrastructure/persistence/sql/sql_database.cpp` SQLite-backed persistence implementation
- `src/application/services/payment_service.cpp` payment orchestration logic
- `src/tests/test_integration.cpp` SQLite and serialization integration tests

## Build

From the repository root:

```bash
cmake -S . -B build
cmake --build build
```

## Run

```bash
./build/src/Debug/travel_app
```

On single-config generators such as Ninja or Makefiles, the executable is typically:

```bash
./build/src/travel_app
```

## Test

```bash
ctest --test-dir build --output-on-failure
```

## Environment Setup

Copy `.env.example` to `.env` and provide the keys you want to enable:

- `DUFFEL_API_KEY` for flight search integration
- `LITEAPI_KEY` for hotel search integration

The app can still be explored without fully configured external services, but live provider-backed search requires valid API credentials.

## Testing Scope

Current automated coverage includes:

- reservation factory behavior
- reservation serialization round-trips
- reservation service behavior
- payment processor behavior
- SQLite integration for users, cards, itineraries, and reservations

## Design Decisions

- SQLite was chosen to keep local setup simple while still demonstrating real persistence
- Repository interfaces isolate the application layer from infrastructure details
- Payment processing uses strategy-based provider selection
- Composition modules keep wiring out of the domain and use-case code

## Current Limitations

- The primary interface is a console application rather than a web or desktop UI
- External provider integrations depend on API keys and available third-party services
- Reservation confirmation infrastructure is simpler than a production-grade booking workflow
- There is no CI pipeline yet in the repository

## What I Would Improve Next

- Add CI for configure, build, and test validation
- Introduce stronger transaction boundaries around payment and reservation confirmation
- Expand provider abstractions for reservation confirmation flows
- Add richer validation and more end-to-end business rule tests
