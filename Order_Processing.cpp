// I have used PF wali libraries, so code thora restricted but it is what it is, things that are yet to be changed:
// combining per se the programs (unmein compatibility add karna somehow), either removing the invoice file cause 
// bruhhh phir usko bhi read aur write karna hoga mujhay nahi pata kaisay hoga, file mein jo tables save hotay
// wo thoray ajeeb hein, havent figured that part completely. so yeye have commented most parts gl

#include <iostream>
#include <string>
#include <fstream>
using namespace std;

const int max_orders = 50; // max orders
const int max_tables = 10; // max tables

struct Orders { // the 1st structure
  int orderId;
  string customer_name;
  string items_ordered;
  int quantity;
  int price;
  int total_cost;
  int assignedTableId; // stores the ID of the table assigned to the order
};

struct Table { // the 2nd structure
  int tableId;
  bool occupied; //  indicates whether the table is occupied or not
  int orderId; 
};

Orders orders[max_orders]; //declaring a new var with the properties of Orders structure
int order_nums = 0; // number of orders

Table tables[max_tables];
int occupied_tables = 0; // number of occupied tables

void CreateOrder() { // first option on the menu (creates the order yeye)
  
  ofstream outputFile("orders.txt", ios::app);

  if (!outputFile.is_open()) {
    cout << "Error opening file." << endl;
    return;
  }
  
  if (order_nums >= max_orders) {
    cout << "Max Orders Exceeded" << endl;
    return;
  }

  Orders new_order;

  new_order.orderId = order_nums + 1;
  order_nums++;

// alot of validation basically

  // int input_id;
  // do { // it is for ID validation 
  //   cout << "Enter Order ID: ";
  //   cin >> input_id;
  //   if (cin.fail()) { // cin.fail here returns true if a letter, comma or special char is entered, so just to make sure the correct input is taken
  //     cout << "Invalid input. Please enter a number: ";
  //     cin.clear(); // (not compul but clears the buffer of the "error state" so an input can be taken again)
  //     cin.ignore(); // makes sures that the "wrong input" is removed from the buffer, makes sure koi problem na ho when taking input again)
  //   }
  // } while (input_id <= 0);

  //new_order.orderId = input_id; // stores that ID into the new stucture variable (sarra data store ho jata in one var iss tarha)

  string customer_name; 
    cout << "Enter Customer Name: ";
    getline(cin, new_order.customer_name); 

  while (new_order.customer_name.empty()){ // checks if the customer name entered is empty or not (if it is then takes input)
    getline(cin, new_order.customer_name);
      if (new_order.customer_name.empty()) { // if it left empty asks for input again
      cout << "Customer name cannot be empty. Please enter a name: ";
    }
  }

  string items_ordered;
  do { // it is for ordered items validation 
    cout << "Enter Ordered Items: ";
    getline(cin, new_order.items_ordered);
    if (new_order.items_ordered.empty()) { // follows the same idea as customer name just with do while lol
      cout << "Items ordered cannot be empty. Please enter items: ";
    }
  } while (new_order.items_ordered.empty());

  
do {
  cout << "Enter Quantity: ";
  while (!(cin >> new_order.quantity) || new_order.quantity <= 0) { // jab tak conditions true nahi hotein it keeps on asking for input ("!" reverses the conditions to check)
    cout << "Invalid input. Please enter a positive number: ";
    cin.clear();
    cin.ignore();
  }
} while (new_order.quantity <= 0);

  do {
  cout << "Enter Price: ";
  cin >> new_order.price;
  if (cin.fail() || new_order.price <= 0.0) {
    cout << "Invalid input. Please enter a positive number: ";
    cin.clear();
    cin.ignore();
  }
} while (new_order.price <= 0.0);

new_order.total_cost = new_order.price * new_order.quantity; // calcs the total cost

int assignedTable = -1; //sets kay no tables are assigned
for (int i = 0; i < max_tables && assignedTable == -1; i++) { 
  if (!tables[i].orderId) { // looks for table available
    assignedTable = i;
  }
}

if (assignedTable == -1) {
  cout << "There Are No Tables Available Right Now, Business is Booming ;)" << endl;
  return;
}

tables[assignedTable].orderId = new_order.orderId; // stores the ID of the new order in the table's var 
new_order.assignedTableId = assignedTable;

orders[order_nums++] = new_order;

  outputFile << "Order ID: " << new_order.orderId << "\n";
  outputFile << "Customer Name: " << new_order.customer_name << "\n";
  outputFile << "Items Ordered: " << new_order.items_ordered << "\n";
  outputFile << "Quantity: " << new_order.quantity << "\n";
  outputFile << "Price: " << new_order.price << " Rs"<< "\n";
  outputFile << "Total Cost: " << new_order.total_cost << " Rs"<< "\n";
  outputFile << "Assigned Table: " << assignedTable + 1 << "\n\n";
  outputFile.close();

  // Confirmation message
  cout << "Your Order Has Been Successfully Created! Table " << assignedTable + 1 << " has been assigned." << endl;
}


