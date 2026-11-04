#include <iostream>
#include <string>
#include "data.h"
#include <iomanip>
#include <ctime>
using namespace std;

string getCurrentDate();
void clearScreen();
int clearShoppingCart();
void backToMenuPage();
void customerLogin();
void customerRegister();
void customerMenu();
void order_Entry();
void addToCart(int, int);
void browseBooks();
void ViewShoppingCart();
void processCheckOut();
void orderHistory();

// shopping cart item information
struct CartItem {
    int id = 0;
    int quantity = 0;
};

const int MAX_CART_ITEMS = 20; // maximum number of items in the shopping cart
CartItem cart[MAX_CART_ITEMS];
int cartCount = 0; // number of items in the shopping cart
int order_id;
string username;

// get the current date
string getCurrentDate() {
    time_t timestamp = time(NULL);
    struct tm datetime;
    localtime_s(&datetime, &timestamp);
    char output[20];
    strftime(output, sizeof(output), "%Y-%m-%d", &datetime);
    return string(output);
}

int clearShoppingCart() {
    cartCount = 0;
    return cartCount;// clear shoppingc card to 0.
}

// back to customer menu
void backToMenuPage() {
    char key;
    cout << "\n\nPress 'Enter' to return to customer menu..... ";
    cin.ignore();
    cin.get(key);
    clearScreen();
}

// customer login
void customerLogin() {
    string password;
    bool loginSuccess = false;

    cout << "\n========== Customer Login ==========\n";
    cout << "Enter username: ";
    cin >> username;
    cout << "Enter password: ";
    cin >> password;

    for (int i = 0; i < customerCount; i++) {
        if (customer_info[i].username == username && customer_info[i].password == password) {
            cout << "\nCustomer login successful\n" << endl;
            clearScreen();
            customerMenu();
            loginSuccess = true;
            break;
        }
    }

    if (!loginSuccess) {
        cout << "\nInvalid username or password.\n" << endl;
    }
}

// register new customer
void customerRegister() {
    int i;
    bool found;
    if (customerCount >= MAX_CUSTOMER) { // check if the number of customer exceed the customer accomoadation
        cout << "Registration is full!" << endl;
        return;
    }
    customer newCustomer; // add new customer
    do {
        cout << "\n========== CUSTOMER REGISTRATION ==========\n";
        cout << "Enter your username: ";
        cin >> newCustomer.username;
        found = false;
        // check if the username is already being used
        for (i = 0; i < customerCount; i++) {
            if (customer_info[i].username == newCustomer.username) {
                found = true;
                cout << "Username already exists! " << endl;
            }
        }
        if (!found) {
            break;
        }
    } while (found);
    // the username is not being used
    cout << "Enter your password: ";
    cin >> newCustomer.password;
    cout << "Registration successfully" << endl;
    customer_info[customerCount] = newCustomer; // add new customer
    customerCount++; // add the number of customer
    saveCustomer(); // save the new customer into customer info
}


