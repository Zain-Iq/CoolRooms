#pragma once
#ifndef ROOMSBOARD_H
#define ROOMSBOARD_H
#include <stdexcept>
#include <vector>
#include <algorithm>

using namespace std;

//define the node here
template <typename E>
class SNode {
private:
	E data;
	SNode<E>* next;

	SNode(const E& d) : data(d), next(nullptr) {} //add constructor to take arguments

	template<class T> friend class RoomsBoard; //making it a friend class
};

template<typename E>
class RoomsBoard {
public:
	RoomsBoard()
	{
		head = nullptr;
		tail = nullptr;
		sz = 0;
	}
	// int size() { return sz; }
	void add(const E& r) {
		SNode<E>* newest = new SNode<E>(r);
		newest->data = r;
		if (isEmpty() == true) {
			head = newest;
			tail = newest;
			sz = 1;
			return;
		}
		else if (r.getTime() < head->data.getTime()) {
			newest->next = head;
			head = newest;
		}
		else
		{
			//add a current node
			SNode<E>* current = head;
			while (current->next != nullptr && r.getTime() > current->next->data.getTime()) { 
				current = current->next;
			}
			newest->next = current->next; 
			current->next = newest;
			if (current == tail) {
				tail = newest;
			}
			sz++;
		}
	}
	void remove(const string& roomID) {
		if (isEmpty() == true) {
			cout << "Nothing to remove, empty list" << endl; 
			return;
		}
		bool flag = false; //flag to make sure I find the room, if I dont, then I can say nothing with that room ID found
		SNode<E>* prev = nullptr; //want to keep track of the previous node while traversing the list and head has no previous node
		SNode<E>* current = head; //making the current node head
		while (current != nullptr) {
			if (current->data.getRoom() == roomID) {
				if (prev == nullptr) {
					head = current->next; //change head to next value since we are removing head
					delete current; //get rid of the current value which was the head value
					current = head; //now make current = head again after
					if (head == nullptr) {
						tail = nullptr; //basically if the next ptr after head is nullptr that means tail = null and the list is empty now
					}
					sz--;
					flag = true;
					continue;
				}
				else {
					prev->next = current->next;
					if (current == tail) {
						tail = prev;
					}
					delete current; //get rid of the last node
					current = prev->next; //make current the end of the node
					flag = true;
					sz--;
				}
			}
			else {
				//code to traverse to the next node while updating the prev and current if roomID is not the same
				prev = current;
				current = current->next;
			}
		}
		if (flag == false) {
			cout << "No rooms with that ID found\n";
		}
		else {
			cout << "Room Successfully removed\n";
		}
	}

	void remove_all_but(const string& roomID) {
		if (isEmpty() == true) {
			cout << "Empty List, nothing to remove" << endl;
			return;
		}
		SNode<E>* prev = nullptr;
		SNode<E>* current = head;
		bool flag = false; //flag to make sure I find the room, if I dont, then I can say nothing with that room ID found
		while (current != nullptr) {
			if (current->data.getRoom() == roomID) {//does match
				flag = true;
				break; //stop the loop
			}
			current = current->next;
		}
		if (flag == false) {
			cout << "No rooms with that ID found\n";
		}
		else {
			while (current != nullptr) {
				if (current->data.getRoom() != roomID) { // doesn't match, remove the node
					if (prev == nullptr) {
						head = current->next; //make head the next node
						delete current; //delete temp which was the current node
						current = head; //after moving the head to the next node, now update current to be the next node which is now head 
						if (head == nullptr) //check if there is no head meaning empty list, make the tail null too
						{
							tail = nullptr;
						}
					}
					else {
						prev->next = current->next; //make the next node linked to the new prev
						SNode<E>* temp = current; //make a temp node to hold the current and delete it so you can change the current to next node 
						current = current->next; //this should now be the next node
						delete temp; //free up some memory!
					}
					sz--;
				}
				else { //for matching ID, traverse to the next node
					prev = current;
					current = current->next;
				}
			}
			cout << "All but one room Successfully removed\n";
		}	
	}

	void removeAll() {

		if (isEmpty() == true) {
			cout << "Empty list, nothing to remove" << endl;
			return;
		}

		SNode<E>* current = head;
		while (current != nullptr) { //run while current is not null 
			SNode<E>* temp = current; //make a temp to hold current and then delete temp and once it loops temp equals the new current and repeats
			current = current->next;
			delete temp;
		}
		head = nullptr;
		tail = nullptr;
		sz = 0;
	}
	void split(RoomsBoard<E>& board1, RoomsBoard<E>& board2) {
		if (isEmpty() == true) {
			cout << "Emptry list, nothing to remove" << endl;
			return;
		}
		SNode<E>* current = head;

		while (current != nullptr) {
			if (current->data.getTime() < 1200) {
				board1.add(current->data);
				//cout << current->data.toString() << endl; instead, you can use the listRooms() functions for efficieny
			}
			else {
				board2.add(current->data);
				//cout << current->data.toString() << endl;
			}
			current = current->next;
		}
		//Inefficient making 2 separate while loops
		//current = head; // reset head

		//cout << "Board2: " << endl;
		//while (current != nullptr) {
		//	if (current->data.getTime() >= 1200) {
		//		board2.add(current->data);
		//		cout << current->data.toString() << endl;
		//	}

		//	current = current->next;
		//}

	}

	void listRooms() const {
		if (isEmpty() == true) {
			cout << "There are currently no rooms reserved." << endl;
			return;
		}

		SNode<E>* current = head;
		//just lists rooms as current keeps changing
		while (current != nullptr) {
			cout << current->data.toString() << endl;
			current = current->next;
		}

	}

	void listReservations(const string& roomID) {
		if (isEmpty() == true) {
			cout << "No Rooms Resereved" << endl;
			return;
		}
		SNode<E>* current = head;
		bool flag = false; //make a flag that lets you know if you found any reservations that match the roomID, could make an else statement but this works better for me
		while (current != nullptr) {
			if (current->data.getRoom() == roomID) {
				cout << current->data.toString() << endl;
				flag = true;
			}

			current = current->next;
		}

		if (flag == false) {
			cout << "Could not find a reservation under the room ID: " << roomID << "." << endl;
		}
	}

	int size() const {
		if (isEmpty() == true) {
			cout << "No Rooms";
			return;
		}
		int count = 0;
		SNode<E>* current = head;
		while (current != nullptr) {
			count++;
			current = current->next;
		}
		return count;
	}

	bool isEmpty() const {
		if (sz == 0) {
			return true;
		}
	}

private:
	SNode<E>* head;
	SNode<E>* tail;
	int sz;
};

#endif // !ROOMSBOARD_H
