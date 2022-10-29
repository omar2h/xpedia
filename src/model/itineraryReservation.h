// #ifndef __ITINERARYRESERVATION_H__
// #define __ITINERARYRESERVATION_H__

// #include "reservation.h"
// #include <vector>
// #include <sstream>

// class ItineraryReservation : public Reservation
// {
// protected:
//     std::vector<Reservation *> reservations; // As has pointers, we need copy constructor

// public:
//     ItineraryReservation() = default;

//     // copy constructor
//     ItineraryReservation(const ItineraryReservation &);

//     void add_reservation(const Reservation &);
//     double total_cost() const override;

//     ~ItineraryReservation() override;

//     const std::vector<Reservation *> &getReservations() const;

//     void clear();

//     std::string toString() const override;

//     Reservation *Clone() const override;
// };

// #endif // __ITINERARYRESERVATION_H__