#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <ctime>

using namespace std;


//__________________________filenames_________________________________
const string filename = "hardees.txt"; 
const string filename2 = "employee.txt";

//________________________________function calls______________________

void managemenu();			void manageemployees();		void displayoptions(int a);

//____________________________________________________________________

class employee {
private: 
	string name;
	string position;
	string contactinfo;
	int salary;
	double totalrating;
	int orderscompleted;

public:
	//default constructor
	employee():name(""),position(""),contactinfo(""),salary(0),totalrating(0),orderscompleted(0){} 

	//constructor
	employee(string name,string position,string contactinfo,int salary):
		name(name),position(position),contactinfo(contactinfo),salary(salary),totalrating(0),orderscompleted(0){}

	void dispempinfo() {
		cout << endl << "name: " << name;
		cout << endl << "position: " << position;
		cout << endl << "contact info: " << contactinfo;
		cout << endl << "salary: " << salary;
		cout << endl << "rating: " << (totalrating>0) ? totalrating/orderscompleted:0 ; // this statement feels like a flex fr
		cout << endl << "orders completed: " << orderscompleted;
	}

	string getname() {
		return name;
	}

	string getposition() {
		return position;
	}

	string getcontactinfo() {
		return contactinfo;
	}

	int getsalary() {
		return salary;
	}

	double getrating() {
		return totalrating;
	}

	int getnumorders() {
		return orderscompleted;
	}

	void setname(string newname) {
		name = newname;
	}

	void setposition(string newposition) {
		position = newposition;
	}

	void setsalary(int change) {
		salary += change;
	}

	void setrating(double newrating){ 
		totalrating += newrating;
	}

	void setcontactinfo(string info) {
		contactinfo = info;
	}

	void increaseordernum() {
		orderscompleted++;
	}

	string serialize() const {
		ostringstream oss;
		oss << name << "|" << position << "|" << contactinfo << "|" << salary << "|" << totalrating << "|" << orderscompleted;
		return oss.str();
	}

