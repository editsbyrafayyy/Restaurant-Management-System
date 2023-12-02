#include <iostream>
#include <string>
#include <fstream>
using namespace std;

const int max_orders = 50; // global var 

struct Orders { // using structures instead of implementing OOP
    int orderId;
    string customer_name;
    string ordered_items;
    int amount;
};

Orders orders[max_orders]; // Array to store orders
int order_nums = 0; // Number of orders 

void CreateOrder() { // function to create the order

    if (order_nums >= max_orders) { // to ensure that the orders don't exceed max 
        cout << "Max Orders Exceeded" << endl;
        return;
    }

    Orders newOrder; //declaring new structure 

    cout << "Enter The Order ID: ";
    cin >> newOrder.orderId;

    cout << "Enter The Customer Name: ";
    cin.ignore(); // needed for getline for some reason hmmm.
    getline(cin, newOrder.customer_name);

    cout << "Enter The Items Ordered: ";
    getline(cin, newOrder.ordered_items);

    cout << "Enter The Amount: ";
    cin >> newOrder.amount;

    orders[order_nums] = newOrder;
    order_nums++; // incrementing order nums

    cout << "Your Order Has Been Successfully Created LESSSGOOOO!" << endl;
}

void ModifyOrder() {
    int ID; // for comparing
    bool found = false;

    cout << "Enter order ID to modify: "; //modify using the order ID
    cin >> ID;

    for (int i = 0; i < order_nums; i++) { // using linear search to find the order
        if (orders[i].orderId == ID) {
            found = true;

            cout << "Enter The New Customer's Name: ";
            cin.ignore();
            getline(cin, orders[i].customer_name);

            cout << "Enter The New Item Ordered: ";
            getline(cin, orders[i].ordered_items);

            cout << "Enter The New Amount: ";
            cin >> orders[i].amount;

            cout << "Order Has Been Successfully Modified HEHE." << endl;
            break;
        }
    }

    if (found == 0) {
        cout << "This Order Does Not Exist." << endl;
    }
}

void CancelOrder() {
    int ID;
    bool found = false;

    cout << "Enter order ID to cancel: ";
    cin >> ID;

    for (int i = 0; i < order_nums; i++) {
        if (orders[i].orderId == ID) {
            found = true;

            for (int j = i; j < order_nums - 1; j++) { // Filling The Empty 
                orders[j] = orders[j + 1];
            }

            order_nums--;

            cout << "The Order Has Been Successfully Canceled MIMIMI." << endl;
            break;
        }
    }

    if (found == 0) {
        cout << "The Order Does Not Exist." << endl;
    }
}

void OutputOrders() {

    if (order_nums == 0) { // if no orders exist
        cout << "No Orders Are Available." << endl;
        return;
    }

    ofstream outputFile("orders.txt");

    if (!outputFile.is_open()) {
        cout << "Error opening file." << endl;
        return;
    }

    for (int i = 0; i < order_nums; i++) {
        outputFile << "Order ID: " << orders[i].orderId << "\n";
        outputFile << "Customer Name: " << orders[i].customer_name << "\n";
        outputFile << "Items Ordered: " << orders[i].ordered_items << "\n";
        outputFile << "Quantity: " << orders[i].amount << "\n\n";
    }

    outputFile.close();

    cout << "Orders written to file successfully." << endl;

    cout << "These Are All The Orders:" << endl;
    for (int i = 0; i < order_nums; i++) {

        cout << "----------------------" << endl;
        cout << "Order ID: " << orders[i].orderId << endl;
        cout << "Customer Name: " << orders[i].customer_name << endl;
        cout << "Items Ordered: " << orders[i].ordered_items << endl;
        cout << "Quantity: " << orders[i].amount << endl;
        cout << "----------------------" << endl;
    }
}

int main() {
    int option;

    do {
        cout<<"----------------------" << endl;

        cout<<"1. Create A New Order" << endl;
        cout<<"2. Modify A Existing Order" << endl;
        cout<<"3. Cancel An Order" << endl;
        cout<<"4. Show All The Orders" << endl;
        cout<<"5. Exit" << endl;

        cout<<"----------------------" << endl;

        cout<<"Enter your option: ";
        cin>>option;

         switch (option) {
            case 1:
                CreateOrder();
                break;
            case 2:
                ModifyOrder();
                break;
            case 3:
                CancelOrder();
                break;
            case 4:
                OutputOrders();
                break;
            case 5:
                cout << "Exiting program." << endl;
                break;
            default:
                cout << "Invalid option. Please try again." << endl;
                break;
        }

        cout << "\n";
    } while (option != 5);

    return 0;
}
