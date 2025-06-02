#include <iostream>
#include <string>
#include "RoomsBoard.h"
#include <conio.h>

using namespace std;

class ReservedRoom {
private:
    string roomID;
    string courseID;
    int time;

public:
    ReservedRoom(string r, string c, int t) : roomID(r), courseID(c), time(t) {}

    //Creating Const for every method, as this method does not change

    string getRoom() const {
        return roomID;
    }

    string getCourse() const {
        return courseID;
    }

    int getTime() const {
        return time;
    }

    string toString() const {
        return "Room: " + roomID + ", Course: " + courseID + ", Time: " + to_string(time);
    }
};

//int validateTime() {
// was planning on making it a separate function
//}

int main() {
    RoomsBoard<ReservedRoom> board;
    int choice;
    bool menu = true;
    while (menu != false) {
        cout << "***************************************\n";
        cout << "1. Add a program.\n";
        cout << "2. Remove all occrruences of a room.\n";
        cout << "3. Remove all rooms except one.\n";
        cout << "4. Clear the Roomboard.\n";
        cout << "5. Split.\n";
        cout << "6. Display Roomboard.\n";
        cout << "7. Display the reservations of a room.\n";
        cout << "8. Exit\n";
        cout << "***************************************\n";
        cin >> choice;

        if (!cin >> choice) { //if the cin isn't stored as an int upon input, it becomes false so the statement negates the condition to true
            //handle invalid stuff
            cout << "Invalid input, please enter a numer from 1-8." << endl;
            cin.clear(); //clear out the error
            cin.ignore(numeric_limits<streamsize>::max(), '\n'); //ignore the last input - https://stackoverflow.com/questions/25020129/cin-ignorenumeric-limitsstreamsizemax-n
            cout << "Press any key to return to the menu..." << endl;
            _getch(); //waiting for a key
            system("cls"); //clear the screen
            continue; //skip through the loop
        }
        switch (choice) {
            case 1: {
                string roomID, courseID;
                cout << "Enter Room ID: ";
                cin >> roomID;
                cout << "Enter Course ID: ";
                cin >> courseID;
                int time;
                while (true) { //keep going until a valid input is put in
                    cout << "Enter Time: ";
                    cin >> time;
                    if (cin.fail() || time <= 0 || time >= 2400) {
                        cin.clear(); // clear error
                        cin.ignore(numeric_limits<streamsize>::max(), '\n'); // https://stackoverflow.com/questions/25020129/cin-ignorenumeric-limitsstreamsizemax-n
                        cout << "invalid time input. Please enter a valid time between 0 and 2400: \n";
                    }
                    else {
                        break; // break loop if valid
                    }
                }
                ReservedRoom newReservation(roomID, courseID, time);
                board.add(newReservation);
                cout << "Reservation added successfully.\n";
                break;
            }
            case 2: {
                string roomID;
                cout << "Enter Room ID to remove all occurrences: " << endl;
                cin >> roomID;
                board.remove(roomID);
                //cout << "successfully removed" << endl;
                break;
            }
            case 3: {
                string roomID;
                cout << "Enter Room ID to keep: ";
                cin >> roomID;
                board.remove_all_but(roomID);
                break;
            }
            case 4: {
                board.removeAll();
                cout << "All reservations cleared.\n";
                break;
            }
            case 5: {
                RoomsBoard<ReservedRoom> board1, board2;
                board.split(board1, board2);
                cout << "Board split.\n";
                cout << "Board1: " << endl;
                board1.listRooms();
                cout << "Board2: " << endl;
                board2.listRooms();
                break;
            }
            case 6: {
                board.listRooms();
                break;
            }
            case 7: {
                string roomID;
                cout << "Enter Room ID to display reservations: ";
                cin >> roomID;
                board.listReservations(roomID);
                break;
            }
            case 8: {
                menu = false; // Exit the loop
                break;
            }
            default: {
                cout << "Invalid choice. Please enter a number between 1 and 8.\n";
                break;
            }
        }
        cout << "Press any key to return to the menu..." << endl;
        _getch(); //waiting for a key
        system("cls"); //clear the screen
        //Test code
        /* ReservedRoom room1("W330", "PROG23627", 1820);
         ReservedRoom room2("W350", "MATH11044", 1900);

         cout << "Room 1: " << room1.toString() << endl;
         cout << "Room 2: " << room2.toString() << endl;*/

       }
    return 0;
}