//------------------------main customer page-----------------------------------------------------
void customerMenu() {

    int customerChoice;

    cout << "\t\t\t  _____  _    ____   ____ ___    _    _   _          " << endl;
    cout << "\t\t\t |_   _|/ \\  |  _ \\ / ___|_ _|  / \\  | \\ | |         " << endl;
    cout << "\t\t\t   | | / _ \\ | |_) | |    | |  / _ \\ |  \\| |         " << endl;
    cout << "\t\t\t   | |/ ___ \\|  _ <| |___ | | / ___ \\| |\\  |         " << endl;
    cout << "\t\t\t  _|_/_/ __\\_\\_|_\\_\\\\____|___/_/___\\_\\_| \\_|_  _____ " << endl;
    cout << "\t\t\t | __ ) / _ \\ / _ \\| |/ / ___|_   _/ _ \\|  _ \\| ____|" << endl;
    cout << "\t\t\t |  _ \\| | | | | | | ' /\\___ \\ | || | | | |_) |  _|  " << endl;
    cout << "\t\t\t | |_) | |_| | |_| | . \\ ___) || || |_| |  _ <| |___ " << endl;
    cout << "\t\t\t |____/ \\___/ \\___/|_|\\_\\____/ |_| \\___/|_| \\_\\_____|" << endl;

    cout << "\n===================================== Customer Menu =====================================\n\n";
    cout << right << setw(53) << "TARCIAN BOOKSTORE" << endl;
    cout << "\t\t\t\tNo. K666, Block K TARUMT," << endl;
    cout << right << setw(63) << "Jalan Genting Klang, Setapak, 53000" << endl;
    cout << right << setw(50) << "Kuala Lumpur." << endl;
    cout << "\n";
    // discount announcement 
    cout << " _____________________________________" << endl;
    cout << "|                                     |" << endl;
    cout << "| Special OFFER !!!                   |" << endl;
    cout << "| Spend RM50 to get a 5% discount!!   | " << endl;
    cout << "| Spend RM100 to get a 10% discount!! |" << endl;
    cout << "|_____________________________________|" << endl;

    do {
        cout << "\nDear customer. Welcome to TARCIAN Book Ordering System!\n" << endl;
        cout << "1. Order Entry" << endl;
        cout << "2. Browse all Books" << endl;
        cout << "3. View Shopping Cart" << endl;
        cout << "4. Process to Checkout" << endl;
        cout << "5. View Order History" << endl;
        cout << "6. Logout" << endl;
        cout << "\nChoice: ";
        if (!(cin >> customerChoice)) { // check the input validation
            cin.clear();
            cin.ignore(100, '\n');
            cout << "\nInvalid input. Please enter a number.\n" << endl;
            continue;
        }
        cout << "\nYou have selected option " << customerChoice << ".\n\n";
        switch (customerChoice) {
        case 1:
            order_Entry();
            break;
        case 2:
            browseBooks();
            break;
        case 3:
            ViewShoppingCart();
            break;
        case 4:
            processCheckOut();
            break;
        case 5:
            orderHistory();
            break;
        case 6:
            cout << "Thank you for visiting TARCIAN Book Ordering System!\n";
            clearScreen();
            return;
            break;
        default:
            cout << "Invalid choice. Please try again." << endl;
            break;
        }
    } while (customerChoice != 6);
}

// order for book
void order_Entry() {
    int id, quantity, month;
    char continueOrder;
    bool found;
    int orderNum = 1;

    cout << "\n================================== BOOK CATALOGUE ==================================" << endl;
    displayBook();
    do {
        cout << "\nOrder " << orderNum << endl;
        do {
            found = false;
            cout << "Enter the book ID to add to shopping cart: ";
            if (!(cin >> id)) {
                cin.clear();
                cin.ignore(100, '\n');
                cout << "\nInvalid input. Please enter a number.\n" << endl;
                continue;
            }
            for (int i = 0; i < bookCount; i++) {
                if (bookcatalogue[i].id == id) {
                    found = true;
                    int already_quantity = 0;
                    for (int k = 0; k < cartCount; k++) {
                        if (cart[k].id == bookcatalogue[i].id) {
                            already_quantity = cart[k].quantity;
                            break;
                        }
                    }
                    do {
                        cout << "Enter quantity: ";
                        if (!(cin >> quantity)) {
                            cin.clear();
                            cin.ignore(100, '\n');
                            cout << "\nInvalid input. Please enter a number.\n" << endl;
                            continue;
                        }

                        if (quantity > 0 && (quantity + already_quantity) <= bookcatalogue[i].stock) {
                            addToCart(id, quantity);
                            cout << "Added to cart: " << quantity
                                << " copy/copies of \"" << bookcatalogue[i].title << "\"" << endl;
                            already_quantity += quantity;
                            break;
                        }
                        else {
                            if (quantity == 0) {
                                break;
                            }
                            cout << "Invalid quantity. ";
                            cout << "Available stock: " << bookcatalogue[i].stock - already_quantity << endl;
                            if (bookcatalogue[i].stock - already_quantity == 0) {
                                break;
                            }
                        }
                    } while (true);

                    break;
                }
            }
            if (!found) {
                cout << "Invalid Book ID, Please Enter Again.\n" << endl;
            }

        } while (!found);

        // continue order or exit
        do {
            cout << "\nAnymore order (Y/N)? ";
            cin >> continueOrder;
            if (!(continueOrder == 'Y' || continueOrder == 'y' || continueOrder == 'N' || continueOrder == 'n')) {
                cout << "Invalid input. Please try again.\n" << endl;
            }
        } while (!(continueOrder == 'Y' || continueOrder == 'y' || continueOrder == 'N' || continueOrder == 'n'));

        orderNum++;

    } while (continueOrder == 'Y' || continueOrder == 'y');

    backToMenuPage();
    return;

}