void ModifyOrder() {
  int orderId;

  cout << "Enter order ID to modify: ";
  cin >> orderId;

  bool found = false;
  int orderIndex = -1; // Stores the index of the order to be modified
  for (int i = 0; i < order_nums; ++i) {
    if (orders[i].orderId == orderId) { // basic searching (could have used algo library but nah pf gang)
      found = true;
      orderIndex = i;
      break; 
    }
  }

  if (!found) {
    cout << "Order not found." << endl;
    return;
  }

  cout << endl << "The Order Has Been Found. What Changes Do You Want to Make?: " << endl;
  cout << "1. Customer Name" << endl;
  cout << "2. Items Ordered" << endl;
  cout << "3. Quantity" << endl;
  cout << "4. Price" << endl;

  int choice;
  cout << "Enter: ";
  cin >> choice;

  switch (choice) {
  case 1:
    cout << "Enter new customer name: ";
    cin.ignore();
    getline(cin, orders[orderIndex].customer_name);
    break;
  case 2:
    cout << "Enter new items ordered: ";
    cin.ignore();
    getline(cin, orders[orderIndex].items_ordered);
    break;
  case 3:
    cout << "Enter new quantity: ";
    cin >> orders[orderIndex].quantity;
    orders[orderIndex].total_cost = orders[orderIndex].price * orders[orderIndex].quantity; // recalculate total cost
    break;
  case 4:
    cout << "Enter new price: ";
    cin >> orders[orderIndex].price;
    orders[orderIndex].total_cost = orders[orderIndex].price * orders[orderIndex].quantity; // recalculate total cost
    break;
  default:
    cout << "Invalid choice." << endl;
    break;
  }

  ofstream outputFile("orders.txt", ios::out | ios::trunc);

  if (!outputFile.is_open()) {
    cout << "Error opening file." << endl;
    return;
  }

  for (int i = 0; i < order_nums; ++i) {
    outputFile << "Order ID: " << orders[i].orderId << "\n";
    outputFile << "Customer Name: " << orders[i].customer_name << "\n";
    outputFile << "Items Ordered: " << orders[i].items_ordered << "\n";
    outputFile << "Quantity: " << orders[i].quantity << "\n";
    outputFile << "Price: " << orders[i].price << " Rs"<< "\n";
    outputFile << "Total Cost: " << orders[i].total_cost << " Rs"<< "\n";
    outputFile << "Assigned Table: " << occupied_tables << "\n\n"; 
  }

  outputFile.close();

  cout << "Modifications Have Been Made Successfully" << endl;
}

