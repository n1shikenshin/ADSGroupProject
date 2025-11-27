#include <iostream>
#include <vector>
#include <string>
#include <chrono>
using namespace std;
using namespace std::chrono;

// Structure to store price + store
struct Item {
    string store;
    double price;
};

int main() {
    vector<Item> prices;
    int choice;

    while (true) {
        cout << "\n==== BASELINE PRICE TRACKER (ARRAY) ====\n";
        cout << "1. Enter Price & Store\n";
        cout << "2. Show Minimum Price\n";
        cout << "3. Show Maximum Price\n";
        cout << "4. Exit\n";
        cout << "Choose: ";
        cin >> choice;

        if (choice == 1) {
            string store;
            double price;

            cout << "Enter store name: ";
            cin >> store;
            cout << "Enter price: ";
            cin >> price;

            // Time insertion (array - vector push_back)
            auto start = high_resolution_clock::now();
            prices.push_back({store, price});
            auto end = high_resolution_clock::now();

            cout << "Inserted (" 
                << duration_cast<microseconds>(end - start).count()
                << " us)\n";
        }

        else if (choice == 2) {
            if (prices.empty()) {
                cout << "No data yet!\n";
                continue;
            }

            auto start = high_resolution_clock::now();

            // Linear Scan (slow)
            Item minItem = prices[0];
            for (const auto &item : prices) {
                if (item.price < minItem.price)
                    minItem = item;
            }

            auto end = high_resolution_clock::now();

            cout << "Minimum Price: " << minItem.store 
                 << " RM" << minItem.price
                 << " (" << duration_cast<microseconds>(end - start).count()
                 << " us)\n";
        }

        else if (choice == 3) {
            if (prices.empty()) {
                cout << "No data yet!\n";
                continue;
            }

            auto start = high_resolution_clock::now();

            // Linear Scan (slow)
            Item maxItem = prices[0];
            for (const auto &item : prices) {
                if (item.price > maxItem.price)
                    maxItem = item;
            }

            auto end = high_resolution_clock::now();

            cout << "Maximum Price: " << maxItem.store 
                 << " RM" << maxItem.price
                 << " (" << duration_cast<microseconds>(end - start).count()
                 << " us)\n";
        }

        else if (choice == 4) {
            cout << "Exiting program...\n";
            break;
        }

        else {
            cout << "Invalid choice! Try again.\n";
        }
    }

    return 0;
}

