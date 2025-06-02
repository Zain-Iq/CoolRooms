# 🏫 Classroom Reservation System (C++)

A console-based classroom reservation management system implemented in C++ using a singly linked list. It maintains classroom bookings in chronological order for a single day and provides operations to manage, view, and filter reservations.

---

## 📋 Overview

This application allows users to reserve classrooms by course and time, manage those reservations, and interact with them via a menu-driven interface. The system ensures all reservations are stored in non-decreasing order of start time.

---

## 🧱 Core Components

### 🔹 `ReservedRoom` Class  
Represents a single classroom reservation.

**Fields:**
- `roomID` — Identifier for the classroom (e.g., `W330`)
- `courseID` — Identifier for the course (e.g., `PROG23672`)
- `time` — Start time in 24-hour format (e.g., `1820`)

**Methods:**
- Constructor to initialize room, course, and time
- `getRoom()` – Returns the room ID
- `getCourse()` – Returns the course ID
- `getTime()` – Returns the reservation time
- `toString()` – String representation of the reservation

---

### 🔹 `RoomsBoard` Class  
Maintains a linked list of `ReservedRoom` objects.

**Operations:**
- `add(ReservedRoom r)` — Adds a reservation in sorted order
- `remove(string roomID)` — Removes all reservations for a specific room
- `remove_all_but(string roomID)` — Keeps only reservations for the specified room
- `removeAll()` — Clears all reservations
- `split(RoomsBoard board1, RoomsBoard board2)` — Splits reservations into AM and PM lists
- `listRooms()` — Displays all reservations in sorted order
- `listReservations(string roomID)` — Lists all reservations for a given room
- `size()` — Returns the total number of reservations
- `isEmpty()` — Checks whether the list is empty

---

## 💻 Menu Options

A user-friendly console interface with the following options:

1. Add a new room reservation  
2. Remove all reservations for a specified room  
3. Keep only reservations for one room  
4. Clear all reservations  
5. Split reservations into two lists (before and after 12:00)  
6. Display all reservations  
7. Display reservations for a specific room  
8. Exit the program  

---

## ⚙️ Error Handling

The program handles a variety of edge cases including:
- Removing from or displaying an empty list  
- Attempting to remove non-existent room entries  
- Invalid menu inputs  