void CancelOrder() {

  int ID;
  cout << "Enter order ID to cancel: ";
  cin >> ID; 

  bool found = false;
  int index = -1;
  for (int i = 0; i < order_nums; ++i) {
    if (orders[i].orderId == ID) { // searches for the ID
      found = true;
      index = i; // brings it to that index where it is located
      break; 
    }
  }

  if (!found) {
    cout << "The Order Does Not Exist" << endl;
    return;
  }

  tables[orders[index].assignedTableId].occupied = false; // sets the table_occupation to false as it will cancel that order
  tables[orders[index].assignedTableId].orderId = -1;

  if (index < order_nums - 1) { // this shifts the orders from the point where the order was removed
    orders[index] = orders[order_nums - 1];
  }

  order_nums--;

  ofstream outputFile("orders.txt", ios::out | ios::trunc); //entering all the data into the file backkk
  if (!outputFile.is_open()) {
    cout << "Error opening file." << endl;
    return;
  }

  for (int i = 0; i < order_nums; ++i) {
    outputFile << "Order ID: " << orders[i].orderId << "\n";
    outputFile << "Customer Name: " << orders[i].customer_name << "\n";
    outputFile << "Items Ordered: " << orders[i].items_ordered << "\n";
    outputFile << "Quantity: " << orders[i].quantity << "\n";
    outputFile << "Total Price in Rs: " << orders[i].total_cost << "\n";
    outputFile << "Assigned Table: " << (orders[i].assignedTableId + 1) << "\n\n";
  }

  outputFile.close();

  cout << "The Order Has Been Successfully Canceled." << endl;
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
  string waiter, taste, temp, speed, staff, clean;

  bool valid_name = false; // for name
  while (!valid_name) {
    cout << "What was the name of the waiter?: ";
    cin.ignore();
    getline(cin, waiter);

    if (waiter.empty()) {
      cout << "Please enter a valid waiter name." << endl;
    } else {
      valid_name = true;
    }
  }

  string validOptions[] = {"Good", "Avg", "Bad", "good", "avg", "bad"}; // validation to ensure that only these 6 options are choosen from

  bool valid_taste = false; // for taste
  while (!valid_taste) {
    cout << "Food taste (Good/Avg/Bad): ";
    getline(cin, taste);

    for (const string& option : validOptions) {
      if (taste == option) {
        valid_taste = true;
        break;
      }
    }

    if (!valid_taste) {
      cout << "Please enter a valid option: Good, Avg, or Bad." << endl;
    }
  }

    bool valid_temp = false; // for temp 
  while (!valid_temp) {
    cout << "Temperature of The Food: (good/avg/bad): ";
    getline(cin, temp);

    for (const string& option : validOptions) {
      if (temp == option) {
        valid_temp = true;
        break;
      }
    }

    if (!valid_temp) {
      cout << "Please enter a valid option: Good, Avg, or Bad." << endl;
    }
  }

  bool valid_speed = false; // for speed
  while (!valid_speed) {
    cout << "Speed of Serving (good/avg/bad): ";
    getline(cin, speed);

    for (const string& option : validOptions) {
      if (speed == option) {
        valid_speed = true;
        break;
      }
    }

    if (!valid_speed) {
      cout << "Please enter a valid option: Good, Avg, or Bad." << endl;
    }
  }

    bool valid_staff = false; // for staff
  while (!valid_staff) {
    cout << "Staff Friendliness (good/avg/bad): ";
    getline(cin, staff);

    for (const string& option : validOptions) {
      if (staff == option) {
        valid_staff = true;
        break;
      }
    }

    if (!valid_staff) {
      cout << "Please enter a valid option: Good, Avg, or Bad." << endl;
    }
  }

  bool valid_clean = false; // for cleaning
    while (!valid_clean) {
      cout << "Clean (good/avg/bad): ";
      getline(cin, clean);

      for (const string& option : validOptions) {
        if (clean == option) {
          valid_clean = true;
          break;
        }
      }

      if (!valid_clean) {
        cout << "Please enter a valid option: Good, Avg, or Bad." << endl;
      }
    }

  ofstream feedbackFile("customer_feedback.txt", ios::app); // adds all the data into the file 
  if (!feedbackFile) {
    cout << "Error opening feedback file." << endl;
    return;
  }

  feedbackFile << "Customer ID: " << customerId << endl;
  feedbackFile << "--------------------------------------" << endl;
  feedbackFile << "Waiter Name: " << waiter << endl;
  feedbackFile << "Taste: " << taste << endl;
  feedbackFile << "Temperature: " << temp << endl;
  feedbackFile << "Speed of Service: " << speed << endl;
  feedbackFile << "Staff Friendliness: " << staff << endl;
  feedbackFile << "Cleanliness: " << clean << endl;
  feedbackFile << "--------------------------------------" << endl;

  feedbackFile.close();

  cout << "Feedback Noted :)" << endl;

}

