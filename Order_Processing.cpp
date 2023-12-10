#include <iostream>
#include <string>
#include <fstream>
using namespace std;

const int max_orders = 50; // global var 

struct Orders { // using structures instead of implementing OOP
    int orderId;
    string customer_name;
    string ordered_items;
    int quantity;
    int price;
    int total_cost;
};

Orders orders[max_orders]; // Array to store orders
int order_nums = 0; // Number of orders 

void CreateOrder() { // function to create the order

    if (order_nums >= max_orders) { // to ensure that the orders don't exceed max 
        cout << "Max Orders Exceeded" << endl;
        return;
    }

    Orders new_order; //declaring new structure var 

    cout << "Enter The Order ID: ";
    string input_id;
    cin >> input_id;

    new_order.orderId = stoi(input_id);

    cout << "Enter The Customer Name: ";
    cin.ignore(); // needed for getline for some reason hmmm.
    getline(cin, new_order.customer_name);

    cout << "Enter The Items Ordered: ";
    getline(cin, new_order.ordered_items);

    cout << "Enter The quantity: ";
    cin >> new_order.quantity;

    cout << "Enter The Price: ";
    cin >> new_order.price;

    new_order.total_cost = new_order.price * new_order.quantity;

    orders[order_nums++] = new_order;
    // order_nums++; // incrementing order nums

    cout << "Your Order Has Been Successfully Created LESSSGOOOO!" << endl;

    //adding the order to a file

        if (order_nums == 0) { // if no orders exist
        cout << "No Orders Are Available." << endl;
        return;
    }

    ofstream outputFile;
    outputFile.open("orders.txt", ios::app);

    if (!outputFile.is_open()) {
        cout << "Error opening file." << endl;
        return;
    }

    for (int i = order_nums - 1; i < order_nums; i++) {
        outputFile << "Order ID: " << orders[i].orderId << "\n";
        outputFile << "Customer Name: " << orders[i].customer_name << "\n";
        outputFile << "Items Ordered: " << orders[i].ordered_items << "\n";
        outputFile << "Quantity: " << orders[i].quantity << "\n";
        outputFile << "Total Price in PKR: " << orders[i].total_cost <<" Rs"<< "\n\n";
    }

    outputFile.close();

    cout << "Orders written to file successfully" << endl;
}

void ModifyOrder() {
  int ID;
  bool found = false;

  cout << "Enter customer ID to modify order: ";
  string input_id;
  cin >> input_id;

  try {
    ID = stoi(input_id);
  } catch (const std::invalid_argument& e) {
    cout << "Invalid input. Please enter a valid integer." << endl;
    return;
  }

  ofstream outputFile;
  outputFile.open("orders.txt", ios::out | ios::ate);

  if (!outputFile.is_open()) {
    cout << "Error opening file." << endl;
    return;
  }

  for (int i = 0; i < order_nums; i++) {
    if (orders[i].orderId == ID) {
      found = true;

      cout<<endl;
      cout << "The Order Has Been Found. What Changes Do You Want to Make?: " << endl;
      cout << "1. Customer Name" << endl;
      cout << "2. Items Ordered" << endl;
      cout << "3. Quantity" << endl;

      int choice;
      cout<<"Enter: ";
      cin >> choice;

      switch (choice) {
        case 1:
          cout << "Enter new customer name: ";
          cin.ignore();
          getline(cin, orders[i].customer_name);
          break;
        case 2:
          cout << "Enter new items ordered: ";
          cin.ignore();
          getline(cin, orders[i].ordered_items);
          break;
        case 3:
          cout << "Enter new quantity: ";
          cin >> orders[i].quantity;
          break;
        default:
          cout << "Invalid choice." << endl;
          break;
      }
    }

    outputFile << "Order ID: " << orders[i].orderId << "\n";
    outputFile << "Customer Name: " << orders[i].customer_name << "\n";
    outputFile << "Items Ordered: " << orders[i].ordered_items << "\n";
    outputFile << "Quantity: " << orders[i].quantity << "\n";
    outputFile << "Total Price in PKR: " << orders[i].total_cost << " Rs" << "\n\n";
  }

  outputFile.close();
  cout << "Modifications Have Been Made Successfully" << endl;

  if (!found) {
    cout << "Order not found." << endl;
  }
}

void CancelOrder() {
  int ID;
  bool found = false;

  cout << "Enter order ID to cancel: ";
  cin >> ID;

  for (int i = 0; i < order_nums; i++) { //basic searching again
    if (orders[i].orderId == ID) {
      found = true;

      if (i == 0) { // the first order was bugging so had to make a case for it
        orders[i] = Orders{};
        order_nums--;
        i++;
      } else {

        for (int j = i; j < order_nums; j++) { //filling the gaps in a nutshell
          orders[j - 1] = orders[j];
        }

        order_nums--;
      }

      break;
    }
  }

  ofstream outputFile; // rewrting the data back to the file
  outputFile.open("orders.txt", ios::trunc);

  if (!outputFile.is_open()) {
    cout << "Error opening file." << endl;
    return;
  }

  // Write only non-empty orders to the file
  for (int i = 0; i < order_nums; i++) {
    if (!orders[i].orderId) continue; // skip empty order

    outputFile << "Order ID: " << orders[i].orderId << "\n";
    outputFile << "Customer Name: " << orders[i].customer_name << "\n";
    outputFile << "Items Ordered: " << orders[i].ordered_items << "\n";
    outputFile << "Quantity: " << orders[i].quantity << "\n";
    outputFile << "Total Price in PKR: " << orders[i].total_cost << " Rs" << "\n\n";
  }

  outputFile.close();

  cout << "The Order Has Been Successfully Canceled MIMIMI." << endl;

  if (!found) {
    cout << "The Order Does Not Exist" << endl;
  }
}

