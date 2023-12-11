#include <iostream>
#include <string>
#include <fstream>
using namespace std;

const int max_orders = 50; // max orders
const int max_tables = 10; // max tables

struct Orders {
  int orderId;
  string customer_name;
  string items_ordered;
  int quantity;
  int price;
  int total_cost;
  int assignedTableId; // table assigned to the order
};

struct Table {
  int tableId;
  bool occupied;
  int orderId; // -1 if not occupied
};

Orders orders[max_orders]; //declaring a new var with the properties of Orders structure
int order_nums = 0; // number of orders

Table tables[max_tables];
int occupied_tables = 0; // number of occupied tables

void CreateOrder() {
  if (order_nums >= max_orders) {
    cout << "Max Orders Exceeded" << endl;
    return;
  }

  Orders new_order;

  // Order ID
  int input_id;
  do {
    cout << "Enter Order ID: ";
    cin >> input_id;
    if (cin.fail()) {
      cout << "Invalid input. Please enter a number: ";
      cin.clear();
      cin.ignore(INT_MAX, '\n');
    }
  } while (input_id <= 0);
  new_order.orderId = input_id;

  // Customer Name
  string customer_name;
    cout << "Enter Customer Name: ";
    getline(cin, new_order.customer_name);
  while (new_order.customer_name.empty()){
    getline(cin, new_order.customer_name);
      if (new_order.customer_name.empty()) {
      cout << "Customer name cannot be empty. Please enter a name: ";
    }
  }

  // Ordered Items
  string items_ordered;
  do {
    cout << "Enter Ordered Items: ";
    getline(cin, new_order.items_ordered);
    if (new_order.items_ordered.empty()) {
      cout << "Items ordered cannot be empty. Please enter items: ";
    }
  } while (new_order.items_ordered.empty());

  // Quantity
  int quantity;
  do {
    cout << "Enter Quantity: ";
    cin >> new_order.quantity;
    if (cin.fail()) {
      cout << "Invalid input. Please enter a positive number: ";
      cin.clear();
      cin.ignore(INT_MAX, '\n');
    } else if (new_order.quantity <= 0) {
      cout << "Quantity must be a positive number. Please try again: ";
    }
  } while (new_order.quantity <= 0);

  // Price
  double price;
  do {
    cout << "Enter Price: ";
    cin >> new_order.price;
    if (cin.fail()) {
      cout << "Invalid input. Please enter a positive number: ";
      cin.clear();
      cin.ignore(INT_MAX, '\n');
    } else if (new_order.price <= 0.0) {
      cout << "Price must be a positive number. Please try again: ";
    }
  } while (price <= 0.0);

  // Total Cost
  new_order.total_cost = new_order.price * new_order.quantity;

  // Find an available table
  int assignedTable = -1;
  for (int i = 0; i < max_tables; ++i) {
    if (!tables[i].occupied) {
      assignedTable = i;
      break;
    }
  }

  if (assignedTable == -1) {
    cout << "There Are No Tables Available Right Now, Business is Booming ;)" << endl;
    return;
  }

  // Update table and order
  tables[assignedTable].occupied = true;
  tables[assignedTable].orderId = new_order.orderId;
  new_order.assignedTableId = assignedTable;

  // Add to orders array and update counters
  orders[order_nums++] = new_order;
  occupied_tables++;

  // Write to file
  ofstream outputFile("orders.txt", ios::app);
  if (!outputFile.is_open()) {
    cout << "Error opening file." << endl;
    return;
  }

  outputFile << "Order ID: " << new_order.orderId << "\n";
  outputFile << "Customer Name: " << new_order.customer_name << "\n";
  outputFile << "Items Ordered: " << new_order.items_ordered << "\n";
  outputFile << "Quantity: " << new_order.quantity << "\n";
  outputFile << "Price: " << new_order.price << " Rs"<< "\n";
  outputFile << "Total Cost: " << new_order.total_cost << " Rs"<< "\n";
  outputFile << "Assigned Table: " << occupied_tables << "\n\n";
  outputFile.close();

  // Confirmation message
  cout << "Your Order Has Been Successfully Created! Table " << occupied_tables << " has been assigned." << endl;
}

