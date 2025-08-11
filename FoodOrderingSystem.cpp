
#include <string>
#include <iomanip>
#include <iostream>
using namespace std;

const int menu_size = 8;
const int sizes = 3;
const int options = 4;

string fooditems[menu_size] = {
    "Burger", "Platters", "Pasta", "Fries", "Cakes", "Drinks", "Pizzas", "Appetizers"
};

int taxprices[menu_size] = { 30, 40, 25, 15, 15, 20, 10, 10 };

string suboptions[menu_size][options] = {
    {"chicken", "beef", "spicy&hot", "veggie"},
    { "chicken tikka", "malai boti", "cheese pizza", "paneer tikka"},
    { "alfredo pasta", "cheese pasta", "carbonara", "pesto pasta"},
    { "regular loaded fries", "extra cheese", "extra hot&spicy", "seasoned fries"},
    { "coffee", "pineapple", "chocolate", "vanilla"},
    { "cola", "fanta", "red bull", "sprite"},
    { "margarita", "pepperoni", "vegetarian", "bbq chicken"},
    { "onion rings", "mozzarella sticks", "spring rolls", "nachos"}
};

string sizeavailable[menu_size][sizes] = {
    { "regular", "mighty", "double patty"},
    { "small", "medium", "large"},
    { "regular plate", "plate for 2", "plate for 4"},
    { "regular", "medium", "large"},
    { "1 piece", "half", "full"},
    { "regular", "large", "jumbo"},
    { "personal", "medium", "large"},
    { "small", "large", "platter"}
};

int prices[menu_size][sizes] = {
    { 200, 350, 400},
    { 300, 700, 1000},
    { 350, 450, 600},
    { 100, 150, 200},
    { 200, 400, 600},
    { 100, 150, 200},
    { 500, 800, 1200},
    { 150, 300, 450}
};

void displaymenu() {
    cout << ">>>>>>>>>>>>>FOOD MENU<<<<<<<<<<<<<<" << endl;
    for (int i = 0; i < menu_size; i++) {
        cout << "\n" << i + 1 << "." << fooditems[i] << endl;
        cout << "\nOptions available:" << endl;
        for (int j = 0; j < options; j++) {
            cout << " -" << suboptions[i][j] << endl;
        }
        cout << "Size and price:" << endl;
        for (int j = 0; j < sizes; j++) {
            cout << " -" << sizeavailable[i][j] << "- Rs." << prices[i][j] << endl;
        }
    }
}

void placeorder(int itemnumbers[], int quantities[], string selectedsuboptions[], int sizechoices[], int maxorders, int& ordercount) {
    char choice;
    ordercount = 0;

    do {
        if (ordercount >= maxorders) {
            cout << "Maximum order limit reached!" << endl;
            break;
        }
        int itemnumber, quantity;
        cout << "\nEnter item number (1 to " << menu_size << "):" << endl;
        cin >> itemnumber;
        if (itemnumber < 1 || itemnumber > menu_size) {
            cout << "Invalid selection! Try again." << endl;
            continue;
        }
        cout << "\nAvailable suboptions for " << fooditems[itemnumber - 1] << ":" << endl;
        for (int j = 0; j < options; j++) {
            cout << j + 1 << ". " << suboptions[itemnumber - 1][j] << endl;
        }
        int suboptionIndex;
        cout << "Select a suboption (1 to " << options << "): ";
        cin >> suboptionIndex;
        if (suboptionIndex < 1 || suboptionIndex > options) {
            cout << "Invalid selection! Try again." << endl;
            continue;
        }
        cout << "Available sizes:" << endl;
        for (int j = 0; j < sizes; j++) {
            cout << j + 1 << " " << sizeavailable[itemnumber - 1][j] << endl;
        }
        int sizechoice;
        cout << "Select size (1 to " << sizes << "): ";
        cin >> sizechoice;
        if (sizechoice < 1 || sizechoice > sizes) {
            cout << "Invalid selection! Try again." << endl;
            continue;
        }
        cout << "\nEnter quantity: ";
        cin >> quantity;
        if (quantity <= 0 || quantity >= 8) {
            cout << "Please enter a valid quantity." << endl;
            continue;
        }
        itemnumbers[ordercount] = itemnumber;
        quantities[ordercount] = quantity;
        selectedsuboptions[ordercount] = suboptions[itemnumber - 1][suboptionIndex - 1];
        sizechoices[ordercount] = sizechoice;
        ordercount++;
        cout << "Do you want to order something else? (y/n): ";
        cin >> choice;
    } while (choice == 'y' || choice == 'Y');
}