void OutputOrders() { // this for testing purposes only

    ifstream inputFile;
    inputFile.open("orders.txt");

    if (inputFile.is_open()) {
        string line;
        while (getline(inputFile, line)) {
                cout << line << endl;
        }
        inputFile.close();
    } else {
        cout << "Failed to open the file." << endl;
    }

    cout << "These Are All The Orders" << endl;
}

void CustomerSatisfaction(int customerId) {
    string waiter_name, taste,temp,speed,staff,clean;

    cout << "What was The Name of The Waiter?: ";
    cin.ignore();
    getline(cin, waiter_name);

    cout << "Food Taste (Highly Satisfied/Satisfied/Neutral/Dissatisifed): ";
    cin.ignore();
    getline(cin, taste);

    cout << "Food Temperature (Highly Satisfied/Satisfied/Neutral/Dissatisifed): ";
    cin.ignore();
    getline(cin, temp);

    cout << "Speed of Service (Highly Satisfied/Satisfied/Neutral/Dissatisifed): ";
    cin.ignore();
    getline(cin, speed);

    cout << "Staff Friendliness (Highly Satisfied/Satisfied/Neutral/Dissatisifed): ";
    cin.ignore();
    getline(cin, staff);

    cout << "Cleanliness (Highly Satisfied/Satisfied/Neutral/Dissatisifed): ";
    cin.ignore();
    getline(cin, clean);

    ofstream feedbackFile("customer_feedback.txt", ios::app); // saving the feedback using append
    if (feedbackFile) {
        feedbackFile << "Customer ID: " << customerId << endl;
        feedbackFile << "--------------------------------------" << endl;
        feedbackFile << "Waiter Name: " << waiter_name << endl;
        feedbackFile << "Taste: " << taste << endl;
        feedbackFile << "Temperature: " << temp << endl;
        feedbackFile << "Speed of Service: " << speed << endl;
        feedbackFile << "Staff Friendliness: " << staff << endl;
        feedbackFile << "--------------------------------------" << endl;
        feedbackFile.close();
        cout << "Thank you for your feedback!" << endl;
    } else {
        cout << "Error saving feedback." << endl;
    }
}

void GenerateInvoice() {
  int ID;

  cout << "Enter the order ID for which you want to generate an invoice: ";
  cin >> ID;

  bool found = false;

  for (int i = 0; i < order_nums; i++) {
    if (orders[i].orderId == ID) { // basic searching using ID again
      found = true;


      char saveInvoice;
      cout << "Do you want to save the invoice for order ID " << ID << " to a file? (Y/N): ";
      cin >> saveInvoice;

      if (saveInvoice == 'y' || saveInvoice == 'Y') {
        string fileName;
        cout << "Enter the filename to save the invoice: ";
        cin >> fileName;

        ofstream outputFile(fileName);

        if (!outputFile.is_open()) {
          cout << "Error opening file." << endl;
          return;
        }

        outputFile << "---------------------------" << endl; // invoice in the file
        outputFile << "Order ID: " << orders[i].orderId << endl;
        outputFile << "Customer Name: " << orders[i].customer_name << endl;
        outputFile << "---------------------------" << endl;
        outputFile << "Ordered Items:" << endl;

        for (int j = 0; j < orders[i].quantity; j++) {
          outputFile << " - " << orders[i].ordered_items << endl;
        }

        outputFile << "---------------------------" << endl;
        outputFile << "Quantity: " << orders[i].quantity << endl;
        outputFile << "Price per item: " << orders[i].price << " Rs" << endl;
        outputFile << "Total Cost: " << orders[i].total_cost << " Rs" << endl;
        outputFile << "---------------------------" << endl;

        outputFile.close();
      }
      break;
    }
  }

  if (!found) {
    cout << "Order with ID " << ID << " not found." << endl;
    return;
  }

  CustomerSatisfaction(ID);
}

int main() {
    int option;

    do {
        cout<<"----------------------" << endl;

        cout<<"1. Create A New Order" << endl;
        cout<<"2. Modify A Existing Order" << endl;
        cout<<"3. Cancel An Order" << endl;
        cout<<"4. Show All The Orders" << endl;
        cout<<"5. Print Invoice For an Order" << endl;
        cout<<"6. Exit" << endl;

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
                GenerateInvoice();
                break;
            case 6:
                cout << "Exiting program." << endl;
                break;
            default:
                cout << "Invalid option. Please try again." << endl;
                break;
        }

        cout << "\n";
    } while (option != 6);

    return 0;
}
