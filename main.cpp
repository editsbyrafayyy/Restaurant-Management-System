#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <ctime>

using namespace std;


//________________________________CONSTANTS____________________________
const string filename = "hardees.txt"; 
const string filename2 = "employee.txt";
//________________________________FUNCTION CALLS______________________
void manageMenu(); void manageEmployees();
void displayOptions(int a);
//_____________________________________________________________________

class Employee {
private: 
	string name;
	string position;
	string contactinfo;
	int salary;
	double totalrating;
	int orderscompleted;

public:
	//default constructor
	Employee():name(""),position(""),contactinfo(""),salary(0),totalrating(0),orderscompleted(0){} 

	//constructor
	Employee(string name,string position,string contactInfo,int salary):
		name(name),position(position),contactinfo(contactInfo),salary(salary),totalrating(0),orderscompleted(0){}

	void dispEmpInfo() {
		cout << endl << "Name: " << name;
		cout << endl << "Position: " << position;
		cout << endl << "Contact Info: " << contactinfo;
		cout << endl << "Salary: " << salary;
		cout << endl << "Rating: " << (totalrating>0) ? totalrating/orderscompleted:0 ; // this statement feels like a flex fr
		cout << endl << "Orders Completed: " << orderscompleted;
	}

	string getName() {
		return name;
	}

	string getPosition() {
		return position;
	}

	string getContactInfo() {
		return contactinfo;
	}

	int getSalary() {
		return salary;
	}

	double getRating() {
		return totalrating;
	}

	int getnumOrders() {
		return orderscompleted;
	}

	void setName(string Name) {
		name = Name;
	}

	void setPosition(string Position) {
		position = Position;
	}

	void setSalary(int change) {
		salary += change;
	}

	void setRating(double newrating){ 
		totalrating += newrating;
	}

	void setContactInfo(string info) {
		contactinfo = info;
	}

	void increaseOrdernum() {
		orderscompleted++;
	}

	string serialize() const {
		ostringstream oss;
		oss << name << "|" << position << "|" << contactinfo << "|" << salary << "|" << totalrating << "|" << orderscompleted;
		return oss.str();
	}

	// Deserialize employee data from a string
	void deserialize(const string& serializedData) {
		istringstream iss(serializedData);
		getline(iss, name, '|');
		getline(iss, position, '|');
		getline(iss, contactinfo, '|');
		iss >> salary;
		iss.ignore();  
		iss >> totalrating;
		iss.ignore();
		iss >> orderscompleted;
	}

	
};

void saveEmployeesToFile(vector<Employee>& employees, const string& filename) {
	ofstream file(filename);

	if (file.is_open()) {
		for (const auto& emp : employees) {
			file << emp.serialize() << '\n';
		}
		file.close();
		cout << "Data saved to file: " << filename << endl;
	}
	else {
		cout << "Error opening file: " << filename << endl;
	}
}

// Deserialize employee data from a text file to vector
void loadEmployeesFromFile(vector<Employee>& employees, const string& filename) {
	ifstream file(filename);

	if (file.is_open()) {
		employees.clear();

		string line;
		while (getline(file, line)) {
			Employee emp;
			emp.deserialize(line);
			employees.push_back(emp);
		}

		file.close();
		cout << "Data loaded from file: " << filename << endl;
	}
	else {
		cout << "Error opening file: " << filename << endl;
	}
}
//____________________________________________________________________________________________________________________
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
		return name + "*" + to_string(price) + "*" + description + "*" + (availaiblity ? "1" : "0") + "*" + category;
	}

	void deserialize(const string serializedString) {
		istringstream iss(serializedString);
		getline(iss, name, '*');
		iss >> price;
		iss.ignore();
		getline(iss, description, '*');

		string availabilityStr;
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
	}
	else {
		cout << "Error: Unable to open file: " << filename << endl;
	}
	return items;
}

vector<MenuItem> loadedMenu; //declaring a global array
vector<Employee> employees; //declaring second global array :(