void applyDiscount(int& totalbill, int ordercount) {
    if (ordercount <= 2) {
        cout << "Discount coupon is only available for orders greater than 3 items." << endl;
        return;
    }
    cout << "Congratulations! You are eligible for a discount coupon." << endl;
    cout << "Use coupon code: FOODHUB10 to get 10% off." << endl;
    string coupon;
    cout << "Do you want to apply the coupon? (y/n): ";
    char hascoupon;
    cin >> hascoupon;
    if (hascoupon == 'y' || hascoupon == 'Y') {
        cout << "Enter the coupon code: ";
        cin >> coupon;
        if (coupon == "FOODHUB10") {
            totalbill = totalbill - (totalbill * 0.10);
            cout << "Coupon applied! 10% discount added." << endl;
        }
        else {
            cout << "Invalid coupon code." << endl;
        }
    }
}

int main() {
    string username, password;
    string storedUsername = "foodlove";
    string storedPassword = "12345";
    bool isUserLoggedIn = false;

    cin.ignore();

    while (!isUserLoggedIn) {
        cout << "\n************************* Sign In to Your Account *************************\n";
        cout << "Enter Username: ";
        getline(cin, username);
        cout << "Enter Password: ";
        getline(cin, password);

        if (username == storedUsername && password == storedPassword) {
            cout << "\n************************* Sign In Successful! *************************\n";
            isUserLoggedIn = true;
        }
        else {
            cout << "\n Sign In Failed! Wrong Username or Password.\n";
            string createAccountInput;
            cout << "Do you want to create an account? (y/n): ";
            getline(cin, createAccountInput);
            char createAccount = createAccountInput.empty() ? 'n' : createAccountInput[0];

            if (createAccount == 'y' || createAccount == 'Y') {
                cout << "\n************************* Sign Up *************************\n";
                cout << "Enter New Username (min 8 characters): ";
                getline(cin, storedUsername);
                while (storedUsername.length() < 8) {
                    cout << "Username too short. Please enter at least 8 characters: ";
                    getline(cin, storedUsername);
                }
                cout << "Enter New Password (min 5 characters): ";
                getline(cin, storedPassword);
                while (storedPassword.length() < 5) {
                    cout << "Password too short. Please enter at least 5 characters: ";
                    getline(cin, storedPassword);
                }
                cout << "Account Created Successfully! Welcome to Food Hub!\n";
                isUserLoggedIn = true;
            }
            else {
                cout << "\n Warning!You can only place an order after creating an account.\n";
                cout << "Please try signing in again.\n";
            }
        }
    }

    cout << "\n-------------------- Delivery Details --------------------\n";
    cout << " * Please enter your delivery location: (^-^) \n";
    string location;
    cout << "   > Enter Location: ";
    getline(cin, location);
    string deliveryTime;
    cout << "   > Enter Desired Delivery Time (e.g., 2:30 PM): ";
    getline(cin, deliveryTime);

    displaymenu();

    const int maxorders = 4;
    int itemnumber[maxorders], quantities[maxorders], sizechoices[maxorders];
    string selectedsuboptions[maxorders];
    int ordercount = 0;

    placeorder(itemnumber, quantities, selectedsuboptions, sizechoices, maxorders, ordercount);

    int totalbill = 0;
    for (int i = 0; i < ordercount; i++) {
        int itemindex = itemnumber[i] - 1;
        int itemsize = sizechoices[i] - 1;
        int itemprice = prices[itemindex][itemsize];
        totalbill += (itemprice + taxprices[itemindex]) * quantities[i];
        cout << fooditems[itemindex] << " (" << selectedsuboptions[i] << ") - size " << sizeavailable[itemindex][itemsize] << " x " << quantities[i] << " = Rs." << ((itemprice + taxprices[itemindex]) * quantities[i]) << endl;
    }

    cout << "==================== ORDER SUMMARY ====================" << endl;
    cout << "| Item                | Quantity | Size    | Price   |\n";
    cout << "------------------------------------------------------\n";
    for (int i = 0; i < ordercount; i++) {
        int itemindex = itemnumber[i] - 1;
        int itemsize = sizechoices[i] - 1;
        int itemprice = prices[itemindex][itemsize];
        cout << "| " << left << setw(20) << fooditems[itemindex]
            << "| " << setw(8) << quantities[i]
            << "| " << setw(8) << sizeavailable[itemindex][itemsize]
            << "| Rs." << setw(7) << itemprice * quantities[i] << " |\n";
    }

    cout << "\nCHECKOUT:" << endl;
    applyDiscount(totalbill, ordercount);
    cout << "Total bill after applying discount: Rs." << totalbill << endl;
    if (totalbill <= 1500) {
        totalbill += 150;
        cout << "Delivery charges: 150 Rs." << endl;
    }
    else {

        cout << "Free delivery above 1500. No delivery charges applied." << endl;
    }

    cout << "\nYour order will be delivered to " << location << " at " << deliveryTime << ". Enjoy your order! (^)" << endl;
    cout << "==================== THANK YOU(^-*) FOR ORDERING FROM FOOD HUB =====================" << endl;

    return 0;
}
