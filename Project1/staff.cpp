#include <iostream>
#include <string>
#include "data.h"
#include <iomanip>
using namespace std;

void clearScreen();
void backToMenu();
void staffLogin();
int mainMenu();
void staffMain();
int staffMenu();
void bookCatalogue();
void menuManage();
void updateBook();
void addBook();
void removeBook();
void stock();
void salesReport();
void orderReport();

void backToMenu() {
	char key;
	cout << "\n\nPress 'Enter' to return to menu..... ";
	cin.ignore();
	cin.get(key);
	clearScreen();
}

//staff login
void staffLogin() {
	string username, password;
	cout << "\n[Staff Login]" << endl;
	cout << "Username: ";
	cin >> username;
	cout << "Password: ";
	cin >> password;
	if (username == "admin" && password == "admin123") {
		cout << "\nSatff login successfull" << endl;
		clearScreen();
		staffMain();
	}
	else {
		cout << "\nStaff login failed" << endl;
	}
}

void staffMain() {
	int choice;
	do {
		choice = staffMenu();
		switch (choice) {
		case 1:
			bookCatalogue();
			break;
		case 2:
			menuManage();
			break;
		case 3:
			stock();
			break;
		case 4:
			salesReport();
			break;
		case 5:
			orderReport();
			break;
		case 6:
			clearScreen();
			return;
		default:
			cout << "\nYour selection is invalid" << endl;
			break;
		}
	} while (choice != 6);
}

