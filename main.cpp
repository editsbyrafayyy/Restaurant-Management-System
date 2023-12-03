#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
using namespace std;

//________________________________CONSTANTS____________________________
const string filename = "hardees.txt";
//________________________________FUNCTION CALLS______________________
void manageMenu();
void displayOptions(int a);
//_____________________________________________________________________

	class MenuItem
	{
	private:
		string name;
		double price;
		string description;
		bool availaiblity;
		string category;
	public:
		void setName(std::string itemName) {
			name = itemName;
		}

		void setPrice(double itemprice) {
			price = itemprice;
		}

		void setDescription(string desc) {
			description = desc;
		}

		void setCategory(string cat) {
			category = cat;
		}

		void setAvailaibilty(bool aval) {
			availaiblity = aval;
		}

		string getName() const {
			return name;
		}

		string getCategory() const {
			return category;
		}

		double getPrice() const {
			return price;
		}

		bool getAvailaibilty() const {
			return availaiblity;
		}

		string getDescription() const {
			return description;
		}
		
		string serialize() const {
			// Will be used in loading and unloading objects from text file
			return name + "*" + to_string(price) + "*" + description + "*" + (availaiblity ? "1" : "0") 
				+ "*" + category;
		}

		void deserialize(const string& serialzedstring) {
			// Breaks down the concatenated data line  
			istringstream iss(serialzedstring); // treats the input as a stream

			getline(iss, name, '*');
			iss >> price;
			iss.ignore(); // Ignore the delimiter and any leading whitespaces
			getline(iss, description, '*');

			// Read availability as a string
			string availaibilityStr;
			getline(iss, availaibilityStr, '*');

			// Convert the availability string to a boolean
			availaiblity = (availaibilityStr == "1");

			// Read the category
			getline(iss, category, '*');
		}
	
	};

//_________________________________________________________________________________________________________
//_________________________________________________________________________________________________________
//_________________________________________________________________________________________________________
//_________________________________________________________________________________________________________

void saveMenuItemsToFile(const vector<MenuItem>& items, const string& filename) {
	ofstream file(filename);
	if (file.is_open()) {
		for (const auto& item : items) {
			file << item.serialize() << "\n";
		}
		file.close();
		std::cout << "Menu items saved to " << filename << std::endl;
	}
	else {
		std::cerr << "Unable to open file: " << filename << std::endl;
	}
}

vector<MenuItem> loadMenuItemsFromFile(const string& filename) {
	vector<MenuItem> items;
	ifstream file(filename);
	if (file.is_open()) {
		string line;
		while (getline(file, line)) {
			MenuItem item;
			item.deserialize(line);
			items.push_back(item);
		}
		file.close();
		cout << "Loaded Items Succesfully from file: " << filename << endl;
	}
	else {
		cout << "Error: Unable to open file: " << filename << endl;
	}
	return items;
}


int main() {

	cout << "Welcome to the resturant management system!" << endl;
	while (true)
	{
		displayOptions(0);
		int n; cin >> n; cin.ignore();
		if (n==1)
		{
			manageMenu();
		}
		else if (n==10)
		{
			system("cls");
			cout << "Thanks for using our application!" << endl;
			break;
		}
	}
	return 0;
}

void displayOptions(int a) {

	if (a == 0) // Main Menu options
	{
		cout << "1) Manage Resturant Menu" << endl;
		cout << "2) Process Orders" << endl;
		cout << "3) Manage Inventory" << endl;
		cout << "4) Manage Employees" << endl;
		cout << "5) Manage your Reservation system" << endl;
		cout << "6) Generate Invoice" << endl;
		cout << "7) Generate Reports" << endl;
		cout << "8) Manage Tables" << endl;
		cout << "9) Customer Feedback" << endl;
		cout << "10) Exit Program" << endl;
	}
	else if (a == 1)// Managing Resturant Menu options
	{
		cout << "1) Display Current Menu" << endl;
		cout << "2) Add New Item to Menu" << endl;
		cout << "3) Remove an Item from Menu" << endl;
		cout << "4) Modidfy Item Details" << endl;
		cout << "5) Modify Availaibility" << endl;
		cout << "6) Modify Discounts" << endl;
		cout << "7) Exit Menu Managing and go back to Main Menu" << endl;
	}
}

 void manageMenu() {
	system("cls");
	cout << "\t---Manage your Returant menu---" << endl;
	displayOptions(1); 
	cout << "Enter your option (number): " << endl;
	int option; cin >> option; // Provide, with and make them select their option
	cin.ignore();
	
	if (option==1) // DISPLAY CURRENT MENU
	{
		vector<MenuItem> loadedMenu = loadMenuItemsFromFile(filename);
		for (const auto& item : loadedMenu) {
			cout << "Item Name: " << item.getName() << endl;
			cout << "Category: " << item.getCategory() << endl;
			cout << "Price: $" << item.getPrice() << endl;
			cout << "Description: " << item.getDescription() << endl;
			cout << "Availability: " << (item.getAvailaibilty() ? "Available" : "Not Available") << endl;
			cout << "-----------------\n";
		}
	}
	else if (option==2)
	{
		string newItemName, newItemDescription, newItemCategory;
		double newItemPrice;

		cout << "Enter details for the new menu item:\n";
		cout << "Name: ";
		getline(cin, newItemName);
		cout << "Description: ";
		getline(cin, newItemDescription);
		cout << "Category: ";
		getline(cin, newItemCategory);
		cout << "Price: ";
		cin >> newItemPrice;

		// Create a new MenuItem
		MenuItem newItem;
		newItem.setName(newItemName);
		newItem.setDescription(newItemDescription);
		newItem.setCategory(newItemCategory);
		newItem.setPrice(newItemPrice);
		newItem.setAvailaibilty(true); // Assuming the new item is available

		// Load menu items from file
		vector<MenuItem> menuItems = loadMenuItemsFromFile(filename);

		// Add the new item to the vector
		menuItems.push_back(newItem);

		// Save the updated menu items to the file
		saveMenuItemsToFile(menuItems, filename);

		cout << "New item added and saved to the menu file.\n";
	}
}