void ModifyOrder() {
  int ID;
  bool found = false;

  cout << "Enter order ID to modify: ";
  string input_id;
  cin >> input_id;

  try {
    ID = stoi(input_id);
  } catch (const invalid_argument& e) {
    cout << "Invalid input. Please enter a valid integer." << endl;
    return;
  }

  // Create a temporary list to store updated orders
  Orders updatedOrders[max_orders];
  int updated_order_num = 0;

  for (int i = 0; i < order_nums; ++i) {
    if (orders[i].orderId == ID) {
      found = true;

      // Get updated information
      cout << endl;
      cout << "The Order Has Been Found. What Changes Do You Want to Make?: " << endl;
      cout << "1. Customer Name" << endl;
      cout << "2. Items Ordered" << endl;
      cout << "3. Quantity" << endl;

      int choice;
      cout << "Enter: ";
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
        getline(cin, orders[i].items_ordered);
        break;
      case 3:
        cout << "Enter new quantity: ";
        cin >> orders[i].quantity;
        orders[i].total_cost = orders[i].price * orders[i].quantity; // recalculate total cost
        break;
      default:
        cout << "Invalid choice." << endl;
        break;
      }
    }

    // Add orders to the temporary list
    updatedOrders[updated_order_num++] = orders[i];
  }

  // Rewrite the entire file with updated orders
  ofstream outputFile;
  outputFile.open("orders.txt", ios::out | ios::trunc);

  if (!outputFile.is_open()) {
    cout << "Error opening file." << endl;
    return;
  }

  for (int i = 0; i < updated_order_num; ++i) {
    outputFile << "Order ID: " << updatedOrders[i].orderId << "\n";
    outputFile << "Customer Name: " << updatedOrders[i].customer_name << "\n";
    outputFile << "Items Ordered: " << updatedOrders[i].items_ordered << "\n";
    outputFile << "Quantity: " << updatedOrders[i].quantity << "\n";
    outputFile << "Total Price in PKR: " << updatedOrders[i].total_cost << " Rs" << "\n";
    outputFile << "Assigned Table: " << occupied_tables << "\n\n";
  }

  outputFile.close();

  // Update order_nums to reflect the changes
  order_nums = updated_order_num;

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

  // Create a temporary list to store non-canceled orders
  Orders updatedOrders[max_orders];
  int updated_order_num = 0;

  for (int i = 0; i < order_nums; ++i) {
    if (orders[i].orderId != ID) {
      // Add non-canceled orders to the temporary list
      updatedOrders[updated_order_num++] = orders[i];
    } else {
      found = true;

      // Update table status
      tables[orders[i].assignedTableId].occupied = false;
      tables[orders[i].assignedTableId].orderId = -1;
    }
  }

  // Open the "orders.txt" file in truncate mode
  ofstream outputFile;
  outputFile.open("orders.txt", ios::trunc);

  if (!outputFile.is_open()) {
    cout << "Error opening file." << endl;
    return;
  }

  // Write only non-canceled orders to the file
  for (int i = 0; i < updated_order_num; ++i) {
    outputFile << "Order ID: " << updatedOrders[i].orderId << "\n";
    outputFile << "Customer Name: " << updatedOrders[i].customer_name << "\n";
    outputFile << "Items Ordered: " << updatedOrders[i].items_ordered << "\n";
    outputFile << "Quantity: " << updatedOrders[i].quantity << "\n";
    outputFile << "Total Price in PKR: " << updatedOrders[i].total_cost << " Rs" << "\n\n";
  }

  outputFile.close();

  // Update order_nums to reflect the changes
  order_nums = updated_order_num;

  cout << "The Order Has Been Successfully Canceled." << endl;

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

