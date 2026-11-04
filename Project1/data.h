//data.h
#ifndef DATA_H
#define DATA_H
#include <map>
#include <string>
#include <vector>
using namespace std;

struct book_catalogue {
	int id;
	string title;
	string category;
	double price;
	int stock;
};

struct customer {
	string username;
	string password;
};

struct order {
	int order_id;
	string username;
	string book_title;
	double book_price;
	int quantity;
	double subtotal;
	double total;
	string payment_method;
	string order_date;
};

struct sales {
	string key;
	string title;
	int quantity = 0;
	double revenue = 0.0;
};

extern sales daily_sales[1000];
extern int dailyCount;

extern sales monthly_sales[1000];
extern int monthlyCount;

const int MAX_BOOKS = 100;
extern book_catalogue bookcatalogue[MAX_BOOKS];
extern int bookCount;

const int MAX_CUSTOMER = 100;
extern customer customer_info[MAX_CUSTOMER];
extern int customerCount;

extern vector<order> order_detail;

extern int total_sold[MAX_BOOKS];

void loadBook();
void saveBook();
void displayBook();
void loadOrder();
void saveOrder();
void loadCustomer();
void saveCustomer();
void clearScreen();

#endif