// add the book to shopping cart
void addToCart(int id, int quantity) {
    // check if the book is already exist in the shopping cart
    for (int i = 0; i < cartCount; i++) {
        if (cart[i].id == id) { // if yes
            cart[i].quantity += quantity; // calculate the total quantity
            return;
        }
    }
    //if no,add new item to cart
    cart[cartCount].id = id;
    cart[cartCount].quantity = quantity;
    cartCount++; // shopping cart count +1
}

// view book catalogue
void browseBooks() {
    cout << "\n================================== BOOK CATALOGUE ==================================" << endl;
    displayBook();
    backToMenuPage();
    return;
}

// view shopping cart
void ViewShoppingCart() {

    double total = 0.0;

    if (cartCount == 0) { // check if the cart is empty
        cout << "\n===================================== Hi I'm your Shopping Cart =====================================\n\n";
        cout << "!!! Your shopping cart is empty yet.!!!" << endl;
        cout << "Please add some books to your cart first." << endl;

        backToMenuPage();
        return;
    }
    // the cart is not empty
    cout << "\n========================== Hi I'm your Shopping Cart ==========================\n\n";
    cout << fixed << setprecision(2); // Set decimal precision for prices
    cout << left << setw(5) << "No." << setw(35) << "Title" << setw(10) << "Qty" << setw(15) << "Price (RM)" << setw(15) << "Total (RM)" << endl;
    cout << "-------------------------------------------------------------------------------" << endl;
    for (int i = 0; i < cartCount; i++) {
        //Find the book corresponding to this bookId
        for (int j = 0; j < bookCount; j++) {
            if (bookcatalogue[j].id == cart[i].id) {
                total = cart[i].quantity * bookcatalogue[j].price;
                cout << left << setw(5) << i + 1 << setw(36) << bookcatalogue[j].title << setw(10) << cart[i].quantity << setw(15) << bookcatalogue[j].price << setw(10) << total << endl;
            }
        }
    }
    // remove item from shopping cart
    char confirm;
    do {
        cout << "\nDo you want to remove an item from cart? (Y/N): ";
        if (!(cin >> confirm)) {
            cin.clear();
            cin.ignore(100, '\n');
            cout << "Invalid input." << endl;
            continue;
        }
        if (confirm != 'Y' && confirm != 'y' && confirm != 'n' && confirm != 'N') {
            cout << "Invalid input." << endl;
        }
    } while (confirm != 'Y' && confirm != 'y' && confirm != 'n' && confirm != 'N');

    if (confirm == 'N' || confirm == 'n') { // no remove action
        cout << "Okay, nothing removed.\n";
        backToMenuPage();
        return;
    }
    // remove action
    int choice;
    do {
        cout << "Enter the item number to remove (0 to cancel): ";
        if (!(cin >> choice)) {
            cin.clear();
            cin.ignore(100, '\n');
            cout << "Invalid input.\n";
            continue;
        }
        if (choice == 0) { // cancel the remove 
            cout << "Remove cancelled.\n";
            backToMenuPage();
            return;
        }

        if (choice < 1 || choice > cartCount) {
            cout << "Invalid item number.\n";
        }
    } while (choice < 1 || choice > cartCount);

    // remove the corresponding item
    for (int i = choice - 1; i < cartCount - 1; i++) {
        cart[i] = cart[i + 1]; //replace the item
    }
    cartCount--; //cart count decreased by 1

    cout << "Item removed successfully.\n";

    // display the current shopping cart
    if (cartCount == 0) { // shopping cart is empty
        cout << "\nNow your shopping cart is empty.\n";
        backToMenuPage();
        return;
    }
    else {
        cout << "\nUpdated Shopping Cart:\n";
        total = 0.0;
        cout << left << setw(5) << "No." << setw(35) << "Title" << setw(10) << "Qty" << setw(15) << "Price (RM)" << setw(15) << "Total (RM)" << endl;
        cout << "-------------------------------------------------------------------------------" << endl;

        for (int i = 0; i < cartCount; i++) {
            for (int j = 0; j < bookCount; j++) {
                if (bookcatalogue[j].id == cart[i].id) {
                    double itemTotal = cart[i].quantity * bookcatalogue[j].price;
                    total += itemTotal;
                    cout << left << setw(5) << i + 1 << setw(36) << bookcatalogue[j].title << setw(10) << cart[i].quantity << setw(15) << bookcatalogue[j].price << setw(15) << itemTotal << endl;
                }
            }
        }
        backToMenuPage();
        return;
    }
}