void GenerateInvoice() {
  int ID;
  bool found = false;

  cout << "Enter the order ID for which you want to generate an invoice: ";
  cin >> ID;

  for (int i = 0; i < order_nums; i++) {
    if (orders[i].orderId == ID) {
      found = true;

      char saveInvoice;
      cout << "Do you want to save the invoice for order ID " << ID << " to a file? (Y/N): ";
      cin >> saveInvoice;

      if (saveInvoice == 'y' || saveInvoice == 'Y') { // asks agar file mein save karna
        ofstream outputFile("invoice.txt");

        if (!outputFile.is_open()) {
          cout << "Error opening file." << endl;
          return;
        }

        outputFile << "---------------------------" << endl;
        outputFile << "Order ID: " << orders[i].orderId << endl;
        outputFile << "Customer Name: " << orders[i].customer_name << endl;
        outputFile << "---------------------------" << endl;
        outputFile << "Ordered Items:" << endl;

        for (int j = 0; j < orders[i].quantity; ++j) {
          outputFile << " - " << orders[i].items_ordered << endl;
        }

        outputFile << "---------------------------" << endl;
        outputFile << "Quantity: " << orders[i].quantity << endl;
        outputFile << "Price per item Rs: " << orders[i].price << endl;
        outputFile << "Total Cost Rs: " << orders[i].total_cost << endl;
        outputFile << "---------------------------" << endl;

        outputFile.close();
      }
    }
  }

  if (!found) {
    cout << "Order with ID " << ID << " not found." << endl;
  }

  CustomerSatisfaction(ID); // calls customer feedback func if order find hota tab
  
}

