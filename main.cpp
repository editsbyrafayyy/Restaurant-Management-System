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

	MenuItem() : name(""), price(0.0), description(""), availaiblity(false), category("") {}

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
		return name + "*" + std::to_string(price) + "*" + description + "*" + (availaiblity ? "1" : "0") + "*" + category;
	}

	void deserialize(const std::string serializedString) {
		std::istringstream iss(serializedString);
		getline(iss, name, '*');
		iss >> price;
		iss.ignore();
		getline(iss, description, '*');

		std::string availabilityStr;
		getline(iss, availabilityStr, '*');
		availaiblity = (availabilityStr == "1");

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
		cout << "Menu items saved to " << filename << endl;
	}
	else {
		cout << "Unable to open file: " << filename << endl;
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

vector<MenuItem> loadedMenu; //declaring a global array

int main() {
	vector<MenuItem> loadedMenu = loadMenuItemsFromFile(filename);
	cout << "Welcome to the resturant management system!" << endl;
	while (true)
	{
		displayOptions(0);
		int n;
		cin >> n;
		cin.ignore();
		if (n == 1)
		{
			manageMenu();
		}
		else if (n == 0)
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
		cout << "2) Process Orders and Generate Invoice" << endl;
		cout << "3) Manage Employees" << endl;
		cout << "4) Manage Tables/ Reservation system" << endl;
		cout << "5) Customer Feedback" << endl;
		cout << "0) Exit Program" << endl;
	}
	else if (a == 1)// Managing Resturant Menu options
	{
		cout << "1) Display Current Menu" << endl;
		cout << "2) Add New Item to Menu" << endl;
		cout << "3) Remove an Item from Menu" << endl;
		cout << "4) Modidfy Item Details" << endl;
		cout << "5) Exit Menu Managing and go back to Main Menu" << endl;
	}
	else if (a == 2) //Modifying Item details (subset of Managing Menu)
	{
		cout << "1) Change Name" << endl;
		cout << "2) Change Price" << endl;
		cout << "3) Change Description" << endl;
		cout << "4) Change Availaibility" << endl;
		cout << "5) Change Category" << endl;
	}
}

void manageMenu() {
	while (true)
	{

		system("cls");
		cout << "\t---Manage your Returant menu---" << endl;
		displayOptions(1);
		cout << "Enter your option (number): " << endl;
		int option; cin >> option; // Provide, with and make them select their option
		cin.ignore();
		loadedMenu = loadMenuItemsFromFile(filename);
		if (option == 1) // DISPLAY CURRENT MENU
		{
			for (const auto& item : loadedMenu) {
				cout << "Item Name: " << item.getName() << endl;
				cout << "Category: " << item.getCategory() << endl;
				cout << "Price: $" << item.getPrice() << endl;
				cout << "Description: " << item.getDescription() << endl;
				cout << "Availability: " << (item.getAvailaibilty() ? "Available" : "Not Available") << endl;
				cout << "-----------------\n";
			}
			int n; cout << endl << "Enter 0 to go back to Main Menu or anyother number to Manage Resturant Menu: ";
			cin >> n;
			if (n == 0)
			{
				break;
			}
		}
		else if (option == 2) // ENTER NEW ITEM
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

			int n;
			cout << endl << "Enter 0 to go back to Main Menu or anyother number to Manage Resturant Menu: ";
			cin >> n;
			if (n == 0)
			{
				break;
			}
		}
		else if (option == 3)//     REMOVE AN ITEM FROM MENU PERMENANTLY
		{
			system("cls");
			cout << "WARNING: Items deletion is permenant" << endl;
			cout << "Enter 'y' to load item list or anyother key to skip ahead: ";
			char y; cin >> y;
			cin.ignore();
			vector<MenuItem> loadedMenu = loadMenuItemsFromFile(filename);

			if (y == 'y' || y == 'Y')
			{
				int n = 0;
				for (const auto& item : loadedMenu)
				{
					cout << n++ << ")" << item.getName() << endl;
				}
			}
			string delitem;
			cout << "Please enter the name of the Item you want to delete: " << endl;
			getline(cin, delitem);

			auto it = remove_if(loadedMenu.begin(), loadedMenu.end(), [delitem](const MenuItem item)
				{return (delitem == item.getName()) ? true : false; }); //i'm so surprised i wrote this myself lmao
			if (it == loadedMenu.end())
			{
				cout << "Item " << delitem << " Not found :(" << endl;
			}
			else
			{
				loadedMenu.erase(it, loadedMenu.end());
				cout << "Item Removed Succesfully! :)" << endl;
			}

			saveMenuItemsToFile(loadedMenu, filename);
			int n; cout << endl << "Enter 0 to go back to Main Menu or anyother number to Manage Resturant Menu: ";
			cin >> n;
			if (n == 0)
			{
				break;
			}
		}
		else if (option == 4) {
			vector<MenuItem> loadedMenu = loadMenuItemsFromFile(filename);
			system("cls");
			int index = 0; bool found = false;

			for (const auto& item : loadedMenu)
			{
				cout << ++index << ") " << item.getName() << endl;
			}


			cout << "Enter the number of the item you want to modify: " << endl;
			int ItemNum; cin >> ItemNum; cin.ignore();

			if (ItemNum >= 0 && ItemNum <= index)
			{
				found = true;
			}

			if (found)
			{
				index = ItemNum - 1;
				cout << "Item found!\n" << "What do you want to modify about this item?\n";
				displayOptions(2);
				int n; cout << "Enter your option by it's corresponding number: "; cin >> n; cin.ignore();

				if (n == 1)
				{
					cout << "Enter new name: ";
					string newname; cin >> newname; cin.ignore();
					loadedMenu[index].setName(newname);
				}
				else if (n == 2)
				{
					cout << "Enter new Price: ";
					double newprice; cin >> newprice;
					loadedMenu[index].setPrice(newprice);
				}
				else if (n == 3)
				{
					cout << "Enter new Description: ";
					string newdesc; cin >> newdesc;
					loadedMenu[index].setDescription(newdesc);

				}
				else if (n == 4)
				{
					cout << "Enter 0 for not availaible and 1 for avaiaible";
					bool aval; cin >> aval;
					if (aval == 0 || aval == 1)
					{
						loadedMenu[index].setAvailaibilty(aval);
					}
					else
						cout << "Error: Enter either 0 or 1!";
				}
				else if (n == 5)
				{
					cout << "Enter new Category: ";
					string newcat; cin >> newcat; cin.ignore();
					loadedMenu[index].setCategory(newcat);
				}
				saveMenuItemsToFile(loadedMenu, filename);
			}
			else
			{
				cout << "Sorry the item name you entered was not found!" << endl
					<< "make sure spellings are correct, search is also case sensitive";
			}
			int n; cout << endl << "Enter 0 to go back to Main Menu or anyother number to Manage Resturant Menu: ";
			cin >> n;
			if (n == 0)
			{
				break;
			}
		}
		else if (option == 5) {
			system("cls");
			cout << "Exited Menu Mangement Succesfully!" << endl;
			break;
		}
		else
		{
			cout << "Error: Please choose from 1-5." << endl;
		}
	}
}