// checkout
void processCheckOut() {
    char confirmCheckout;

    // check if the shopping cart is empty
    if (cartCount == 0) {
        cout << "Remainder: " << endl;
        cout << "!!! Your shopping cart is empty yet.!!!" << endl;
        cout << "Please add some books to your cart first." << endl;

        backToMenuPage();
        return;
    }
    // shopping cart is not empty
    do {
        cout << "Are you confirm to process checkout (Y/N): ";
        cin >> confirmCheckout;

        if (confirmCheckout == 'N' || confirmCheckout == 'n') {
            cout << "\n(return to customer menu)" << endl;
            clearScreen();
            return;
        }
        else if (confirmCheckout != 'Y' && confirmCheckout != 'y') {
            cout << "Please enter Y or N." << endl;
        }
    } while (confirmCheckout != 'Y' && confirmCheckout != 'y');

    cout << "Okay... Then let's goo!" << endl;


    //------------------------------------------------ invoice page ---------------------------------------------
    double Total = 0.0, subtotal = 0.0;
    string typePaymentMethod;
    char paymentMethod;
    string date = getCurrentDate(); // checkout date

    if (!order_detail.empty()) { // check if the order_detail is empty
        order_id = order_detail.back().order_id + 1; // if not, order_id + 1
    }
    else {
        order_id = 1; // if yes, set the order_id with 1
    }

    clearScreen();

    cout << "\n\nInvoice: \n" << endl;
    cout << right << setw(53) << "TARCIAN BOOKSTORE" << endl;
    cout << "\t\t\t\tNo. K666, Block K TARUMT," << endl;
    cout << right << setw(63) << "Jalan Genting Klang, Setapak, 53000" << endl;
    cout << right << setw(50) << "Kuala Lumpur." << endl;
    cout << right << setw(53) << "Tel : 03 - 1314520 " << endl;
    cout << "\n";

    cout << "Invoice No. INV: " << order_id << right << setw(53) << "Date: " << date << endl;

    cout << "---------------------------------------------------------------------------------" << endl;
    cout << fixed << setprecision(2); // Set decimal precision for prices
    cout << left << setw(5) << "ID" << setw(35) << "Title" << setw(10) << "Qty" << setw(15) << "Price (RM)" << setw(15) << "Total (RM)" << endl;
    cout << "---------------------------------------------------------------------------------" << endl;


    for (int i = 0; i < cartCount; i++) {
        // find the corresponding book
        for (int j = 0; j < bookCount; j++) {
            if (bookcatalogue[j].id == cart[i].id) {
                Total = cart[i].quantity * bookcatalogue[j].price;
                subtotal += Total;

                cout << left << setw(5) << i + 1 << setw(36) << bookcatalogue[j].title << setw(10) << cart[i].quantity << setw(15) << bookcatalogue[j].price << setw(10) << Total << endl;
            }
        }
    }
    // calculate discount, tax and total payable
    double serviceTax = 0.0, SST = 0.0, totalPayable = 0.0, discountPrice = 0.0;
    string discountPercentage;

    if (subtotal > 0 && subtotal < 50) {
        discountPercentage = "(0%) : ";
        discountPrice = subtotal * 0.00;
    }
    else if (subtotal >= 50 && subtotal < 100) {
        discountPercentage = "(5%) : ";
        discountPrice = subtotal * 0.05;
    }
    else if (subtotal >= 100) {
        discountPercentage = "(10%) :";
        discountPrice = subtotal * 0.10;
    }

    SST = round((subtotal - discountPrice) * 0.06 * 100) / 100.0;
    serviceTax = round((subtotal - discountPrice) * 0.06 * 100) / 100.0;
    totalPayable = subtotal - discountPrice + serviceTax + SST;
    totalPayable = round(totalPayable * 100) / 100.0;

    cout << endl;
    cout << left << setw(66) << "Subtotal : " << "RM" << right << setw(6) << subtotal << endl;
    cout << "Discount " << discountPercentage << right << setw(52) << "- RM" << right << setw(6) << discountPrice << endl;
    cout << left << setw(66) << "Service Charge (6%) :" << "RM" << right << setw(6) << serviceTax << endl;
    cout << left << setw(66) << "SST Tax (6%) :  " << "RM" << right << setw(6) << SST << endl;
    cout << left << setw(67) << "\nTotal Payable: " << "RM" << right << setw(6) << totalPayable << endl;

    //payment method selection
    do {
        cout << "\n\n(W = e-Wallet, C = Credit card, D = Debit card, A = Cash)" << endl;
        cout << "Select payment method: ";
        cin >> paymentMethod;

        // check valid payment method
        if (paymentMethod != 'W' && paymentMethod != 'C' && paymentMethod != 'D' && paymentMethod != 'A' && paymentMethod != 'w' && paymentMethod != 'c' && paymentMethod != 'd' && paymentMethod != 'a') {
            cout << "Invalid payment method. Please try again." << endl;
        }
    } while (paymentMethod != 'W' && paymentMethod != 'C' && paymentMethod != 'D' && paymentMethod != 'A' && paymentMethod != 'w' && paymentMethod != 'c' && paymentMethod != 'd' && paymentMethod != 'a');

    switch (paymentMethod) {
    case 'W': case'w':
        typePaymentMethod = "E-Wallet";
        break;
    case 'C': case'c':
        typePaymentMethod = "Credit Card";
        break;
    case 'D': case'd':
        typePaymentMethod = "Debit Card";
        break;
    case 'A': case'a':
        typePaymentMethod = "Cash";
        break;
    }

    double paymentAmount = 0.0;

    do {
        cout << "\nPlease enter you payment amount (Eg.Rm 120.80): RM ";
        cin.clear();
        cin >> paymentAmount;
        // check if the payment amount is enough
        if (paymentAmount < totalPayable) {
            cout << "Not enought payment amount. Please try again.";
        }

    } while (paymentAmount < totalPayable);


    // ------------------------------------------receipt page---------------------------------------------
    cout << "\n\nReceipt: \n" << endl;
    cout << right << setw(53) << "TARCIAN BOOKSTORE" << endl;
    cout << "\t\t\t\tNo. K666, Block K TARUMT," << endl;
    cout << right << setw(63) << "Jalan Genting Klang, Setapak, 53000" << endl;
    cout << right << setw(50) << "Kuala Lumpur." << endl;
    cout << right << setw(53) << "Tel : 03 - 1314520 " << endl;
    cout << "\n";

    cout << "Receipt No.RCP " << order_id << right << setw(55) << "Date: " << date << endl;

    cout << "---------------------------------------------------------------------------------" << endl;
    cout << fixed << setprecision(2);
    cout << left << setw(5) << "ID" << setw(35) << "Title" << setw(10) << "Qty" << setw(15) << "Price (RM)" << setw(15) << "Total (RM)" << endl;
    cout << "---------------------------------------------------------------------------------" << endl;

    for (int i = 0; i < cartCount; i++) {
        // find the corresponding book
        for (int j = 0; j < bookCount; j++) {
            if (bookcatalogue[j].id == cart[i].id) {
                Total = cart[i].quantity * bookcatalogue[j].price;

                cout << left << setw(5) << i + 1 << setw(36) << bookcatalogue[j].title << setw(10) << cart[i].quantity << setw(15) << bookcatalogue[j].price << setw(10) << Total << endl;
            }
        }
    }

    double change = 0.0;
    change = paymentAmount - totalPayable; // calculate change

    cout << right << setw(81) << "-----------------" << endl;
    cout << left << setw(66) << "Subtotal : " << "RM" << right << setw(6) << subtotal << endl;
    cout << left << "Discount " << discountPercentage << right << setw(52) << "- RM" << right << setw(6) << discountPrice << endl;
    cout << left << setw(66) << "Service Charge (6%) :" << "RM" << right << setw(6) << serviceTax << endl;
    cout << left << setw(66) << "SST Tax (6%) :  " << "RM" << right << setw(6) << SST << endl;

    cout << left << setw(67) << "\nTotal Payable: " << "RM" << right << setw(6) << totalPayable << endl;

    cout << right << setw(81) << "-----------------" << endl;
    cout << left << setw(68) << "\n\nPayment Method: " << typePaymentMethod << endl;
    cout << left << setw(66) << "Payment Amount: " << "RM" << paymentAmount << endl;

    cout << left << setw(66) << "Change: " << "RM" << change << endl;

    cout << "\nThank you for using TARCIAN BOOKSTORE! See you next time! >_<" << endl;


    // save the order details and book catalogue
    for (int i = 0; i < cartCount; i++) {
        for (int j = 0; j < bookCount; j++) {
            if (bookcatalogue[j].id == cart[i].id) {
                bookcatalogue[j].stock -= cart[i].quantity;
                order newOrder;
                newOrder.order_id = order_id;
                newOrder.username = username;
                newOrder.book_title = bookcatalogue[j].title;
                newOrder.book_price = bookcatalogue[j].price;
                newOrder.quantity = cart[i].quantity;
                newOrder.subtotal = subtotal;
                newOrder.total = totalPayable;
                newOrder.payment_method = typePaymentMethod;
                newOrder.order_date = date;

                order_detail.push_back(newOrder);
            }
        }
    }
    saveBook();
    saveOrder();
    // Clear the shopping cart after successful checkout
    clearShoppingCart();

    backToMenuPage();
    return;
}

// view order history
void orderHistory() {
    int i;
    bool found = false;
    cout << "\n==================== ORDER HISTORY ===================" << endl;
    cout << "\n";
    for (i = 0; i < order_detail.size(); i++) {
        if (order_detail[i].username == username) { // check if the customer has order before
            found = true;
            cout << "Order ID: " << order_detail[i].order_id << endl;
            cout << "Date    : " << order_detail[i].order_date << endl;
            cout << "Book    : " << order_detail[i].book_title << endl;
            cout << "Quantity: " << order_detail[i].quantity << endl;
            cout << "Price   : RM " << fixed << setprecision(2) << order_detail[i].book_price << endl;
            cout << "Subtotal: RM " << order_detail[i].subtotal << endl;
            cout << "Total   : RM " << order_detail[i].total << endl;
            cout << "Payment : " << order_detail[i].payment_method << endl;
            cout << "\n";
        }
    }
    if (!found) { //if no 
        cout << "You have no order yet" << endl;
    }
    backToMenuPage();
    return;
}