void SearchOrders() {

  string keyword;
  cout<<"Enter The Keyword That You Want To Find: "; // looks for a specific word and outputs the order accordingly
  cin>>keyword;

  bool found = false; 
  for (int i = 0; i < order_nums; ++i) {
    
    if (orders[i].customer_name.find(keyword) != string::npos || orders[i].items_ordered.find(keyword) != string::npos ||
        to_string(orders[i].total_cost).find(keyword) != string::npos) { // checks the entire string to see if the val was not found 
                                                      // npos ka matlab is no position so like agar val nahi found to return false
      found = true; // if found
      
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

// I cant explain the readfile, writefile is straightforward enough tbh
void WriteDataToFiles(const string& filePath, const Orders orders[], int order_nums, const Table tables[], int occupied_tables) {
  ofstream file(filePath);

  if (!file.is_open()) {
    cerr << "Error opening file: " << filePath << endl;
    return;
  }

  // Write all orders
  for (int i = 0; i < order_nums; ++i) {
    file << "Order ID: " << orders[i].orderId << endl;
    file << "Customer Name: " << orders[i].customer_name << endl;
    file << "Items Ordered: " << orders[i].items_ordered << endl;
    file << "Quantity: " << orders[i].quantity << endl;
    file << "Price per item: " << orders[i].price << endl;
    file << "Total Cost: " << orders[i].total_cost << endl;
    file << "Assigned Table: " << (orders[i].assignedTableId + 1) << endl;
    file << endl;
  }

  // Write table status
  for (int i = 0; i < occupied_tables; ++i) {
    file << "Table ID: " << tables[i].tableId << endl;
    file << "Occupied: " << (tables[i].occupied ? "Yes" : "No") << endl;
    file << "Order ID: " << (tables[i].occupied ? tables[i].orderId : -1) << endl;
    file << endl;
  }

  file.close();
}

bool readDataFromFile(const string& filePath, Orders orders[], int& order_nums, Table tables[], int& occupied_tables) {
  // Open the file for reading
  ifstream file(filePath);

  // Check if file opened successfully
  if (!file.is_open()) {
    cerr << "Error opening file: " << filePath << endl;
    return false;
  }

  // Initialize variables
  string line;
  int currentOrderId = 0;

  // Clear existing data
  order_nums = 0;
  occupied_tables = 0;

  // Read each line of the file
  while (getline(file, line)) {
    // Check for empty line or comment
    if (line.empty() || line.rfind("//", 0) == 0) {
      continue;
    }

    // Check if new order is starting
    if (line.find("Order ID:") != string::npos) {
      // Extract order ID
      currentOrderId = stoi(line.substr(line.find(":") + 2));

      // Initialize new order
      orders[order_nums] = Orders();
      orders[order_nums].orderId = currentOrderId;
      ++order_nums;
    } else {
      // Extract other order details based on the current line
      if (line.find("Customer Name:") != string::npos) {
        orders[order_nums - 1].customer_name = line.substr(line.find(":") + 2);
      } else if (line.find("Items Ordered:") != string::npos) {
        orders[order_nums - 1].items_ordered = line.substr(line.find(":") + 2);
      } else if (line.find("Quantity:") != string::npos) {
        orders[order_nums - 1].quantity = stoi(line.substr(line.find(":") + 2));
      } else if (line.find("Price:") != string::npos) {
        orders[order_nums - 1].price = stoi(line.substr(line.find(":") + 2));
      } else if (line.find("Total Cost:") != string::npos) {
        orders[order_nums - 1].total_cost = stoi(line.substr(line.find(":") + 2));
      } else if (line.find("Assigned Table:") != string::npos) {
        orders[order_nums - 1].assignedTableId = stoi(line.substr(line.find(":") + 2)) - 1;
      }
    }
  }

  for (int i = 0; i < order_nums; ++i) {
    if (orders[i].assignedTableId > -1) {
      int tableIndex = orders[i].assignedTableId;
      tables[tableIndex].occupied = true;
      tables[tableIndex].orderId = orders[i].orderId;
      ++occupied_tables;
    }
  }

  // Close the file
  file.close();

  return true;
}

void ExitProgram() {
  ofstream outputFile("orders.txt", ios::out | ios::trunc); // exits and updates everything 

  if (!outputFile.is_open()) {
    cerr << "Error opening file." << endl;
    return;
  }

  for (int i = 0; i < order_nums; ++i) {
    outputFile << "Order ID: " << orders[i].orderId << endl;
    outputFile << "Customer Name: " << orders[i].customer_name << endl;
    outputFile << "Items Ordered: " << orders[i].items_ordered << endl;
    outputFile << "Quantity: " << orders[i].quantity << endl;
    outputFile << "Total Cost (Rs): " << orders[i].total_cost << endl;
    outputFile << "Assigned Table: " << (orders[i].assignedTableId + 1) << endl << endl;
  }

  outputFile.close();

  cout << "Exiting Program..." << endl;
  exit(0);
}


int main() {
  int option;

  readDataFromFile("orders.txt", orders, order_nums, tables, occupied_tables); // before exexuting the program reads the file

  do { // this was kafi uneccesary but looks cool (totally didnt spend way too much time aligning everything)
    cout << "\t-┌───────────────────────────────────────┐-" << endl;
    cout << "-----= \t│      Restaurant Management System       │  =-----" << endl;
    cout << "\t-└───────────────────────────────────────┘-" << endl;

    cout << "\t    ┌───────────────────────────────┐" << endl;
    cout << "\t    │ 1. Create a New Order         │" << endl;
    cout << "\t    │ 2. Modify an Existing Order   │" << endl;
    cout << "\t    │ 3. Cancel an Order            │" << endl;
    cout << "\t    │ 4. Show All Orders            │" << endl;
    cout << "\t    │ 5. Print Invoice for an Order │" << endl;
    cout << "\t    │ 6. Search for an Order        │" << endl;
    cout << "\t    │ 7. Exit                       │" << endl;
    cout << "\t    └───────────────────────────────┘" << endl;

    cout<<endl;
    cout << "Enter your option: ";
    cin >> option;

    switch (option) {
      case 1:
        CreateOrder();
        WriteDataToFiles("orders.txt", orders, order_nums, tables, occupied_tables);
        break;
      case 2:
        ModifyOrder();
        WriteDataToFiles("orders.txt", orders, order_nums, tables, occupied_tables);
        break;
      case 3:
        CancelOrder();
        WriteDataToFiles("orders.txt", orders, order_nums, tables, occupied_tables);
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