void CustomerSatisfaction(int customerId) { // for customer feedback, it is called in the generate invoice function
  string waiterName, taste, temp, speed, staff, clean;

  cout << "What was the name of the waiter?: ";
  cin.ignore();
  getline(cin, waiterName);

  cout << "Food taste (Good/Avg/Bad): ";
  cin.ignore();
  getline(cin, taste);

  cout << "Food temperature (Good/Avg/Bad): ";
  cin.ignore();
  getline(cin, temp);

  cout << "Speed of service (Good/Avg/Bad): ";
  cin.ignore();
  getline(cin, speed);

  cout << "Staff friendliness (Good/Avg/Bad): ";
  cin.ignore();
  getline(cin, staff);

  cout << "Cleanliness (Good/Avg/Bad): ";
  cin.ignore();
  getline(cin, clean);

  ofstream feedbackFile("customer_feedback.txt", ios::app); // Open file in append mode

  if (!feedbackFile) {
    cout << "Error opening feedback file." << endl;
    return;
  }

  // Write feedback data
  feedbackFile << "Customer ID: " << customerId << endl;
  feedbackFile << "--------------------------------------" << endl;
  feedbackFile << "Waiter Name: " << waiterName << endl;
  feedbackFile << "Taste: " << taste << endl;
  feedbackFile << "Temperature: " << temp << endl;
  feedbackFile << "Speed of Service: " << speed << endl;
  feedbackFile << "Staff Friendliness: " << staff << endl;
  feedbackFile << "Cleanliness: " << clean << endl;
  feedbackFile << "--------------------------------------" << endl;

  feedbackFile.close();

  cout << "Thank you for your feedback!" << endl;
}

void GenerateInvoice() {

  int ID;
  string fileName = "invoice.txt";

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
          outputFile << " - " << orders[i].items_ordered << endl;
        }

        outputFile << "---------------------------" << endl;
        outputFile << "Quantity: " << orders[i].quantity << endl;
        outputFile << "Price per item Rs: " << orders[i].price << endl;
        outputFile << "Total Cost Rs: " << orders[i].total_cost <<  endl;
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

void ExitProgram(){
  ofstream outputFile; // rewrting the data back to the file
  outputFile.open("orders.txt", ios::out);

  if (!outputFile.is_open()) {
    cout << "Error opening file." << endl;
    return;
  }

  // Write only non-empty orders to the file
  for (int i = 0; i < order_nums; i++) {
    outputFile << "Order ID: " << orders[i].orderId << "\n";
    outputFile << "Customer Name: " << orders[i].customer_name << "\n";
    outputFile << "Items Ordered: " << orders[i].items_ordered << "\n";
    outputFile << "Quantity: " << orders[i].quantity << "\n";
    outputFile << "Total Price in PKR: " << orders[i].total_cost << " Rs" << "\n";
    outputFile << "Assigned Table: " << occupied_tables << "\n\n";
  }
  outputFile.close();
  cout<<"Exiting Program..."<<endl;
  exit(0);
}

void SearchOrders() {

  string keyword;
  cout<<"Enter The Keyword That You Want To Find: ";
  cin>>keyword;

  bool found = false; 
  for (int i = 0; i < order_nums; ++i) {
    
    if (orders[i].customer_name.find(keyword) != string::npos || orders[i].items_ordered.find(keyword) != string::npos ||
        to_string(orders[i].total_cost).find(keyword) != string::npos) {
     
      found = true;
      
      cout << "Order ID: " << orders[i].orderId << endl;
      cout << "Customer Name: " << orders[i].customer_name << endl;
      cout << "Items Ordered: " << orders[i].items_ordered << endl;
      cout << "Quantity: " << orders[i].quantity << endl;
      cout << "Price: Rs" << orders[i].price << endl;
      cout << "Total Cost: Rs" << orders[i].total_cost << endl;
      cout << "Assigned Table: " << orders[i].assignedTableId << endl << endl;
    }
  }
  
  if (!found) {
    cout << "No orders found matching the keyword '" << keyword << "'." << endl;
    return;
  }
}

int main() {
    int option;

    string line;

      ifstream inputFile("orders.txt");
  if (inputFile) {
      while (!inputFile.eof()) {
        inputFile >> line;
      }
       inputFile.close();
  } 
    else {
      cout<<"Unable to Open The File"<<endl;
  }

    do {
        cout<<"----------------------" << endl;

        cout<<"1. Create A New Order" << endl;
        cout<<"2. Modify A Existing Order" << endl;
        cout<<"3. Cancel An Order" << endl;
        cout<<"4. Show All The Orders" << endl;
        cout<<"5. Print Invoice For an Order" << endl;
        cout<<"6. Search An Order" << endl;
        cout<<"7. Exit" << endl;

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
                SearchOrders();
                break;
            case 7:
                ExitProgram();
                break;
            default:
                cout << "Invalid option. Please try again." << endl;
                break;
        }

        cout << "\n";
    } while (option != 7);

    return 0;
}