// staff menu
int staffMenu() {
	int choice;
	while (true) {
		cout << "\n===== STAFF MENU =====" << endl;
		cout << "\n1. View Book Catalogue" << endl;
		cout << "2. Menu Management" << endl;
		cout << "3. Stock" << endl;
		cout << "4. Sales Reporting" << endl;
		cout << "5. Order Reporting" << endl;
		cout << "6. Logout" << endl;
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

// view book catalogue
void bookCatalogue() {
	displayBook();
	backToMenu();
	return;
}

// manage book menu
void menuManage() {
	int choice;
	do {
		cout << "\n==== Manage Book Catalogue ====" << endl;
		cout << "\n1. Update Book Info" << endl;
		cout << "2. Add New Book" << endl;
		cout << "3. Remove Book" << endl;
		cout << "4. Return" << endl;
		cout << "\nEnter your choice: ";
		if (!(cin >> choice)) {
			cin.clear();
			cin.ignore(100, '\n');
			cout << "\nInvalid input. Please enter a number." << endl;
			continue;
		}
		switch (choice) {
		case 1:
			updateBook();
			break;
		case 2:
			addBook();
			break;
		case 3:
			removeBook();
			break;
		case 4:
			return;
			break;
		default:
			cout << "\nInvalid choice" << endl;
			break;
		}
	} while (choice != 4);
}

// eidt book info
void updateBook() {
	int id, choice, i;
	bool found = false;
	do {
		cout << "\n================================== BOOK CATALOGUE ==================================" << endl;
		displayBook();
		cout << "\nEnter book id to update book info: ";
		if (!(cin >> id)) {
			cin.clear();
			cin.ignore(100, '\n');
			cout << "\nInvalid input. Please enter a number.\n" << endl;
			continue;
		}
		for (i = 0; i < bookCount; i++) {
			if (bookcatalogue[i].id == id) {
				found = true;
				do {
					cout << "\n1. Update Title" << endl;
					cout << "2. Update Category" << endl;
					cout << "3. Update Price" << endl;
					cout << "4. Return" << endl;
					cout << "\nSelect field to update: ";
					// check if the input is invalid
					if (!(cin >> choice)) {
						cin.clear();
						cin.ignore(100, '\n');
						cout << "\nInvalid input. Please enter a number." << endl;
						continue;
					}
					switch (choice) {
					case 1:
						cout << "\nEnter new title: ";
						cin.ignore();
						getline(cin, bookcatalogue[i].title);
						break;
					case 2:
						cout << "\nEnter new category: ";
						cin.ignore();
						getline(cin, bookcatalogue[i].category);
						break;
					case 3:
						cout << "\nEnter new price: ";
						cin >> bookcatalogue[i].price;
						break;
					case 4:
						return;
						break;
					default:
						cout << "\nInvalid choice." << endl;
						break;
					}
					if (choice == 1 || choice == 2 || choice == 3) {
						saveBook();
						cout << "\nBook info updated successfully" << endl;
						cout << "\n============================== CURRENT BOOK CATALOGUE ==============================" << endl;
						displayBook();
						backToMenu();
						return;
					}
				} while (choice < 1 || choice > 4);
			}
		}
		if (!found) { // the book is not exist
			cout << "\nBook not found." << endl;
		}
	} while (!found);
}

// add new book
void addBook() {
	if (bookCount >= MAX_BOOKS) {
		cout << "Book catalogue is full!" << endl;
		return;
	}
	book_catalogue newBook;
	// new id for new book
	newBook.id = (bookCount == 0) ? 1 : bookcatalogue[bookCount - 1].id + 1;
	cout << "Enter book title: ";
	cin.ignore();
	getline(cin, newBook.title);
	cout << "Enter book category: ";
	getline(cin, newBook.category);
	cout << "Enter book price: ";
	cin >> newBook.price;
	cout << "Enter book stock: ";
	cin >> newBook.stock;
	bookcatalogue[bookCount] = newBook;
	bookCount++;
	// save the new book into book catalogue
	saveBook();
	cout << "\nBook added successfully!" << endl;
	cout << "\n============================== CURRENT BOOK CATALOGUE ==============================" << endl;
	displayBook();
	backToMenu();
	return;
}

// remove book
void removeBook() {
	int id, i;
	bool found = false;
	do {
		cout << "\n================================== BOOK CATALOGUE ==================================" << endl;
		displayBook();
		cout << "\nEnter book id to remove: ";
		if (!(cin >> id)) {
			cin.clear();
			cin.ignore(100, '\n');
			cout << "\nInvalid input. Please enter a number.\n" << endl;
			continue;
		}
		for (i = 0; i < bookCount; i++) { //find the corresponding book
			if (bookcatalogue[i].id == id) {
				found = true; //book is exist
				for (int j = i; j < bookCount - 1; j++) {
					bookcatalogue[j] = bookcatalogue[j + 1]; //replace the book
				}
				bookCount--;
				for (int k = 0; k < bookCount; k++) {
					bookcatalogue[k].id = k + 1; //rearrange the id
				}
				cout << "Book removed successfully!" << endl;
				saveBook();
				cout << "\n============================== CURRENT BOOK CATALOGUE ==============================" << endl;
				displayBook();
				backToMenu();
				return;
			}
		}
		if (!found) {
			cout << "\nBook not found" << endl;
		}
	} while (!found);
}

void stock() {
	int choice, i, id;
	bool found = false;
	do {
		cout << "\n==== STOCK MANAGEMENT ====" << endl;
		cout << "\n1. View Stock" << endl;
		cout << "2. Update Stock" << endl;
		cout << "3. Return" << endl;
		cout << "\nEnter your choice: ";
		if (!(cin >> choice)) {
			cin.clear();
			cin.ignore(100, '\n');
			cout << "\nInvalid input. Please enter a number." << endl;
			continue;
		}
		switch (choice) {
		case 1: // view stock
			cout << "\n==================================== VIEW STOCK ====================================" << endl;
			displayBook();
			backToMenu();
			return;
			break;
		case 2: // edit stock
			do {
				cout << "\n===================================== STOCK ========================================" << endl;
				displayBook();
				cout << "\nEnter book id to update stock: ";
				if (!(cin >> id)) {
					cin.clear();
					cin.ignore(100, '\n');
					cout << "\nInvalid input. Please enter a number." << endl;
					continue;
				}
				for (i = 0; i < bookCount; i++) {
					if (bookcatalogue[i].id == id) {
						found = true;
						cout << "Enter new stock: ";
						cin >> bookcatalogue[i].stock;
						saveBook(); //save new stock for the book
						cout << "\n=================================== CURRENT STOCK ==================================" << endl;
						displayBook();
						backToMenu();
						return;
					}
				}
				if (!found) {
					cout << "\nBook not found" << endl;
				}
			} while (!found);
			break;
		case 3:
			return;
			break;
		default:
			cout << "\nInvalid choice" << endl;
			break;
		}
	} while (choice != 3);
}

// generate sales report
void salesReport() {
	int choice;
	string date, month;
	bool found;
	double total_revenue;
	int total_quantity;
	do {
		cout << "\n========== Sales Report ==========" << endl;
		cout << "1. Daily Sales Report" << endl;
		cout << "2. Monthly Sales Report" << endl;
		cout << "3. Return" << endl;
		cout << "\nEnter your choice: ";
		if (!(cin >> choice)) {
			cin.clear();
			cin.ignore(100, '\n');
			cout << "\nInvalid input. Please enter a number." << endl;
			continue;
		}
		switch (choice) {
		case 1: // daily sales report
			total_revenue = 0;
			total_quantity = 0;
			found = false;
			cout << "\nDate (YYYY-MM-DD): ";
			cin >> date;
			cout << "\n===== Daily Sales Report =====" << endl;
			cout << "\n" << left << setw(35) << "TITLE" << left << setw(15) << "SOLD" << "SALES" << endl;
			cout << "---------------------------------------------------------------------" << endl;
			for (int i = 0; i < dailyCount; i++) {
				if (daily_sales[i].key == date) {
					found = true;
					cout << left << setw(36) << daily_sales[i].title << left << setw(14) << daily_sales[i].quantity << fixed << setprecision(2) << daily_sales[i].revenue << endl;
					total_quantity += daily_sales[i].quantity; // calculate the total quantity 
					total_revenue += daily_sales[i].revenue; // calculate the total revenue 
				}
			}
			cout << "\n---------------------------------------------------------------------" << endl;
			if (found) {
				cout << "\nTotal Sold: " << total_quantity << endl;
				cout << "Total Daily Sales: " << total_revenue << endl;
			}
			if (!found) {
				cout << "Sales not found on " << date << endl;
			}
			backToMenu();
			return;
			break;
		case 2: // monthly sales report
			total_revenue = 0;
			total_quantity = 0;
			found = false;
			cout << "\nMonth (YYYY-MM): ";
			cin >> month;
			cout << "\n===== Monthly Sales Report =====" << endl;
			cout << "\n" << left << setw(35) << "TITLE" << left << setw(15) << "SOLD" << "SALES" << endl;
			cout << "---------------------------------------------------------------------" << endl;
			for (int i = 0; i < monthlyCount; i++) {
				if (monthly_sales[i].key == month) {
					found = true;
					cout << left << setw(36) << monthly_sales[i].title << left << setw(14) << monthly_sales[i].quantity << fixed << setprecision(2) << monthly_sales[i].revenue << endl;
					total_quantity += monthly_sales[i].quantity; // calculate the total quantity 
					total_revenue += monthly_sales[i].revenue; // calculate the total revenue 
				}
			}
			cout << "\n---------------------------------------------------------------------" << endl;
			if (found) {
				cout << "\nTotal Sold: " << total_quantity << endl;
				cout << "Total Monthly Sales: " << total_revenue << endl;
			}
			if (!found) {
				cout << "Sales not found on " << date << endl;
			}
			backToMenu();
			return;
			break;
		default:
			cout << "Invalid selection." << endl;
		}
	} while (choice != 3);
}

// generate order report
void orderReport() {
	bool found = false;
	string date;
	cout << "\nDate (YYYY-MM-DD): ";
	cin >> date;
	cout << "\n============= Order Report on " << date << " ==============" << endl;
	for (int i = 0; i < order_detail.size(); i++) {
		if (order_detail[i].order_date == date) {
			found = true;
			cout << "Order ID: " << order_detail[i].order_id << "\n" << "Customer Name: " << order_detail[i].username << "\n" << "Title: " << order_detail[i].book_title << "\n" << "Price: " << order_detail[i].book_price << "\n" << "Quantity: " << order_detail[i].quantity << "\n" << "Subtotal: " << order_detail[i].subtotal << "\n" << "Total: " << order_detail[i].total << "\n" << "Payment method: " << order_detail[i].payment_method << "\n" << "Order Date: " << order_detail[i].order_date << endl;
			cout << "\n---------------------------------------------------------------------\n" << endl;
		}
	}
	if (!found) {
		cout << "Order not found on " << date << endl;
	}
	backToMenu();
	return;
}