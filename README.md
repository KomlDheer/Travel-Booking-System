# Travel-Booking System
## Overview
A simple C++ console application for managing travel booking, and perform functions<br/>
including seat selection,aquiring passenger details, and ensure data <br/>
persistence by storing the data in a CSV file.  

## Features
1)Add new booking with passenger name, age, destination, date,
and seat number.<br/>
2)Update existing bookings(name, age, destination, date, seat
number).<br/>
3)Search booking by ID, name, destination or date.<br/>
4)Cancel bookings.<br/>
5)Prevents double-booking of seats for the same destination 
and date.<br/>
6)Data is saved and loaded from a CSV file.<br/>


## Structure
________________________________________________________________________
travelbooking.cpp-->Main source code file.<br/>
bookings.csv-->Data file for storing bookings. <br/>
Document.docx-->Full documentation.<br/>
Document.pdf-->Documentation file in pdf format to enable view in GitHub.
________________________________________________________________________

## Notes
### The program checks for valid input
1)Name format: ensures that name does not contain digits or special characters.<br/>
2)Age range: ensures that only a positive integer is entered in range 1 to 150.<br/>
3)Date format: ensured that date is valid and entered in the form DD-MM-YYYY<br/>
4)Seat availability: ensures that no two passengers with same destination and date are alloted same seat.
### Seat summary
1)It displays all the available seat numbers.<br/>
2)Already booked seats are represented with letter 'x'.<br/>
3)Total number of seats is decided by variable 'maxseat' (default :20).
### Unique ID generation
1)A unique ID is generated for each booking.<br/>
2)It is used for identification of passenger to delete or update booking<br/>
### Menu driven system
1)The program takes instructions from user throgh main menu having following options:<br/>
*-Create booking<br/>
-Update booking<br/>
-Search booking<br/>
-Cancel booking<br/>
-Exit system<br/>*

## Example Booking Entry:-
An example of booking entry is shown as:<br/>
_______________________________________________
Name: *Ram* <br/>
Age: *25*  
Destination: *Jaipur*  
Seat No. :*7*   
ID: *17348*  
Fee: *100*  
Date :*12-07-2025*  
________________________________________________<br/>
### Steps for creating new booking
1]Entered name is checked for format. If incorrect, warning is shown for invalid input.<br/>
If the format is evaluated as correct, the firct alphabet of each word of name input is <br/>
converted to uppercase and then displayed.<br/>
<br/>
2]Similarly age is evaluated for its range. If correct displayed in the following line.<br/>
<br/>
3]Destination is to be selected from the list of choices.<br/>
<br/>
4]Input for date and seat number are taken and validated.<br/>
<br/>
5]Finally all the attributes of the created booking are shown in a single line.<br/>
####         Output for above example:

<img width="1254" height="687" alt="Screenshot 2025-07-13 142025" src="https://github.com/user-attachments/assets/2281b656-c5d3-418c-a8be-6f448795fa8d" />