	// deserialize employee data from a string
	void deserialize(const string& serializeddata) {
		istringstream iss(serializeddata);
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

void saveemployeestofile(vector<employee>& employees, const string& filename) {
	ofstream file(filename);

	if (file.is_open()) {
		for (const auto& emp : employees) {
			file << emp.serialize() << '\n';
		}
		file.close();
		cout << "data saved to file: " << filename << endl;
	}
	else {
		cout << "error opening file: " << filename << endl;
	}
}

// deserialize employee data from a text file to vector
void loademployeesfromfile(vector<employee>& employees, const string& filename) {
	ifstream file(filename);

	if (file.is_open()) {
		employees.clear();

		string line;
		while (getline(file, line)) {
			employee emp;
			emp.deserialize(line);
			employees.push_back(emp);
		}

		file.close();
		cout << "data loaded from file: " << filename << endl;
	}
	else {
		cout << "error opening file: " << filename << endl;
	}
}
//____________________________________________________________________________________________________________________
class menuitem
{
private:
	string name;
	double price;
	string description;
	bool availaiblity;
	string category;
public:

	menuitem() : name(""), price(0.0), description(""), availaiblity(false), category("") {}

	void setname(std::string itemname) {
		name = itemname;
	}

	void setprice(double itemprice) {
		price = itemprice;
	}

	void setdescription(string desc) {
		description = desc;
	}

	void setcategory(string cat) {
		category = cat;
	}

	void setavailaibilty(bool aval) {
		availaiblity = aval;
	}

	string getname() const {
		return name;
	}

	string getcategory() const {
		return category;
	}

	double getprice() const {
		return price;
	}

	bool getavailaibilty() const {
		return availaiblity;
	}

	string getdescription() const {
		return description;
	}

	string serialize() const {
		return name + "*" + to_string(price) + "*" + description + "*" + (availaiblity ? "1" : "0") + "*" + category;
	}


	void deserialize(const string serializedstring) {
		istringstream iss(serializedstring);
		getline(iss, name, '*');
		iss >> price;
		iss.ignore();
		getline(iss, description, '*');

		string availabilitystr;
		getline(iss, availabilitystr, '*');
		availaiblity = (availabilitystr == "1");

		getline(iss, category, '*');
	}

};

//_________________________________________________________________________________________________________
//_________________________________________________________________________________________________________
//_________________________________________________________________________________________________________
//_________________________________________________________________________________________________________

void savemenuitemstofile(const vector<menuitem>& items, const string& filename) {
	ofstream file(filename);
	if (file.is_open()) {
		for (const auto& item : items) {
			file << item.serialize() << "\n";
		}
		file.close();
		cout << "menu items saved to " << filename << endl;
	}
	else {
		cout << "unable to open file: " << filename << endl;
	}
}

vector<menuitem> loadmenuitemsfromfile(const string& filename) {
	vector<menuitem> items;
	ifstream file(filename);
	if (file.is_open()) {
		string line;
		while (getline(file, line)) {
			menuitem item;
			item.deserialize(line);
			items.push_back(item);
		}
		file.close();
	}
	else {
		cout << "error: unable to open file: " << filename << endl;
	}
	return items;
}

vector<menuitem> loadedmenu; //declaring a global array
vector<employee> employees; //declaring second global array :(

int main() {
	loadedmenu = loadmenuitemsfromfile(filename); // load first arr from file
	loademployeesfromfile(employees,filename2); // load second array from file

	cout << "welcome to the resturant management system!" << endl;
	while (true)
	{
		displayoptions(0);
		int n;  
		cin >> n; 
		cin.ignore();
		if (n == 1)
		{
			managemenu();
		}
		else if (n==3)
		{
			manageemployees();
		}
		else if (n == 0)
		{
			system("cls");
			cout << "thanks for using our application!" << endl;
			break;
		}
	}
	return 0;
}

void displayoptions(int a) {

	if (a == 0) // main menu options
	{
		cout << "1) manage resturant menu" << endl;
		cout << "3) manage employees" << endl;
		cout << "0) exit program" << endl;
	}
	else if (a == 1)// managing resturant menu options
	{
		cout << "1) display current menu" << endl;
		cout << "2) add new item to menu" << endl;
		cout << "3) remove an item from menu" << endl;
		cout << "4) modidfy item details" << endl;
		cout << "5) exit menu managing and go back to main menu" << endl;
	}
	else if (a==2) //modifying item details (subset of managing menu)
	{
		cout << "1) change name" << endl;
		cout << "2) change price" << endl;
		cout << "3) change description" << endl;
		cout << "4) change availaibility" << endl;
		cout << "5) change category" << endl;
	}
	else if (a==3) // manage employee options
	{
		cout << "1) list all employees" << endl;
		cout << "2) hire new employee" << endl;
		cout << "3) mark attendance" << endl;
		cout << "4) check attendance" << endl;
		cout << "5) fire employee" << endl;
		cout << "6) change employee information" << endl;
		cout << "0) exit managing employees and go back to main menu" << endl;
	}
	else if (a==4) // change employee info options
	{
		cout << "1) change name" << endl;
		cout << "2) change position" << endl;
		cout << "3) change contact information" << endl;
		cout << "4) increase or decrease salary" << endl;
	}
}

void managemenu() {
	while (true)
	{

		system("cls");
		cout << "\t---manage your returant menu---" << endl;
		displayoptions(1);
		cout << "enter your option (number): " << endl;
		int option; cin >> option; // provide, with and make them select their option
		cin.ignore();
		loadedmenu = loadmenuitemsfromfile(filename);
		if (option == 1) // display current menu
		{
			for (const auto& item : loadedmenu) {
				cout << "item name: " << item.getname() << endl;
				cout << "category: " << item.getcategory() << endl;
				cout << "price: $" << item.getprice() << endl;
				cout << "description: " << item.getdescription() << endl;
				cout << "availability: " << (item.getavailaibilty() ? "available" : "not available") << endl;
				cout << "-----------------\n";
			}
			int n; cout << endl << "enter 0 to go back to main menu or anyother number to manage resturant menu: ";
			cin >> n;
			if (n==0)
			{
				break;
			}
		}
		else if (option == 2) // enter new item
		{
			string newitemname, newitemdescription, newitemcategory;
			double newitemprice;

			cout << "enter details for the new menu item:\n";
			cout << "name: ";
			getline(cin, newitemname);
			cout << "description: ";
			getline(cin, newitemdescription);
			cout << "category: ";
			getline(cin, newitemcategory);
			cout << "price: ";
			cin >> newitemprice;

			// create a new menuitem
			menuitem newitem;
			newitem.setname(newitemname);
			newitem.setdescription(newitemdescription);
			newitem.setcategory(newitemcategory);
			newitem.setprice(newitemprice);
			newitem.setavailaibilty(true); // assuming the new item is available

			// load menu items from file
			vector<menuitem> menuitems = loadmenuitemsfromfile(filename);

			// add the new item to the vector
			menuitems.push_back(newitem);

			// save the updated menu items to the file
			savemenuitemstofile(menuitems, filename);

			cout << "new item added and saved to the menu file.\n";

			int n; 
			cout << endl << "enter 0 to go back to main menu or anyother number to manage resturant menu: ";
			cin >> n;
			if (n == 0)
			{
				break;
			}
		}
		else if (option == 3)//     remove an item from menu permenantly
		{
			system("cls");
			cout << "warning: items deletion is permenant" << endl;
			cout << "enter 'y' to load item list or anyother key to skip ahead: ";
			char y; cin >> y;
			cin.ignore();
			vector<menuitem> loadedmenu = loadmenuitemsfromfile(filename);

			if (y == 'y' || y == 'Y')
			{
				int n = 0;
				for (const auto& item : loadedmenu)
				{
					cout << n++ << ")" << item.getname() << endl;
				}
			}
			string delitem;
			cout << "please enter the name of the item you want to delete: " << endl;
			getline(cin, delitem);

			auto it = remove_if(loadedmenu.begin(), loadedmenu.end(), [delitem](const menuitem item)
				{return (delitem == item.getname()) ? true : false; }); //i'm so surprised i wrote this myself lmao
			if (it == loadedmenu.end())
			{
				cout << "item " << delitem << " not found :(" << endl;
			}
			else
			{
				loadedmenu.erase(it, loadedmenu.end());
				cout << "item removed succesfully! :)" << endl;
			}

			savemenuitemstofile(loadedmenu, filename);
			int n; cout << endl << "enter 0 to go back to main menu or anyother number to manage resturant menu: ";
			cin >> n;
			if (n == 0)
			{
				break;
			}
		}
		else if (option == 4) {
			vector<menuitem> loadedmenu = loadmenuitemsfromfile(filename);
			system("cls");
			int index = 0; bool found = false;

			for (const auto& item : loadedmenu)
			{
				cout << ++index << ") " << item.getname() << endl;
			}


			cout << "enter the number of the item you want to modify: " << endl;
			int itemnum; cin >> itemnum; cin.ignore();

			if (itemnum >= 0 && itemnum <= index)
			{
				found = true;
			}

			if (found)
			{
				index = itemnum - 1;
				cout << "item found!\n" << "what do you want to modify about this item?\n";
				displayoptions(2);
				int n; cout << "enter your option by it's corresponding number: "; cin >> n; cin.ignore();

				if (n == 1)
				{
					cout << "enter new name: ";
					string newname; cin >> newname; cin.ignore();
					loadedmenu[index].setname(newname);
				}
				else if (n == 2)
				{
					cout << "enter new price: ";
					double newprice; cin >> newprice;
					loadedmenu[index].setprice(newprice);
				}
				else if (n == 3) {
					cout << "enter new description: ";
					cin.ignore(); string newdesc;
					getline(cin, newdesc);
					loadedmenu[index].setdescription(newdesc);
				}

				else if (n == 4)
				{
					cout << "enter 0 for not availaible and 1 for avaiaible";
					bool aval; cin >> aval;
					if (aval == 0 || aval == 1)
					{
						loadedmenu[index].setavailaibilty(aval);
					}
					else
						cout << "error: enter either 0 or 1!";
				}
				else if (n == 5)
				{
					cout << "enter new category: ";
					string newcat; cin >> newcat; cin.ignore();
					loadedmenu[index].setcategory(newcat);
				}
				savemenuitemstofile(loadedmenu, filename);
			}
			else
			{
				cout << "sorry the item name you entered was not found!" << endl
					<< "make sure spellings are correct, search is also case sensitive";
			}
			int n; cout << endl << "enter 0 to go back to main menu or anyother number to manage resturant menu: ";
			cin >> n;
			if (n == 0)
			{
				break;
			}
		}
		else if (option == 5) {
			system("cls");
			cout << "exited menu mangement succesfully!" << endl;
			break;
		}
		else
		{
			cout << "error: please choose from 1-5." << endl;
		}
	}
}

void manageemployees() {
	
	system("cls");
	while (true) {
		cout << "-manage your employees-" << endl;
		displayoptions(3);
		int option;
		cout << endl << "enter your option(number) : ";
		cin >> option;
		if (option == 1) // display employees
		{
			employees.clear();
			loademployeesfromfile(employees, filename2);
			for (employee item : employees) {
				item.dispempinfo();
				cout << "\n____________________________" << endl;
			}
		}
		else if (option == 2)   // hire new employee
		{
			system("cls");
			cout << "congratulations on hiring new employee\n" << "please enter the new employees details" << endl;
			employee newemp;
			
			string name;
			cout << "enter employee name: ";
			cin >> name;

			string position;
			cout << "enter employee position: ";
			cin >> position;

			string contacinfo;
			cout << "enter employee contact info: ";
			cin >> contacinfo; cin.ignore();

			int salary;
			cout << "enter employee salary: ";
			while (!(cin >> salary)) { //             validation check ewww
				cin.clear();  // clear the error flag
				cin.ignore(numeric_limits<streamsize>::max(), '\n');  // discard invalid input
				cout << "invalid input. please enter a numeric value for salary: ";
			}

			newemp.setname(name); newemp.setposition(position);
			newemp.setcontactinfo(contacinfo); newemp.setsalary(salary);
			
			employees.push_back(newemp);
			saveemployeestofile(employees, filename2);
		}
		else if (option == 3)   // mark attendance
		{
			ofstream outfile("attendance.txt",ios::app);
			cout << "\nwarning attendance can not be modified be carfeful\n\n";
			if (outfile.is_open()) {
				time_t now = time(0);
				tm* currentdate = localtime(&now);

				// adding date to the file
				outfile << (currentdate->tm_mday) << '/' << (currentdate->tm_mon + 1) << '/' << (currentdate->tm_year + 1900) << "|";

				for (employee emp : employees) {
					char attendance;
					cout << "is " << emp.getname() << " present? (y/n): ";
					cin >> attendance;

					// converting to 1 for present, 0 for absent
					int attendancecode = (attendance == 'y' || attendance == 'Y') ? 1 : 0;

					// write to file in the format: employeename|attendancecode+
					outfile << emp.getname() << "|" << attendancecode << "+";
				}

				outfile.close();
				cout << "attendance recorded and saved to attendance.txt.\n";
			}
			else {
				cout << "error opening file: attendance.txt\n";
			}
		}
		else if (option == 4) // reads attendance
		{
			string inputdate;
			cout << "enter the date you want to check attendance of (dd/mm/yy): ";
			cin >> inputdate;

			// validation checks are tiring ;(
			while (true) {
				cout << "enter the date (dd/mm/yy): ";
				cin >> inputdate;

				if (inputdate.length() == 8) {
					bool validformat = true;
					for (auto i = inputdate.begin(); i != inputdate.end(); ++i) {
						if (!isdigit(*i) && (i == inputdate.begin() + 2 || i == inputdate.begin() + 5)) {
							validformat = false;
							break;
						}
					}

					if (validformat) {
						break; // exit the loop if the input is in the correct format
					}
				}

				cout << "invalid date format. please enter the date in dd/mm/yy format.\n";
				cin.clear();    // clear input buffer to handle invalid input
				cin.ignore(numeric_limits<streamsize>::max(), '\n'); // ignore remaining characters in the buffer
			}

			ifstream infile("attendance.txt");
			if (infile.is_open()) {
				string line;
				while (getline(infile, line)) {
					// extract date from the line
					string currentdate = line.substr(0, 8);

					// check if the date matches the user input
					if (currentdate == inputdate) {
						cout << "attendance for " << inputdate << ":\n";
						// display attendance for each employee
						for (employee emp : employees) {
							size_t pos = line.find(emp.getname() + "|");
							if (pos != string::npos) { // checks if this shit actually exists
								int attendancecode = line[pos + emp.getname().length() + 1] - '0';
								cout << emp.getname() << ": " << (attendancecode ? "present" : "absent") << endl;
							}
						}
						return; // found and displayed attendance for the specified date
					}
				}

				cout << "no attendance found for the specified date.\n";
				infile.close();
			}
			else {
				cout << "error opening file: attendance.txt\n";
			}
		}
		else if (option == 5) // fire employee
		{
			loademployeesfromfile(employees, filename2); 
			cout << "\nwarning, firing an employee will delete all their data including orders completed and rating\n";
			int n = 1;
			cout << "choose an employee to fire by entering the number behind their name" << endl;
			for (employee emp : employees) {
				cout << n++ << ") " << emp.getname() << endl;
			}
			cout << endl << "enter number: ";
			cin >> n;
			n--;

			if (n >= 1 && n < (employees.size())) {
				// get fired lmao skill issue + ratio xd
				employees.erase(employees.begin() + n);

				cout << "employee fired successfully.\n";

			}
			else {
				cout << "invalid choice. no employee fired.\n"; //validation check ;(
			}
			saveemployeestofile(employees,filename2);
		}
		else if (option==6) // change employee details
		{
			system("cls");
			loademployeesfromfile(employees, filename2); int n = 0;
			for (employee emp : employees) {
				cout << ++n << ") " << emp.getname() << endl;
			}
			cout << "\nplease choose an employee to modify their details" << endl;
			bool c = true;
			do
			{
				cout << "enter your option (number behind their name): ";
				cin >> n; 
				if (n<1 || n>employees.size() + 1)
				{
					cout << "please choose a correct number from the list displayed above" << endl; 
					c = false;
				}
				else
				{
					c = true;
				}
			} while (c==false);
			system("cls");
			cout << "what do you want to change about employee: " << employees[--n].getname() << endl;
			displayoptions(4); int n2;
			do {
				cout << "\nchoose your option by entering it's number: ";
				cin >> n2;
				if (n2 < 1 || n2>4)
				{
					cout << "please choose a correct number from the list displayed above" << endl;
					c = false;
				}
				else
				{
					c = true;
				}
			} while (!c);
			cin.ignore();
			if (n2 == 1) {
				cout << "please enter new name for your employee: ";
				string newname;
				getline(cin, newname);
				employees[n].setname(newname);
				saveemployeestofile(employees, filename2);
			}
			else if (n2 == 2) {
				cout << "please enter new position for your employee: ";
				string newpos;
				getline(cin, newpos);
				employees[n].setposition(newpos);
				saveemployeestofile(employees, filename2);
			}
			else if (n2 == 3) {
				cout << "please enter new contact info for your employee: ";
				string newc;
				getline(cin, newc);
				employees[n].setcontactinfo(newc);
				saveemployeestofile(employees, filename2);
			}
			else if (n2 == 4) {
				cout << "please enter salary adjustment (+ve for inc and -ve for dec) in pakistani rupees: ";
				int news;
				cin >> news;
				employees[n].setsalary(news);
				saveemployeestofile(employees, filename2);
			}
			
		}
		else if (option == 0) // go back to main menu
		{
			break;
		}
		else
		{
			cout << "please enter an integer between 1 to 6" << endl;
		}

		cout << endl << "do you wish to continue managing employees (enter y) or not?(enter any char): ";
		char opt; cin >> opt;
		if (!(opt=='y' || opt=='Y'))
		{
			break;
		}
	}
}