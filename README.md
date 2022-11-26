# Xpedia
![image](https://user-images.githubusercontent.com/29601694/199601434-1430d707-9bad-41f5-8832-8f26ab20c0c4.png)

Xpedia is an Expedia.com clone project. The website can be used to book airline tickets, hotel reservations, car rentals, cruise ships.
In this project the customer creates a travel itinerary. An Itinerary consists of flight tickets and/or hotel reservations. When the customer requests an itinerary item after adding the search criteria of dates, city, etc, the system calls the APIs for available reservations and the customer selects the reservations he/she finds suitable. Afterwards pays for the reservations for it to be confirmed. This is a C++ console application built using concepts of OOP like inheritance, Polymorphism and adheres to the solid principles and utilizes the suitable design patterns like factoy pattern, startegy pattern, singelton pattern and using Json files as database.
## Video Demo
https://youtu.be/4njfqKla5yE

## Requirements

1. Customers should be able to create a new itinerary.
2. Customers should be able to add a new flight ticket or a new hotel booking to the same itinerary.
3. Customers should be able to search for flights based on a certain date and country of origin/destination.
4. Customers should be able to search for hotel reservation based on the dates and location.
5. Customers should be able to select a flight ticket to buy from the available options.
6. Customers should be able to select a hotel room to book from the available options.
7. The system should be able to handle payments for reservations.
8. The system should cancel the whole itinerary if any of its items is cancelled.

## Use case diagram
![image](https://user-images.githubusercontent.com/29601694/199153401-2816d6a7-a25f-4c1f-8648-ff9efef054f6.png)

## Class diagram
![image](https://user-images.githubusercontent.com/29601694/199153614-8a558b95-15a1-46be-a074-7cc9d796c1a3.png)

## Activity diagram
Create an itinerary<br/>
![activity diagram2 vpd](https://user-images.githubusercontent.com/29601694/199153664-b9c18785-4e68-4041-b0bb-59fb9b823735.jpg)
</br>
diagrams created using visual-paradigm.com

## Selected Design Patterns
### Factory Pattern</br>
![factory2](https://user-images.githubusercontent.com/29601694/200191301-c35dae14-a677-49a9-8220-6d03c22dd07a.jpg)
### Strategy Pattern</br>
![strategy2](https://user-images.githubusercontent.com/29601694/200191438-32c5edc5-0d05-4a5c-b925-af94a3d2d140.jpg)
