#include <iostream>
#include <string>
#include "data.h"
using namespace std;

int mainMenu();
void staffLogin();
void customerLogin();
void customerRegister();

int main() {
	loadBook();
	loadOrder();
	loadCustomer();
	int choice;
	do {
		choice = mainMenu();
		switch (choice) {
		case 1:
			staffLogin();
			break;
		case 2:
			customerLogin();
			break;
		case 3:
			customerRegister();
			break;
		case 0:
			cout << "\nExiting system..." << endl;
			break;
		default:
			cout << "\nYour selection is invalid." << endl;
			break;
		}
	} while (choice != 0);
	return 0;
}

//display main menu
int mainMenu() {
	int choice;
	while (true) {
		cout << "\n==== TARCIAN BOOKSTORE ORDERING SYSTEM ====" << endl;
		cout << "\n1. Staff Login" << endl;
		cout << "2. Customer Login" << endl;
		cout << "3. Customer Register" << endl;
		cout << "0. Exit" << endl;
		cout << "\nEnter your choice: ";
		if (cin >> choice) {
			return choice;
		}
		else {
			cin.clear();
			cin.ignore(100, '\n');
			cout << "\nInvalid input. Please enter a number." << endl;
		}
	}
}
