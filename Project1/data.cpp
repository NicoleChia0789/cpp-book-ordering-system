//data.cpp
#include "data.h"
#include <fstream>
#include <iostream>
#include <string>
#include <iomanip>
#include <map>
using namespace std;

book_catalogue bookcatalogue[MAX_BOOKS]; // set the maximum number for book catalogue
int bookCount = 0; // number of book

customer customer_info[MAX_CUSTOMER]; // set the maximum number for customer
int customerCount = 0; // number of customer

vector<order>order_detail; // store order detail with no maximum number

sales daily_sales[1000];
int dailyCount = 0;

sales monthly_sales[1000];
int monthlyCount = 0;

int total_sold[MAX_BOOKS] = { 0 };

void clearScreen() { // clear screen
	for (int i = 0; i < 50; i++) {
		cout << endl;
	}
}

// read book catalogue
void loadBook() {
	// declare file stream variables
	ifstream inData;
	// open input file
	inData.open("books.txt");
	if (!inData) {
		cout << "Error opening file"; // promp error msg if can't open file
		return;
	}
	int id, stock;
	string title, category;
	double price;

	// read data
	while (inData >> id) {
		inData.ignore();
		getline(inData, title, '|');
		inData >> category >> price >> stock;
		bookcatalogue[bookCount].id = id;
		bookcatalogue[bookCount].title = title;
		bookcatalogue[bookCount].category = category;
		bookcatalogue[bookCount].price = price;
		bookcatalogue[bookCount].stock = stock;

		bookCount++;
	}
	inData.close(); //close input file
}

// save book catalogue
void saveBook() {
	ofstream outData;
	// open output file
	outData.open("books.txt");
	if (!outData) {
		cout << "Error saving books";
		return;
	}
	// write the data into the file
	for (int i = 0; i < bookCount; i++) {
		outData << bookcatalogue[i].id << " "
			<< bookcatalogue[i].title << "|"
			<< bookcatalogue[i].category << " "
			<< fixed << setprecision(2) << bookcatalogue[i].price << " "
			<< bookcatalogue[i].stock << endl;
	}
	outData.close(); // close output file
}

// display book catalogue
void displayBook() {
	cout << "\nID\t" << left << setw(35) << "TITLE" << left << setw(16) << "CATEGORY" << left << setw(10) << "PRICE" << left << setw(9) << "STOCK" << "SOLD" << endl;
	cout << "------------------------------------------------------------------------------------" << endl;
	for (int i = 0; i < bookCount; i++) {
		cout << bookcatalogue[i].id << "\t" << left << setw(35) << bookcatalogue[i].title << left << setw(16) << bookcatalogue[i].category << left << setw(11) << fixed << setprecision(2) << bookcatalogue[i].price << left << setw(10) << bookcatalogue[i].stock << total_sold[i] << endl;
	}
}

// read order_detail
void loadOrder() {
	ifstream inData;
	inData.open("order.txt");
	if (!inData) {
		cout << "Error opening file";
		return;
	}
	int order_id, quantity;
	double subtotal, total, book_price;
	string username, book_title, payment_method, order_date;

	while (inData >> order_id >> username) {
		inData.ignore();
		getline(inData, book_title, '|');
		inData >> book_price >> quantity >> subtotal >> total;
		inData.ignore();
		getline(inData, payment_method, '|');
		inData >> order_date;
		order_detail.push_back({ order_id, username, book_title, book_price,quantity,subtotal,total,payment_method,order_date }); //push order detail into vector
		for (int j = 0; j < bookCount; j++) {
			if (bookcatalogue[j].title == book_title) {
				total_sold[j] += quantity;
				break;
			}
		}
		// daily sales
		bool found = false;
		for (int i = 0; i < dailyCount; i++) {
			if (daily_sales[i].key == order_date && daily_sales[i].title == book_title) {
				found = true;
				daily_sales[i].quantity += quantity;
				daily_sales[i].revenue += book_price * quantity;
				break;
			}
		}
		if (!found) {
			daily_sales[dailyCount].key = order_date;
			daily_sales[dailyCount].title = book_title;
			daily_sales[dailyCount].quantity = quantity;
			daily_sales[dailyCount].revenue = book_price * quantity;
			dailyCount++;
		}

		// monthly_sales
		string month = order_date.substr(0, 7);
		found = false;
		for (int i = 0; i < monthlyCount; i++) {
			if (monthly_sales[i].key == month && monthly_sales[i].title == book_title) {
				found = true;
				monthly_sales[i].quantity += quantity;
				monthly_sales[i].revenue += book_price * quantity;

				break;
			}
		}
		if (!found) {
			monthly_sales[monthlyCount].key = month;
			monthly_sales[monthlyCount].title = book_title;
			monthly_sales[monthlyCount].quantity = quantity;
			monthly_sales[monthlyCount].revenue = book_price * quantity;
			monthlyCount++;
		}

	}
	inData.close();
}

// save order_detail
void saveOrder() {
	ofstream outData;
	outData.open("order.txt");
	if (!outData) {
		cout << "Error saving order";
		return;
	}
	for (int i = 0; i < order_detail.size(); i++) {
		outData << order_detail[i].order_id << " " << order_detail[i].username << " " << order_detail[i].book_title << "|" << fixed << setprecision(2) << order_detail[i].book_price << " " << order_detail[i].quantity << " " << fixed << setprecision(2) << order_detail[i].subtotal << " " << fixed << setprecision(2) << order_detail[i].total << " " << order_detail[i].payment_method << "|" << order_detail[i].order_date << endl;
	}
	outData.close();
}

// read customer info
void loadCustomer() {
	ifstream inData;
	inData.open("customer.txt");
	if (!inData) {
		cout << "Error opening file";
		return;
	}
	string username, password;

	while (inData >> username >> password) {
		customer_info[customerCount].username = username;
		customer_info[customerCount].password = password;

		customerCount++;
	}
	inData.close();
}

// save customer info
void saveCustomer() {
	ofstream outData;
	outData.open("customer.txt");
	if (!outData) {
		cout << "Error saving customer";
		return;
	}
	for (int i = 0; i < customerCount; i++) {
		outData << customer_info[i].username << " " << customer_info[i].password << endl;
	}
	outData.close();
}