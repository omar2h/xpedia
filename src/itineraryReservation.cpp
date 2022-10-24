// #include "itineraryReservation.h"

// ItineraryReservation::ItineraryReservation(const ItineraryReservation &anotherReservation)
// {
//     for (const Reservation *reservation : anotherReservation.getReservations())
//         add_reservation(*reservation);
// }

// void ItineraryReservation::add_reservation(const Reservation &reservation)
// {
//     reservations.push_back(reservation.Clone());
// }

// double ItineraryReservation::total_cost() const
// {
//     double cost = 0;

//     for (const Reservation *reservation : reservations)
//         cost += reservation->total_cost();

//     return cost;
// }

// ItineraryReservation::~ItineraryReservation()
// {
//     clear();
// }

// const std::vector<Reservation *> &ItineraryReservation::getReservations() const
// {
//     return reservations;
// }

// void ItineraryReservation::clear()
// {
//     for (const Reservation *reservation : reservations)
//         delete reservation;
//     reservations.clear();
// }

// std::string ItineraryReservation::toString() const
// {
//     std::ostringstream oss;

//     oss << "**********************************************\n";
//     oss << "Itinerary of " << reservations.size() << " sub-reservations\n";

//     for (const Reservation *reservation : reservations)
//         oss << reservation->toString() << "\n";

//     oss << "Total Itinerary cost: " << total_cost() << "\n";
//     oss << "**********************************************\n";
//     return oss.str();
// }

// Reservation *ItineraryReservation::Clone() const
// {
//     return new ItineraryReservation(*this);
// }