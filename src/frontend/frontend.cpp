// #include "frontend.hpp"
// #include "printer.hpp"
// #include "input_handler.hpp"
// #include "../error.hpp"
// #include "request_data_reader.hpp"
// #include "flight_request_data_reader.hpp"
// #include "hotel_request_data_reader.hpp"
// #include "../model/reservation.hpp"
// #include <iostream>

// RequestDataReader *Frontend::reader{};

// int Frontend::show_start_menu()
// {
//     std::vector<std::string> startMenu{"Login", "SignUp", "Exit"};
//     Printer::print_menu(startMenu);
//     int choice{};
//     try
//     {
//         choice = InputHandler::get_choice(1, 3);
//     }
//     catch (int e)
//     {
//         Error::display_error(e);
//         return show_start_menu();
//     }
//     return choice;
// }

// void Frontend::display_welcome_message(const std::string &firstName, const std::string &lastName)
// {
//     std::cout << "Welcome " << firstName << " " << lastName << "\n\n";
// }

// int Frontend::display_main_menu()
// {
//     std::vector<std::string> startMenu{"View Profile", "Create Itinerary", "List My Itineraries", "Logout"};
//     Printer::print_menu(startMenu);
//     int menuCount{(int)startMenu.size()};
//     int choice{};
//     try
//     {
//         choice = InputHandler::get_choice(1, menuCount);
//     }
//     catch (int e)
//     {
//         Error::display_error(e);
//         return display_main_menu();
//     }
//     return choice;
// }

// void Frontend::display_user_profile(const User &user)
// {
//     std::cout << "\n";
//     std::cout << "Name: " << user.getFirstName() << " " << user.getLastName() << "\n";
//     std::cout << "Email: " << user.getEmail() << "\n";
//     std::cout << "Phone: " << user.getPhone() << "\n";
//     std::cout << "\n";
// }

// int Frontend::display_create_itinerary_menu()
// {
//     std::vector<std::string> menu{"Add Flight", "Add Hotel", "Check Out", "Cancel"};
//     Printer::print_menu(menu);
//     int menuCount{(int)menu.size()};
//     int choice{};
//     try
//     {
//         choice = InputHandler::get_choice(1, menuCount);
//     }
//     catch (int e)
//     {
//         Error::display_error(e);
//         return display_create_itinerary_menu();
//     }
//     return choice;
// }

// int Frontend::display_payment_options(const std::vector<PaymentCard> &cards)
// {
//     std::vector<std::string> options;
//     for (const auto &card : cards)
//         options.push_back(card.toString());
//     Printer::print_options(options);
//     int cardsCount{(int)cards.size()};

//     std::cout << "Enter choice(0 to add card, -1 to cancel): ";
//     int choice{};
//     try
//     {
//         choice = InputHandler::get_choice(0, cardsCount);
//     }
//     catch (int e)
//     {
//         Error::display_error(e);
//         return display_payment_options(cards);
//     }
//     return choice;
// }

// void Frontend::read_flight_request_data(FlightRequest &request)
// {
//     std::string from{};
//     std::string to{};
//     std::string date{};
//     int adults{};
//     int children{};

//     std::cout << "Enter From City: ";
//     std::cin >> from;
//     std::cout << "Enter To City: ";
//     std::cin >> to;
//     std::cout << "Enter Date: ";
//     std::cin >> date;
//     std::cout << "Enter Adults: ";
//     std::cin >> adults;
//     std::cout << "Enter Children: ";
//     std::cin >> children;

//     request.setFromCity(from);
//     request.setToCity(to);
//     request.setDate(date);
//     request.setAdults(adults);
//     request.setChildren(children);
// }

// void Frontend::read_hotel_request_data(HotelRequest &request)
// {
//     std::string city{};
//     std::string fromDate{};
//     std::string toDate{};
//     int adults{};
//     int children{};
//     int rooms{};

//     std::cout << "Enter City: ";
//     std::cin >> city;
//     std::cout << "Enter From Date: ";
//     std::cin >> fromDate;
//     std::cout << "Enter To Date: ";
//     std::cin >> toDate;
//     std::cout << "Enter Adults: ";
//     std::cin >> adults;
//     std::cout << "Enter Children: ";
//     std::cin >> children;
//     std::cout << "Enter Rooms: ";
//     std::cin >> rooms;

//     request.setCity(city);
//     request.setFromDate(fromDate);
//     request.setToDate(toDate);
//     request.setAdults(adults);
//     request.setChildren(children);
//     request.setRooms(rooms);
// }

// void Frontend::read_request_data(ReservationRequest &request, RequestType type)
// {
//     if (type == RequestType::flight)
//     {
//         read_flight_request_data(dynamic_cast<FlightRequest &>(request));
//     }
//     else if (type == RequestType::hotel)
//     {
//         read_hotel_request_data(dynamic_cast<HotelRequest &>(request));
//     }
// }

// int Frontend::read_reservation_choice(const std::vector<std::unique_ptr<ItineraryItem>> &items)
// {
//     std::vector<std::string> options{};
//     for (const auto &item : items)
//     {
//         options.push_back(item->toString());
//     }
//     Printer::print_options(options);
//     int itemsCount{(int)items.size()};
//     std::cout << "Enter choice(-1 to cancel): ";
//     int choice{};
//     try
//     {
//         choice = InputHandler::get_choice(1, itemsCount);
//     }
//     catch (int e)
//     {
//         Error::display_error(e);
//         return read_reservation_choice(items);
//     }
//     return choice;
// }

// PaymentCard Frontend::read_card()
// {
//     std::string number;
//     std::string owner;
//     std::string date;
//     std::string ccv;
//     std::cout << "Enter Card Number: ";
//     std::cin >> number;
//     std::cout << "Enter Card Owner: ";
//     std::cin >> owner;
//     std::cout << "Enter Catd Expiry Date: ";
//     std::cin >> date;
//     std::cout << "Enter Card CCV: ";
//     std::cin >> ccv;

//     return {number, owner, date, ccv};
// }

// void Frontend::display_itinerary(const Itinerary &itinerary)
// {
//     std::vector<Reservation *> reservations{};
//     reservations = itinerary.getReservations();
//     int count{(int)reservations.size()};
//     std::cout << "Itinerary of " << count << " reservations\n";
//     std::cout << itinerary.toString2() << "\n";
// }

// void Frontend::display_itineraries(const std::vector<Itinerary> &itineraries)
// {
//     int count{(int)itineraries.size()};
//     std::cout << count << " itineraries\n";
//     for (int i = 0; i < count; i++)
//     {
//         std::cout << i + 1 << "- ";
//         display_itinerary(itineraries[i]);
//         std::cout << "\n";
//     }
// }

// User Frontend::login()
// {
//     while (true)
//     {
//         try
//         {
//             return LoginHandler::login();
//         }
//         catch (int e)
//         {
//             Error::display_error(e);
//         }
//     }
// }

// void Frontend::signup()
// {
//     while (true)
//     {
//         try
//         {
//             SignupHandler::signup();
//             return;
//         }
//         catch (int e)
//         {
//             Error::display_error(e);
//         }
//     }
// }

// int Frontend::display_payment_services()
// {
//     std::cout << "Payment Services:\n";
//     std::vector<std::string> services{"Paypal", "Stripe", "Square"};
//     int count{(int)services.size()};
//     Printer::print_options(services);
//     std::cout << "Enter choice(-1 to cancel): ";
//     int choice{};
//     try
//     {
//         choice = InputHandler::get_choice(1, count);
//     }
//     catch (int e)
//     {
//         Error::display_error(e);
//         return display_payment_services();
//     }
//     return choice;
// }
