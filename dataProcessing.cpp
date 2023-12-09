#include <iostream>
#include <map>
#include <stdexcept>
using namespace std;


class InMemoryDB {
private:
    map<string, int> main;
    map<string, int> transactions;
    bool inTransaction;

public:
    InMemoryDB() {
        inTransaction = false;
    } 

    void begin_transaction() {
        if (inTransaction) {
            throw runtime_error("Transaction already in progress.");
        }
        inTransaction = true;
        transactions = main;
    }

    int get(string key) {
        if (inTransaction) {
            if (transactions.find(key) != transactions.end()) {
                return transactions[key];
            } else {
                return NULL;
            }
        } else {
            if (main.find(key) != main.end()) {
                return main[key];
            } else {
                return NULL;
            }
        }
    }

    void put(string key, int value) {
        if (!inTransaction) {
            throw runtime_error("No transaction in progress.");
        }
        transactions[key] = value;
    }

    void commit() {
        if (!inTransaction) {
            throw runtime_error("No transaction in progress.");
        }
        main = transactions;
        transactions.clear();
        inTransaction = false;
    }

    void rollback() {
        if (!inTransaction) {
            throw runtime_error("No transaction in progress.");
        }
        transactions.clear();
        inTransaction = false;
    }
};

int main() {
    InMemoryDB inmemoryDB;
    string input;

    while (true) {
        cin >> input;
        if (input == "BEGIN") {
            inmemoryDB.begin_transaction();
        } else if (input == "PUT") {
            string key;
            int value;
            cin >> key >> value;
            inmemoryDB.put(key, value);
        } else if (input == "GET") {
            string key;
            cin >> key;
            int value = inmemoryDB.get(key);
            cout << "VALUE = " << value << endl;
        } else if (input == "COMMIT") {
            inmemoryDB.commit();
        } else if (input == "ROLLBACK") {
            inmemoryDB.rollback();
        } 
    }
    return 0;
}