int main() {
	loadedMenu = loadMenuItemsFromFile(filename); // load first arr from file
	loadEmployeesFromFile(employees,filename2); // load second array from file

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
		else if (n==3)
		{
			manageEmployees();
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
	else if (a==2) //Modifying Item details (subset of Managing Menu)
	{
		cout << "1) Change Name" << endl;
		cout << "2) Change Price" << endl;
		cout << "3) Change Description" << endl;
		cout << "4) Change Availaibility" << endl;
		cout << "5) Change Category" << endl;
	}
	else if (a==3) // Manage employee options
	{
		cout << "1) List all employees" << endl;
		cout << "2) Hire New employee" << endl;
		cout << "3) Mark Attendance" << endl;
		cout << "4) Check Attendance" << endl;
		cout << "5) Fire Employee" << endl;
		cout << "6) Change Employee information" << endl;
		cout << "0) Exit Managing Employees and go back to Main Menu" << endl;
	}
	else if (a==4) // CHANGE EMPLOYEE INFO OPTIONS
	{
		cout << "1) Change Name" << endl;
		cout << "2) Change Position" << endl;
		cout << "3) Change Contact Information" << endl;
		cout << "4) Increase or decrease Salary" << endl;
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
			if (n==0)
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

void manageEmployees() {
	
	system("cls");
	while (true) {
		cout << "-Manage Your Employees-" << endl;
		displayOptions(3);
		int option;
		cout << endl << "Enter Your Option(number) : ";
		cin >> option;
		if (option == 1) // Display Employees
		{
			employees.clear();
			loadEmployeesFromFile(employees, filename2);
			for (Employee item : employees) {
				item.dispEmpInfo();
				cout << "\n____________________________" << endl;
			}
		}
		else if (option == 2)   // Hire New employee
		{
			system("cls");
			cout << "Congratulations on hiring new employee\n" << "Please enter the new employees details" << endl;
			Employee newEmp;
			
			string name;
			cout << "Enter employee name: ";
			cin >> name;

			string position;
			cout << "Enter employee position: ";
			cin >> position;

			string contacinfo;
			cout << "Enter employee contact info: ";
			cin >> contacinfo; cin.ignore();

			int salary;
			cout << "Enter employee salary: ";
			while (!(cin >> salary)) { //             Validation check ewww
				cin.clear();  // Clear the error flag
				cin.ignore(numeric_limits<streamsize>::max(), '\n');  // Discard invalid input
				cout << "Invalid input. Please enter a numeric value for salary: ";
			}

			newEmp.setName(name); newEmp.setPosition(position);
			newEmp.setContactInfo(contacinfo); newEmp.setSalary(salary);
			
			employees.push_back(newEmp);
			saveEmployeesToFile(employees, filename2);
		}
		else if (option == 3)   // Mark Attendance
		{
			ofstream outFile("attendance.txt",ios::app);
			cout << "\nWARNING ATTENDANCE CAN NOT BE MODIFIED BE CARFEFUL\n\n";
			if (outFile.is_open()) {
				time_t now = time(0);
				tm* currentDate = localtime(&now);

				// Adding date to the file
				outFile << (currentDate->tm_mday) << '/' << (currentDate->tm_mon + 1) << '/' << (currentDate->tm_year + 1900) << "|";

				for (Employee emp : employees) {
					char attendance;
					cout << "Is " << emp.getName() << " present? (Y/N): ";
					cin >> attendance;

					// Converting to 1 for present, 0 for absent
					int attendanceCode = (attendance == 'Y' || attendance == 'y') ? 1 : 0;

					// Write to file in the format: EmployeeName|AttendanceCode+
					outFile << emp.getName() << "|" << attendanceCode << "+";
				}

				outFile.close();
				cout << "Attendance recorded and saved to attendance.txt.\n";
			}
			else {
				cout << "Error opening file: attendance.txt\n";
			}
		}
		else if (option == 4) // Reads Attendance
		{
			string inputDate;
			cout << "Enter the date you want to check attendance of (dd/mm/yy): ";
			cin >> inputDate;

			// Validation checks are tiring ;(
			while (true) {
				cout << "Enter the date (dd/mm/yy): ";
				cin >> inputDate;

				if (inputDate.length() == 8) {
					bool validFormat = true;
					for (auto i = inputDate.begin(); i != inputDate.end(); ++i) {
						if (!isdigit(*i) && (i == inputDate.begin() + 2 || i == inputDate.begin() + 5)) {
							validFormat = false;
							break;
						}
					}

					if (validFormat) {
						break; // Exit the loop if the input is in the correct format
					}
				}

				cout << "Invalid date format. Please enter the date in dd/mm/yy format.\n";
				cin.clear();    // Clear input buffer to handle invalid input
				cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Ignore remaining characters in the buffer
			}

			ifstream inFile("attendance.txt");
			if (inFile.is_open()) {
				string line;
				while (getline(inFile, line)) {
					// Extract date from the line
					string currentDate = line.substr(0, 8);

					// Check if the date matches the user input
					if (currentDate == inputDate) {
						cout << "Attendance for " << inputDate << ":\n";
						// Display attendance for each employee
						for (Employee emp : employees) {
							size_t pos = line.find(emp.getName() + "|");
							if (pos != string::npos) { // checks if this shit actually exists
								int attendanceCode = line[pos + emp.getName().length() + 1] - '0';
								cout << emp.getName() << ": " << (attendanceCode ? "Present" : "Absent") << endl;
							}
						}
						return; // Found and displayed attendance for the specified date
					}
				}

				cout << "No attendance found for the specified date.\n";
				inFile.close();
			}
			else {
				cout << "Error opening file: attendance.txt\n";
			}
		}
		else if (option == 5) // Fire Employee
		{
			loadEmployeesFromFile(employees, filename2); 
			cout << "\nWARNING, FIRING AN EMPLOYEE WILL DELETE ALL THEIR DATA INCLUDING ORDERS COMPLETED AND RATING\n";
			int n = 1;
			cout << "Choose an employee to fire by entering the number behind their name" << endl;
			for (Employee emp : employees) {
				cout << n++ << ") " << emp.getName() << endl;
			}
			cout << endl << "Enter number: ";
			cin >> n;
			n--;

			if (n >= 1 && n < (employees.size())) {
				// GET FIRED LMAO SKILL ISSUE + RATIO XD
				employees.erase(employees.begin() + n);

				cout << "Employee fired successfully.\n";

			}
			else {
				cout << "Invalid choice. No employee fired.\n"; //Validation check ;(
			}
			saveEmployeesToFile(employees,filename2);
		}
		else if (option==6) // CHANGE EMPLOYEE DETAILS
		{
			system("cls");
			loadEmployeesFromFile(employees, filename2); int n = 0;
			for (Employee emp : employees) {
				cout << ++n << ") " << emp.getName() << endl;
			}
			cout << "\nPlease choose an employee to modify their details" << endl;
			bool c = true;
			do
			{
				cout << "Enter your option (number behind their name): ";
				cin >> n; 
				if (n<1 || n>employees.size() + 1)
				{
					cout << "Please choose a correct number from the list displayed above" << endl; 
					c = false;
				}
				else
				{
					c = true;
				}
			} while (c=false);
			system("cls");
			cout << "What do you want to change about employee: " << employees[--n].getName() << endl;
			displayOptions(4);
			do {
				cout << "\nChoose your option by entering it's number: ";
				cin.ignore(); cin >> n;
				if (n < 1 || n>4)
				{
					cout << "Please choose a correct number from the list displayed above" << endl;
					c = false;
				}
				else
				{
					c = true;
				}
			} while (c = false);

			if (c == 1) {
				cout << "Please enter new name for your employee: ";
				string newname;
				getline(cin, newname);
				employees[n].setName(newname);
			}
			else if (c == 2) {
				cout << "Please enter new Position for your employee: ";
				string newpos;
				getline(cin, newpos);
				employees[n].setPosition(newpos);
			}
			else if (c == 3) {
				cout << "Please enter new contact info for your employee: ";
				string newc;
				getline(cin, newc);
				employees[n].setContactInfo(newc);
			}
			else if (c == 4) {
				cout << "Please enter salary adjustment (+ve for inc and -ve for dec) in pakistani rupees: ";
				int news;
				cin >> news;
				employees[n].setSalary(news);
			}
			saveEmployeesToFile(employees,filename2);
		}
		else if (option == 0) // Go back to main menu
		{
			break;
		}
		else
		{
			cout << "Please enter an integer between 1 to 6" << endl;
		}

		cout << endl << "Do you wish to continue managing employees (enter y) or not?(enter any char): ";
		char opt; cin >> opt;
		if (!(opt=='y' || opt=='Y'))
		{
			break;
		}
	}
}