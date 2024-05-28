# Travel Desk
Ease the process of Booking, Adding and Filtering Trips For a College Event.

# Concepts Used
Vector, Graph, Red Black Trees, Binary Search Trees, Queue, Hash Map, Linked List, Time etc.

# Classess used
1) redblack_tree - A Self-Balancing tree which is used to retrieve Trips Faster.
2) Vehicle - Stores Information of a Vehicle used in Trips.
3) TransportService - It is class which stores RB Tree of Trips with same destination from a same Pickup Location.
4) Location - It Keeps track of collection of TransportService from a Particular Location.
5) TravelDesk - Function Like AddTrip, BookTrip and Show trip.

# Process
1) We will take input in four initials ('AddTrip', 'Showbytime', 'ShowbyDestination', 'BookTrip'). (Sample Input.txt is attached)
2) We will Have Location Pointers for each pick up Locations where for each destination we will have a Red Black Trees.
3) Each Node will Store DepartureTime as key and Trip pointer.
4) For booking Trip we will have a maximum Limit of a bus so if passengers are full then a new bus will be arranged.
5) Show Trip will filter out the required trips by giving Destination or Time range or both. (Given a Pickup Location).

# Advantages 
1) Red Black Tree Are fastest Self Balancing tree among all the trees so inserting new nodes will be faster under large data.
2) Organizing Team will be helped by knowing which buses have no passengers so they can cancel it or by knowing which buses are overflowing so they can arrange a new bus.
