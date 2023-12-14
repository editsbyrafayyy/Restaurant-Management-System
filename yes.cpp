// this is the copy of my original code which I made changes to

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

void CreateOrder() {
  // Open output file
  ofstream outputFile("orders.txt", ios::app);
  if (!outputFile.is_open()) {
    cout << "Error opening file." << endl;
    return;
  }

  // Check order limit
  if (order_nums >= max_orders) {
    cout << "Max Orders Exceeded" << endl;
    return;
  }

  // Create new order
  Orders new_order;
  new_order.orderId = order_nums + 1;
  order_nums++;

  int input_id;
  do { // it is for ID validation 
    cout << "Enter Order ID: ";
    cin >> input_id;
    if (cin.fail()) { // cin.fail here returns true if a letter, comma or special char is entered, so just to make sure the correct input is taken
      cout << "Invalid input. Please enter a number: ";
      cin.clear(); // (not compul but clears the buffer of the "error state" so an input can be taken again)
      cin.ignore(); // makes sures that the "wrong input" is removed from the buffer, makes sure koi problem na ho when taking input again)
    }
  } while (input_id <= 0);
  new_order.orderId = input_id;

  // Get customer name and validate
  getline(cin, new_order.customer_name);
  while (new_order.customer_name.empty()) {
    cout << "Please enter a name: ";
    getline(cin, new_order.customer_name);
  }

  // Initialize variables
  vector<int> orderedItems;
  new_order.quantity = 1; // Default quantity

  // Loop for entering item indexes
  do {
  cout << "Enter Item Number (1-20, 0 to finish): ";
  int itemIndex;
  while (!(cin >> itemIndex) || itemIndex < 0 || itemIndex > 20) {
    cout << "Invalid input. Please enter a number between 1 and 20: ";
    cin.clear();
    cin.ignore();
  }

  if (itemIndex == 0) break; // exit loop on 0

  // Ask for quantity for this item
  cout << "Enter Quantity: ";
  while (!(cin >> new_order.quantity) || new_order.quantity <= 0) {
    cout << "Invalid input. Please enter a positive number: ";
    cin.clear();
    cin.ignore();
  }

  orderedItems.push_back(itemIndex - 1); // add valid index
} while (true);

  // Initialize total price and iterate through ordered items
  double totalPrice = 0.0;
  for (int itemIndex : orderedItems) {
    // Check if valid index
    if (itemIndex < 0 || itemIndex >= loadedMenu.size()) {
      cout << "Error: Invalid item index." << endl;
      outputFile.close();
      return; // Order creation failed
    }

    // Add price based on item index and quantity
    totalPrice += loadedMenu[itemIndex].getPrice() * new_order.quantity;
  }

  // Set total cost
  new_order.total_cost = totalPrice;

  // Assign table and update tables array
  int assignedTable = -1;
  for (int i = 0; i < max_tables && assignedTable == -1; i++) {
    if (!tables[i].orderId) {
      assignedTable = i;
      tables[i].orderId = new_order.orderId;
      new_order.assignedTableId = assignedTable;
    }
  }

  // Handle no available tables
  if (assignedTable == -1) {
    cout << "There Are No Tables Available Right Now, Business is Booming ;)" << endl;
    outputFile.close();
    return;
  }

  // Add order to orders array and save to file
  orders[order_nums++] = new_order;

  outputFile << "Order ID: " << new_order.orderId << "\n";
  outputFile << "Customer Name: " << new_order.customer_name << "\n";
  outputFile << "Items Ordered: ";
  for (int itemIndex : orderedItems) {
    const MenuItem& item = loadedMenu[itemIndex]; 
    outputFile << item.getName();
  }
  outputFile.seekp(-2, std::ios::cur);
  outputFile << "\n";
  outputFile << "Quantity: " << new_order.quantity << "\n";
  outputFile << "Total Cost: " << new_order.total_cost << " Rs" << "\n";
  outputFile << "Assigned Table: " << assignedTable + 1 << "\n\n";
  outputFile.close();

  cout << "Your Order Has Been Successfully Created! Table " << assignedTable + 1 << " has been assigned." << endl;
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
        getline(cin, orders[i].ordered_items);
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
    outputFile << "Items Ordered: " << updatedOrders[i].ordered_items << "\n";
    outputFile << "Quantity: " << updatedOrders[i].quantity << "\n";
    outputFile << "Total Price in PKR: " << updatedOrders[i].total_cost << " Rs" << "\n";
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
  bool found = false;
  cout << "Enter the order ID for which you want to generate an invoice: ";
  cin >> ID;

  for (int i = 0; i < order_nums; i++) {
    if (orders[i].orderId == ID) {
      found = true;

      cout << "-----------------------------------" << endl;
      cout << "Order ID: " << orders[i].orderId << endl;
      cout << "Customer Name: " << orders[i].customer_name << endl;
      cout << "-----------------------------------" << endl;

      cout << "Ordered Items:" << endl;
      for (const auto& item : loadedMenu) {
        int count = std::count(orders[i].items_ordered.begin(), orders[i].items_ordered.end(), item.getName());
        if (count > 0) {
          cout << " - " << item.getName() << " (" << count << ")" << endl;
        }
      }

      cout << "-----------------------------------" << endl;
      cout << "Quantity: " << orders[i].quantity << endl;
      cout << "Price per item: Rs." << orders[i].price << endl;
      cout << "Total Cost: Rs." << orders[i].total_cost << endl;
      cout << "-----------------------------------" << endl;

      CustomerSatisfaction(); 

      break;
    }
  }

  if (!found) {
    cout << "Order with ID " << ID << " not found." << endl;
  }
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
    outputFile << "Items Ordered: " << orders[i].ordered_items << "\n";
    outputFile << "Quantity: " << orders[i].quantity << "\n";
    outputFile << "Total Price in PKR: " << orders[i].total_cost << " Rs" << "\n\n";
  }
  outputFile.close();
  cout<<"Exiting Program..."<<endl;
  exit(0);
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
                ExitProgram();
                break;
            default:
                cout << "Invalid option. Please try again." << endl;
                break;
        }

        cout << "\n";
    } while (option != 6);

    return 0;
}
