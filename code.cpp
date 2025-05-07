#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <sstream>
using namespace std;

string formatMoney(long long amount) {
    stringstream ss;
    ss << amount;
    string num = ss.str();
    int insertPosition = num.length() - 3;

    while (insertPosition > 0) {
        num.insert(insertPosition, ",");
        insertPosition -= 3;
    }

    return num;
}

class Account {
private:
    string AccountID;
    string AccountOwner;
    long long Balance;

public:
    Account(string id, string name, long long bal) {
        AccountID = id;
        AccountOwner = name;
        Balance = bal;
    }

    bool deposit(long long amount) {
        if (amount > 0) {
            Balance += amount;
            cout << "Deposited " << formatMoney(amount) << " VND into account.\n";
            cout << "Deposit successful! New balance: " << formatMoney(Balance) << " VND\n";
            return true;
        }
        cout << "Deposit failed! The amount must be greater than 0.\n";
        return false;
    }

    bool withdraw(long long amount) {
        if (amount > 0 && amount <= Balance) {
            Balance -= amount;
            cout << "Withdraw successful! New balance: " << formatMoney(Balance) << " VND\n";
            return true;
        }
        cout << "Withdraw failed! Insufficient funds or invalid amount.\n";
        return false;
    }

    bool transfer(Account& target, long long amount) {
        if (amount > 0 && amount <= Balance) {
            Balance -= amount;
            target.Balance += amount;
            cout << "Transfer successful! New balance: " << formatMoney(Balance) << " VND\n";
            return true;
        }
        cout << "Transfer failed! Insufficient funds or invalid amount.\n";
        return false;
    }

    void ShowInfo() const {
        cout << "ID: " << AccountID << "\nName: " << AccountOwner;
        cout << "\nBalance: " << formatMoney(Balance) << " VND\n";
    }

    string getID() const {
        return AccountID;
    }
};

Account* findAccountByID(vector<Account>& accounts, const string& id) {
    for (auto& acc : accounts) {
        if (acc.getID() == id) {
            return &acc;
        }
    }
    return nullptr;
}

int main() {
    vector<Account> accounts;
    accounts.push_back(Account("001", "A", 10000000));
    accounts.push_back(Account("002", "B", 5000000));

    int choice;
    long long amount;
    string id;

    do {
        cout << "\n========= MENU =========\n";
        cout << "1. Deposit\n";
        cout << "2. Withdraw\n";
        cout << "3. Show Balance\n";
        cout << "4. Transfer\n";
        cout << "5. Show Account Info\n";
        cout << "6. Show All Accounts\n";
        cout << "0. Exit\n";
        cout << "Choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                cout << "Enter account ID to deposit to: ";
                cin >> id;
                if (Account* acc = findAccountByID(accounts, id)) {
                    cout << "Enter amount to deposit: ";
                    cin >> amount;
                    acc->deposit(amount);
                } else {
                    cout << "Account not found.\n";
                }
                break;

            case 2:
                cout << "Enter account ID to withdraw from: ";
                cin >> id;
                if (Account* acc = findAccountByID(accounts, id)) {
                    cout << "Enter amount to withdraw: ";
                    cin >> amount;
                    acc->withdraw(amount);
                } else {
                    cout << "Account not found.\n";
                }
                break;

            case 3:
                cout << "Enter account ID to show info: ";
                cin >> id;
                if (Account* acc = findAccountByID(accounts, id)) {
                    acc->ShowInfo();
                } else {
                    cout << "Account not found.\n";
                }
                break;
            case 4:
                cout << "Enter account ID to transfer from: ";
                cin >> id;
                if (Account* acc = findAccountByID(accounts, id)) {
                    string targetID;
                    cout << "Enter target account ID: ";
                    cin >> targetID;
                    Account* targetAcc = findAccountByID(accounts, targetID);
                    if (targetAcc) {
                        cout << "Enter amount to transfer: ";
                        cin >> amount;
                        acc->transfer(*targetAcc, amount);
                    } else {
                        cout << "Target account not found.\n";
                    }
                } else {
                    cout << "Account not found.\n";
                }
                break;
            
            case 5: 
                cout << "Enter account ID to show info: ";
                cin >> id;
                if (Account* acc = findAccountByID(accounts, id)) {
                    acc->ShowInfo();
                } else {
                    cout << "Account not found.\n";
                }
                break;

            case 6: 
                cout << "All accounts:\n";
                for (const auto& acc : accounts) {
                    acc.ShowInfo();
                }
                break;

            case 0:
                cout << "Exit.\n";
                break;

            default:
                cout << "Choose another choice!\n";
        }
    } while (choice != 0);

    return 0;
}
