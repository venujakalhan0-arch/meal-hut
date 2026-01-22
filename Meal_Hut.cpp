#include <iostream>
#include <fstream>
#include <string>
#include <iomanip>

using namespace std;

const int MAX_ITEMS = 50;
const string MENU_FILE = "menu.txt";

// Structure to represent a menu item
struct MenuItem {
    int itemNumber;
    string itemName;
    double price;
};

// Function prototypes
void getData(MenuItem menuList[], int &count);
void showMenu(const MenuItem menuList[], int count);
void printCheck(const MenuItem menuList[], int count);
void saveData(const MenuItem menuList[], int count);
void addItem(MenuItem menuList[], int &count);
void displayWelcomeMessage();
int getUserChoice();

int main() {
    MenuItem menuList[MAX_ITEMS];
    int itemCount = 0;
    getData(menuList, itemCount);

    int choice;
    displayWelcomeMessage();

    do {
        choice = getUserChoice();

        switch (choice) {
            case 1:
                showMenu(menuList, itemCount);
                break;
            case 2:
                printCheck(menuList, itemCount);
                break;
            case 3:
                addItem(menuList, itemCount);
                break;
            case 4:
                saveData(menuList, itemCount);
                break;
            case 5:
                cout << "\nThank you for choosing Meal Hut! Have a fantastic day!\n";
                break;
            default:
                cout << "Oops! That's not valid option. Please choose between 1 and 5.\n";
        }
    } while (choice != 5);

    return 0;
}

// Function to load initial data into the menu list
void getData(MenuItem menuList[], int &count) {
    menuList[count++] = {111, "Plain Egg", 1.45};
    menuList[count++] = {112, "Bacon and Egg", 2.45};
    menuList[count++] = {113, "Muffin", 0.99};
    menuList[count++] = {114, "French Toast", 1.99};
    menuList[count++] = {115, "Fruit Basket", 2.49};
    menuList[count++] = {116, "Cereal", 0.69};
    menuList[count++] = {117, "Coffee", 0.50};
    menuList[count++] = {118, "Tea", 0.75};
}

// Function to display a welcome message
void displayWelcomeMessage() {
    cout << "\n******** Welcome to Meal Hut *********\n";
    cout << "Enjoy a hearty breakfast with us!\n";
}

// Function to get user's menu choice with validation
int getUserChoice() {
    int choice;
    cout << "\nPlease select an option:\n";
    cout << "1. Show Menu\n";
    cout << "2. Print Check\n";
    cout << "3. Add Item to Menu\n";
    cout << "4. Save Menu Data\n";
    cout << "5. Exit\n";
    cout << "Enter your choice: ";
    cin >> choice;

    // Validate input
    while (cin.fail()) {
        cin.clear();
        cin.ignore(1000, '\n');
        cout << "Invalid input. Please enter a number between 1 and 5: ";
        cin >> choice;
    }

    return choice;
}

// Function to display the menu
void showMenu(const MenuItem menuList[], int count) {
    cout << "\n******** Meal Hut Menu ********\n";
    cout << left << setw(10) << "Item No" << setw(20) << "Menu Item" << setw(10) << "Price\n";
    cout << "------------------------------------------\n";
    for (int i = 0; i < count; ++i) {
        cout << left << setw(10) << menuList[i].itemNumber
             << setw(20) << menuList[i].itemName
             << "$" << fixed << setprecision(2) << menuList[i].price << endl;
    }
}

// Function to calculate and print the bill
void printCheck(const MenuItem menuList[], int count) {
    int itemNumber;
    double total = 0.0;
    char choice;

    cout << "\nEnter the item numbers for your order (Enter 0 to complete your selection):\n";
    do {
        cout << "Item Number: ";
        cin >> itemNumber;

        // Validate input
        while (cin.fail()) {
            cin.clear();
            cin.ignore(1000, '\n');
            cout << "Invalid input. Please enter a valid item number: ";
            cin >> itemNumber;
        }

        if (itemNumber == 0) break;

        bool found = false;
        for (int i = 0; i < count; ++i) {
            if (menuList[i].itemNumber == itemNumber) {
                total += menuList[i].price;
                cout << "Added: " << menuList[i].itemName << " - $" << menuList[i].price << endl;
                found = true;
                break;
            }
        }

        if (!found) {
            cout << "Sorry, no such item on the menu. Try again.\n";
        }

        cout << "Would you like to add another item? (y/n): ";
        cin >> choice;
    } while (choice == 'y' || choice == 'Y');

    double tax = total * 0.05;
    double amountDue = total + tax;

    cout << "\n******** Meal Hut Bill ********\n";
    cout << left << setw(20) << "Total:" << "$" << fixed << setprecision(2) << total << endl;
    cout << left << setw(20) << "Tax (5%):" << "$" << tax << endl;
    cout << left << setw(20) << "Amount Due:" << "$" << amountDue << endl;
}

// Function to save the menu data to a file
void saveData(const MenuItem menuList[], int count) {
    ofstream outFile(MENU_FILE.c_str());
    if (outFile.is_open()) {
        for (int i = 0; i < count; ++i) {
            outFile << menuList[i].itemNumber << " " << menuList[i].itemName << "; " << menuList[i].price << endl;
        }
        outFile.close();
        cout << "Menu data has been successfully saved to " << MENU_FILE << ".\n";
    } else {
        cout << "Error: Unable to save the the menu data to a file.\n";
    }
}

// Function to add a new item to the menu
void addItem(MenuItem menuList[], int &count) {
    if (count >= MAX_ITEMS) {
        cout << "The menu is full. No more items can be added.\n";
        return;
    }

    MenuItem newItem;
    cout << "Enter the unique item number: ";
    cin >> newItem.itemNumber;
    cin.ignore(); // To clear the newline character from input buffer
    cout << "Enter the item name: ";
    getline(cin, newItem.itemName);
    cout << "Enter the price of the item: ";
    cin >> newItem.price;

    menuList[count++] = newItem;
    cout << "New item successfully added to the menu.\n";
}

