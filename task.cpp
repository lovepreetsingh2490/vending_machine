#include <iostream>
#include <vector>
#include <iomanip>
#include <map>
using namespace std;

class Item {
public:
    string name;
    int code;
    double price;
    int stock;
    string category;

    Item(string n, int c, double p, int s, string cat) : name(n), code(c), price(p), stock(s), category(cat) {}
};

class VendingMachine {
private:
    vector<Item> items;
    double balance;

public:
    VendingMachine() {
        balance = 0.0;
        items.push_back(Item("Coke", 101, 1.50, 10, "Cold Drink"));
        items.push_back(Item("Pepsi", 102, 1.40, 8, "Cold Drink"));
        items.push_back(Item("Water", 103, 1.00, 15, "Cold Drink"));
        items.push_back(Item("Chips", 104, 1.20, 12, "Snack"));
        items.push_back(Item("Chocolate", 105, 2.00, 5, "Snack"));
        items.push_back(Item("Coffee", 106, 2.50, 7, "Hot Drink"));
        items.push_back(Item("Biscuits", 107, 1.80, 9, "Snack"));
    }

    void displayMenu() {
        cout << "\n---- Vending Machine Menu ----\n";
        cout << "Code  | Item       | Price  | Stock | Category\n";
        cout << "------------------------------------------------\n";
        for (auto &item : items) {
            cout << item.code << "  | " << setw(10) << item.name << " | $" << fixed << setprecision(2) << item.price << " | " << item.stock << " | " << item.category << "\n";
        }
    }

    void insertMoney(double amount) {
        if (amount > 0) {
            balance += amount;
            cout << "Money inserted: $" << fixed << setprecision(2) << amount << "\n";
            cout << "Current balance: $" << balance << "\n";
        } else {
            cout << "Invalid amount. Please insert money again.\n";
        }
    }

    void selectItem(int code) {
        for (auto &item : items) {
            if (item.code == code) {
                if (item.stock > 0) {
                    if (balance >= item.price) {
                        item.stock--;
                        balance -= item.price;
                        cout << "Dispensing " << item.name << "...\n";
                        cout << "Remaining balance: $" << balance << "\n";
                        suggestItem(item.name);
                        return;
                    } else {
                        cout << "Insufficient balance. Please add more money.\n";
                        return;
                    }
                } else {
                    cout << "Sorry, " << item.name << " is out of stock.\n";
                    return;
                }
            }
        }
        cout << "Invalid item code. Please try again.\n";
    }

    void returnChange() {
        if (balance > 0) {
            cout << "Returning change: $" << balance << "\n";
            balance = 0;
        } else {
            cout << "No change to return.\n";
        }
    }

    void suggestItem(string selectedItem) {
        map<string, string> suggestions = {
            {"Coffee", "Biscuits"},
            {"Coke", "Chips"},
            {"Pepsi", "Chocolate"},
            {"Water", "Nothing"}
        };
        if (suggestions.find(selectedItem) != suggestions.end()) {
            cout << "Suggestion: Would you like to buy " << suggestions[selectedItem] << " as well?\n";
        }
    }
};

int main() {
    VendingMachine vm;
    int choice;
    double money;

    while (true) {
        cout << "\n1. Display Menu\n2. Insert Money\n3. Select Item\n4. Return Change\n5. Exit\nEnter choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                vm.displayMenu();
                break;
            case 2:
                cout << "Enter amount to insert: ";
                cin >> money;
                vm.insertMoney(money);
                break;
            case 3:
                int code;
                cout << "Enter item code: ";
                cin >> code;
                vm.selectItem(code);
                break;
            case 4:
                vm.returnChange();
                break;
            case 5:
                cout << "Exiting program...\n";
                return 0;
            default:
                cout << "Invalid choice. Please try again.\n";
        }
    }
}
