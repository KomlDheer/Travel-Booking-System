# Travel-Booking System
A simple C++ console application for managing travel booking,<br/>
including seat selection, passenger details, and data <br/>
persistence using CSV file.  

## Features
1)Add new booking with passenger name, age, destination, date,
and seat number.<br/>
2)Update existing bookings(name, age, destination, date, seat
number).<br/>
3)Search booking by ID, name, destination or date.<br/>
4)Cancel bookings.<br/>
5)Prevents double-booking of seats for the same destination 
and date.<br/>
6)Data is saved and loaded from a CSV file.

## File Structure
travelbooking.cpp-->Main source code file.<br/>
bookings.csv-->Data file for storing bookings.   

## Notes
1]The program checks for valid input(e.g., name format, 
age range, date format, seat availability).<br/>
2]Maximum number of seats is set by the maxseat variable
 (default : 20).<br/>
3]Each booking is assinged a unique ID. 

## Example Booking Entry:-
Name: *Ram* 
Age: *25*  
Destination: *Jaipur*  
Seat No. :*5*   
ID: *123456*  
Fee: *100*  
Date :*12-07-2025*  
Status :*confirmed*  




