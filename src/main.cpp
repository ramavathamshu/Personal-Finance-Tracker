#include <iostream>
#include <iomanip>
#include <fstream>
#include <string>
using namespace std;

struct Transaction {
    string date;      // Format: YYYY-MM-DD
    string type;      // "income" or "expense"
    string category;
    double amount;
};

const int MAX = 100;
Transaction transactions[MAX];
int countT = 0;

void addTransaction() {
    if (countT >= MAX) {
        cout << "Transaction limit reached!\n";
        return;
    }
    cout << "Enter date (YYYY-MM-DD): ";
    cin >> transactions[countT].date;
    cout << "Enter type (income/expense): ";
    cin >> transactions[countT].type;
    cout << "Enter category: ";
    cin >> transactions[countT].category;
    cout << "Enter amount: ";
    cin >> transactions[countT].amount;
    countT++;
}

void viewTransactions() {
    cout << left << setw(12) << "Date" 
         << setw(10) << "Type" 
         << setw(15) << "Category" 
         << setw(10) << "Amount" << "\n";
    cout << "-------------------------------------------------\n";
    for (int i = 0; i < countT; i++) {
        cout << left << setw(12) << transactions[i].date
             << setw(10) << transactions[i].type
             << setw(15) << transactions[i].category
             << "$" << setw(9) << transactions[i].amount << "\n";
    }
}

void filterExpensesOver100() {
    cout << "Expenses over $100:\n";
    for (int i = 0; i < countT; i++) {
        if (transactions[i].type == "expense" && transactions[i].amount > 100) {
            cout << transactions[i].date << " | " 
                 << transactions[i].category << " | $" 
                 << transactions[i].amount << "\n";
        }
    }
}

void sortByAmount() {
    for (int i = 0; i < countT - 1; i++) {
        for (int j = i + 1; j < countT; j++) {
            if (transactions[i].amount > transactions[j].amount) {
                swap(transactions[i], transactions[j]);
            }
        }
    }
    cout << "Transactions sorted by amount!\n";
}

void saveToFile() {
    ofstream file("finance.txt");
    for (int i = 0; i < countT; i++) {
        file << transactions[i].date << " "
             << transactions[i].type << " "
             << transactions[i].category << " "
             << transactions[i].amount << "\n";
    }
    file.close();
    cout << "Data saved to finance.txt\n";
}

void loadFromFile() {
    ifstream file("finance.txt");
    countT = 0;
    while (file >> transactions[countT].date 
                >> transactions[countT].type 
                >> transactions[countT].category 
                >> transactions[countT].amount) {
        countT++;
    }
    file.close();
    cout << "Data loaded from finance.txt\n";
}

void asciiBarChart() {
    double monthly[13] = {0}; // monthly totals
    for (int i = 0; i < countT; i++) {
        if (transactions[i].type == "expense") {
            int month = stoi(transactions[i].date.substr(5, 2));
            monthly[month] += transactions[i].amount;
        }
    }
    cout << "\nMonthly Spending Chart:\n";
    for (int m = 1; m <= 12; m++) {
        cout << setw(2) << m << " | ";
        int bars = (int)(monthly[m] / 10); // scale
        for (int b = 0; b < bars; b++) cout << "#";
        cout << " $" << monthly[m] << "\n";
    }
}

int main() {
    int choice;
    loadFromFile();
    do {
        cout << "\n=== Personal Finance Tracker ===\n";
        cout << "1. Add Transaction\n";
        cout << "2. View Transactions\n";
        cout << "3. Filter Expenses > $100\n";
        cout << "4. Sort by Amount\n";
        cout << "5. Save Data\n";
        cout << "6. Show ASCII Bar Chart\n";
        cout << "0. Exit\n";
        cout << "Choose: ";
        cin >> choice;

        switch (choice) {
            case 1: addTransaction(); break;
            case 2: viewTransactions(); break;
            case 3: filterExpensesOver100(); break;
            case 4: sortByAmount(); break;
            case 5: saveToFile(); break;
            case 6: asciiBarChart(); break;
            case 0: saveToFile(); cout << "Goodbye!\n"; break;
            default: cout << "Invalid choice!\n";
        }
    } while (choice != 0);
    return 0;
}
