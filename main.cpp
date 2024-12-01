#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include <sstream>		// to work with strings as streams
#include <algorithm>	// std::sort
#include <limits>

using namespace std;

// Befine a structure to represent each car entry
struct Vehicle
{
	string manufacturer;
	string model;
	double price;
	double power;
	int year_of_manufacturer;
};

bool isValidNumber(const string &input);
void addVehicle(vector<Vehicle> &vehicles, const string &list_of_vehicles);
void searchByManufacturer(const vector<Vehicle> &vehicles);
void searchByModel(const vector<Vehicle>& vehicle);
vector<Vehicle> readVehiclesFromFile(const string& filename);
void searchByPrice(const vector<Vehicle>& vehicles);
void searchByPower(const vector<Vehicle>& vehicles);
void searchByYearOfManufacturer(const vector<Vehicle>& vehicles);
void showLibrary(vector<Vehicle>& vehicles);
void modifyVehicle(vector<Vehicle>& vehicles, const string& filename);
void deleteVehicle(vector<Vehicle>& vehicles, const string& filename);
void sortLibrary(vector<Vehicle>& vehicles, const string& filename);
bool compareByManufacturer(const Vehicle& a, const Vehicle& b);
bool compareByYear(const Vehicle& a, const Vehicle& b);
bool compareByPrice(const Vehicle& a, const Vehicle& b);
void printLine();
void printMenu();


int main() {
	const string filename = "list_of_vehicles.txt";
	vector<int> valid_numbers = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, -1};    // this vector made of valid integers
                                                                        // that will help to prevent invalid inputs from the user.
	int choice = 0;

	cout << "Hello! I'm your Library Assistant. " << endl;
	printLine();

	while (choice != -1) {
        vector<Vehicle> vehicles = readVehiclesFromFile("list_of_vehicles.txt");

        printLine();
        printMenu();
        printLine();

        while (true) {
            cout << "Choose from 1 to 10, or '-1' to exit: ";
            string input;
            getline(cin, input);


            if (isValidNumber(input)) {
                // Convert the valid input to an integer
                choice = stoi(input);

                if (find(valid_numbers.begin(), valid_numbers.end(), choice) != valid_numbers.end()) {
                    break;
                } else {
                    cout << "Invalid choice. Try again." << "\n\n";
                }
            } else {
                cout << "Invalid choice. Try again." << "\n\n";
            }
        }
		
		printLine();

		switch (choice) {
		case 1:
			addVehicle(vehicles, filename);
			break;
		case 2:
			searchByManufacturer(vehicles);
			break;
		case 3:
			searchByModel(vehicles);
			break;
		case 4:
			searchByPrice(vehicles);
			break;
		case 5:
			searchByPower(vehicles);
			break;
		case 6:
			searchByYearOfManufacturer(vehicles);
			break;
		case 7:
			showLibrary(vehicles);
			break;
		case 8:
			modifyVehicle(vehicles, filename);
			break;
		case 9:
			deleteVehicle(vehicles, filename);
			break;
		case 10:
			sortLibrary(vehicles, filename);
			break;
		case -1:
			cout << "\nLeaving the Library, thank you!" << endl;
            break;
		default:
			cout << "Invalid input, please try again. " << endl;
            break;
        }
	}

	return 0;
}

bool isValidNumber(const string &input) {
    // Check if the entire string is numeric (only digits and optional leading '-' for negative numbers)
    if (input.empty()) return false;

    int start = 0;
    if (input[0] == '-') start = 1;  // Allow for negative numbers

    for (int i = start; i < input.length(); ++i) {
        if (!isdigit(input[i])) {
            return false;  // Contains non-digit characters
        }
    }

    return true;  // All characters are digits (or a leading '-')
}

void addVehicle(vector<Vehicle>& vehicles, const string& filename) {
	Vehicle new_vehicle;
	// cout << "Please enter the vehicle's manufacturer: ";
	// cin.ignore();
	while (true) {
		string input;
		cout << "Please enter the vehicle's manufacturer: ";
		getline(cin, input);
        

        bool is_valid = true;  // Flag to track if input is valid

		for (char ch : input)
		{
			if (!isalpha(ch))
			{
                is_valid = false;
                break;
			}
		}

        if (is_valid) {
            new_vehicle.manufacturer = input;
            break;
        }
        else {
            cout << "The manufacturer's name have to contain only letters." << "\n\n";
        }
	}

    while (true) {
        cout << "Please enter the vehicle's model: ";
        string input;
        getline(cin, input);

        if (!input.empty()) {
            new_vehicle.model = input;
            break;
        } else {
            cout << "Invalid input. Please try again." << "\n\n";
        } 
    }

	while (true) {
        string input;
        cout << "Please enter the vehicle's price: ";
        getline(cin, input);

        bool is_valid = true;

        for (char ch : input) 
        {
            if (isdigit(ch))
            {
                is_valid = false;
                break;
            }
        }

        if (!is_valid) {
            double price = stod(input);
            new_vehicle.price = price;
            break;
        }
        else if (input.empty()) {
            cout << "Price can't be empty. Please try again.";
        }
        else {
            cerr << "Invalid input. Please try again" << "\n\n";
        }
    }

    while (true) {
        string input;
        cout << "Please enter the vehicle's power: ";
        getline(cin, input);

        bool is_valid = true;

        for (char ch : input) 
        {
            if (isdigit(ch))
            {
                is_valid = false;
                break;
            }
        }

        if (!is_valid) {
            double power = stod(input);
            new_vehicle.power = power;
            break;
        }
        else if (input.empty()) {
            cout << "Power can't be empty. Please try again.";
        }
        else {
            cout << "Invalid input. Please try again" << "\n\n";
        }
    }

    while (true) {
        string input;
        cout << "Please enter the vehicle's year of manufacturer: ";
        getline(cin, input);

        bool is_valid = false;

        for (char ch : input){
            if (isdigit(ch))
            {
                is_valid = true;
                break;
            }
        }

        if (is_valid) {
            int year = stoi(input);
            new_vehicle.year_of_manufacturer = year;
            break;
        }
        else if (input.empty()) {
            cout << "Invalid input. Year of manufacturer can't be empty." << "\n\n";
        }
        else {
            cout << "Invalid input. Please try again." << "\n\n";
        }
    }

	// Write the new vehicle to the file
	ofstream outputFile(filename, std::ios::app); // Open the file in append mode
	if (outputFile.is_open()) {
		outputFile << new_vehicle.manufacturer << "\t" << new_vehicle.model << "\t" 
				   << new_vehicle.price << "\t" << new_vehicle.power << "\t" << new_vehicle.year_of_manufacturer << endl;
		outputFile.close();
		cout << '\n' << "New vehicle added and written to the file successfully." << "\n" << endl;
	}
	else {
		cerr << "Error opening the file for writing." << endl;
	}
}

// fucntion to search for vehicles by manufacturer
void searchByManufacturer(const vector<Vehicle>& vehicles)
{
	vector<Vehicle> result;
	string manufacturertofind;
	cout << "Please enter the manufacturer's name whose vehicles you want to find. ";
	cin >> manufacturertofind;
	
	// cin.ignore(numeric_limits<streamsize>::max(), '\n');
	// getline(cin, manufacturertofind);

	transform(manufacturertofind.begin(), manufacturertofind.end(), manufacturertofind.begin(), ::tolower);	// convert to lowercase

	// convert name of the manufacturer from the database into lowercase to compare with inputed one by user.
	for (const Vehicle& vehicle : vehicles) {
		string manufacturerLowerCase = vehicle.manufacturer;
		transform(manufacturerLowerCase.begin(), manufacturerLowerCase.end(), manufacturerLowerCase.begin(), ::tolower);

		if (manufacturerLowerCase == manufacturertofind) {
			result.push_back(vehicle);
		}
	}

	if (result.empty()) {
		cout << "No vehicles found for manufacturer '" << manufacturertofind << "'." << endl;
	}
	else {
		cout << "Vehicles by manufacturer '" << manufacturertofind << "':" << endl;
		for (const Vehicle& vehicles : result) {
			cout << vehicles.manufacturer << "\t" << vehicles.model << "\t"
				<< vehicles.price << "\t" << vehicles.power << "\t" << vehicles.year_of_manufacturer << endl;
		}
	}
}

vector<Vehicle> readVehiclesFromFile(const string& filename) {
	vector<Vehicle> vehicles;
	ifstream file(filename);

	if (!file.is_open())
	{
		cerr << "Error opening file: " << filename << endl;
	}

	string line;
	while (getline(file, line)) {
		Vehicle vehicle;
		stringstream iss(line);

		getline(iss, vehicle.manufacturer, '\t');
		getline(iss, vehicle.model, '\t');

		/*!!!!*/
		iss >> vehicle.price;
		iss >> vehicle.power;
		iss >> vehicle.year_of_manufacturer;

		vehicles.push_back(vehicle);
	}
	file.close();
	return vehicles;
}

// fucntion to search for vehicles by model
void searchByModel(const vector<Vehicle>& vehicles)
{
	vector<Vehicle> result;
	string modeltofind;
	//cin.ignore();
	cout << "Please enter the model's name whose vehicles you want to find. ";
	/*getline(cin, modeltofind);
	*/
	cin >> modeltofind;

	transform(modeltofind.begin(), modeltofind.end(), modeltofind.begin(), ::tolower);	// convert to lowercase

	// convert name of the manufacturer from the database into lowercase to compare with inputed one by user.
	for (const Vehicle& vehicle : vehicles) {
		string modelLowerCase = vehicle.model;
		transform(modelLowerCase.begin(), modelLowerCase.end(), modelLowerCase.begin(), ::tolower);

		if (modelLowerCase == modeltofind) {
			result.push_back(vehicle);
		}
	}

	if (result.empty()) {
		cout << "No vehicles found for manufacturer '" << modeltofind << "'." << endl;
	}
	else {
		cout << "Vehicles by manufacturer '" << modeltofind << "':" << endl;
		for (const Vehicle& vehicles : result) {
			cout << vehicles.manufacturer << "\t" << vehicles.model << "\t"
				<< vehicles.price << "\t" << vehicles.power << "\t" << vehicles.year_of_manufacturer << endl;
		}
	}
}

// fucntion to search for vehicles by model
void searchByPrice(const vector<Vehicle>& vehicles)
{
	vector<Vehicle> result;
	double pricetofind;
	//cin.ignore();
	cout << "Please enter the price of vehicles you want to find: ";
	cin >> pricetofind;

	for (const Vehicle& vehicle : vehicles) {
		if (vehicle.price == pricetofind) {
			result.push_back(vehicle);
		}
	}

	if (result.empty()) {
		cout << "No vehicles found by price '" << pricetofind << "'." << endl;
	}
	else {
		cout << "Vehicles by price '" << pricetofind << "':" << endl;
		for (const Vehicle& vehicles : result) {
			cout << vehicles.manufacturer << "\t" << vehicles.model << "\t"
				<< vehicles.price << "\t" << vehicles.power << "\t" << vehicles.year_of_manufacturer << endl;
		}
	}
}

// fucntion to search for vehicles by model
void searchByPower(const vector<Vehicle>& vehicles)
{
	vector<Vehicle> result;
	double powertofind;
	//cin.ignore();
	cout << "Please enter the power of vehicles you want to find: ";

	cin >> powertofind;

	for (const Vehicle& vehicle : vehicles) {
		if (vehicle.power == powertofind) {
			result.push_back(vehicle);
		}
	}

	if (result.empty()) {
		cout << "No vehicles found by power '" << powertofind << "'." << endl;
	}
	else {
		cout << "Vehicles by power '" << powertofind << "':" << endl;
		for (const Vehicle& vehicles : result) {
			cout << vehicles.manufacturer << "\t" << vehicles.model << "\t"
				<< vehicles.price << "\t" << vehicles.power << "\t" << vehicles.year_of_manufacturer << endl;
		}
	}
}

void searchByYearOfManufacturer(const vector<Vehicle>& vehicles)
{
	vector<Vehicle> result;
	int yeartofind;
	//cin.ignore();
	cout << "Please enter the year of manufacturer of vehicles you want to find: ";

	cin >> yeartofind;

	for (const Vehicle& vehicle : vehicles) {
		if (vehicle.year_of_manufacturer == yeartofind) {
			result.push_back(vehicle);
		}
	}

	if (result.empty()) {
		cout << "No vehicles found by year of manufacturer '" << yeartofind << "'." << endl;
	}
	else {
		cout << "Vehicles by year of manufacturer'" << yeartofind<< "':" << endl;
		for (const Vehicle& vehicles : result) {
			cout << vehicles.manufacturer << "\t" << vehicles.model << "\t"
				<< vehicles.price << "\t" << vehicles.power << "\t" << vehicles.year_of_manufacturer << endl;
		}
	}
}

void showLibrary(vector<Vehicle>& vehicles) {
	if (vehicles.size() == 0){
		cout << "The library is empty, you should add a book at first. " << endl;
	}
	else {
		for (int i = 0, n = vehicles.size(); i < n; i++) {
			cout << " #" << i + 1 << "  ";
			cout << "Manufacturer: " << vehicles[i].manufacturer << "\n";
			cout << "	Model: " << vehicles[i].model << "\n";
			cout << "	Price: " << vehicles[i].price << "\n";
			cout << "	Power: " << vehicles[i].power << "\n";
			cout << "	Year of manufacturer: " << vehicles[i].year_of_manufacturer << "\n\n";
		}
	}
}

void modifyVehicle(vector<Vehicle>& vehicles, const string& filename) {
	int vehicleIndex;
	cout << "Enter the index of the vehicle you want to modify: ";
	cin >> vehicleIndex;

	if ((vehicleIndex - 1) < 0 || (vehicleIndex - 1) >= vehicles.size()) {
		cout << "Invalid vehicle index. There is no such book number in the library. " << endl;
		return;
	}

	Vehicle& vehicleToModify = vehicles[vehicleIndex - 1];

	char ch = '\0';
	while (ch != 'q') {
		cout << "Please choose what you want to modify: 1 - manufacturer," 
			    "2 - model, 3 - price, 4 - power, 5 - year of manufacturer; or 'q' to exit. " << '\n';
		cin >> ch;
		switch (ch) {
		case '1':
			cout << "Currect Manufacturer: " << vehicleToModify.manufacturer << endl;
			cout << "Enter the new author: ";
			cin.ignore(); // clear the newline character left in the input buffer
			getline(cin, vehicleToModify.manufacturer);
			break;
		case '2':
			cout << "Current Model: " << vehicleToModify.model << endl;
			cout << "Enter the new model: ";
			cin.ignore();
			getline(cin, vehicleToModify.model);
			break;
		case '3':
			cout << "Current Price: " << vehicleToModify.price << endl;
			cout << "Enter the price: ";
			cin.ignore();
			cin >> vehicleToModify.price;
			break;
		case '4':
			cout << "Current Power: " << vehicleToModify.power << endl;
			cout << "Enter the power: ";
			cin.ignore();
			cin >> vehicleToModify.power;
			break;
		case '5':
			cout << "Current year of manufacturer: " << vehicleToModify.year_of_manufacturer<< endl;
			cout << "Enter the year of manufacturer: ";
			cin.ignore();
			cin >> vehicleToModify.year_of_manufacturer;
			break;
		default:
			if (ch == 'q') cout << '\n' << "Leaving the Library, thank you! " << endl;
			else cout << "Invalid input, please try again. " << endl;
		}
	}
	ofstream outputFile(filename);	// Update the file with the modified vehicle information

	if (!outputFile.is_open()) {
		cerr << "Error opening the file of for writing." << endl;
		return;
	}
	// now we have to rewrite the entire library to the file so that the file contains the updated information
	for (const Vehicle& vehicle : vehicles) {
		outputFile << vehicle.manufacturer << '\t' << vehicle.model << "\t"
			<< vehicle.price << "\t" << vehicle.power << "\t" << vehicle.year_of_manufacturer << endl;
	}
	outputFile.close();
	cout << '\n';
	cout << "Book modified and updated in the file successfully." << endl;
}

void deleteVehicle(vector<Vehicle>& vehicles, const string& filename) {
	int vehicleIndex;
	cout << "Enter the index of the vehicle you want to delete: ";
	cin >> vehicleIndex;

	if ((vehicleIndex - 1) < 0 || (vehicleIndex - 1) >= vehicles.size()) {
		cout << "Invalid vehicle index. There is no such book number in the library. " << endl;
		return;
	}

	Vehicle& vehicleToDelete = vehicles[vehicleIndex - 1];
	cout << "Deleting the following vehicle: " << endl;
	cout << "Manufacturer: " << vehicleToDelete.manufacturer << endl;
	cout << "Model: " << vehicleToDelete.model << endl;
	cout << "Price: " << vehicleToDelete.price << endl;
	cout << "Power: " << vehicleToDelete.power << endl;
	cout << "Year of manufacturer: " << vehicleToDelete.year_of_manufacturer<< endl;

	vehicles.erase(vehicles.begin() + (vehicleIndex - 1)); // Erase the vehicle from the vector

	ofstream outputFile(filename);

	if (!outputFile.is_open()) {
		cerr << "Error opening the file for writing. " << endl;
		return;
	}

	for (const Vehicle& vehicle : vehicles) {
		outputFile << vehicle.manufacturer << "\t" << vehicle.model << "\t"
			<< vehicle.price << "\t" << vehicle.power << "\t" << vehicle.year_of_manufacturer << endl;
	}
	outputFile.close();
	cout << "Book deleted and file updated successfully." << endl;
}

bool compareByManufacturer(const Vehicle& a, const Vehicle& b) {
	return a.manufacturer < b.manufacturer;
}

bool compareByYear(const Vehicle& a, const Vehicle& b) {
	return a.manufacturer < b.manufacturer;
}

void sortLibrary(vector<Vehicle>& vehicles, const string& filename) {
	char ch = '\0';
	while (ch != 'q') {
		cout << "Please choose how you want to sort the Library: 1 - by manufacturer, 2 - by year or 'q' to exit when you're done with sorting. " << "\n";
		cin >> ch;
		switch (ch) {
		case '1':
			sort(vehicles.begin(), vehicles.end(), compareByManufacturer);
			showLibrary(vehicles);
			break;
		case '2':
			sort(vehicles.begin(), vehicles.end(), compareByYear);
			showLibrary(vehicles);
			break;
		default:
			if (ch == 'q') cout << "\n" << "Leaving the Library, thank you! " << endl;
			else cout << "Invalid input, please try again. " << endl;
		}
	}
	ofstream outputFile(filename); // Update the file with the sorted information

	if (!outputFile.is_open()) {
		cerr << "Error opening the file for writing." << endl;
		return;
	}
	// now we have to rewrite the entire library to the file so that the file contains the updated information
	for (const Vehicle& vehicle : vehicles) {
		outputFile << vehicle.manufacturer << '\t' << vehicle.model << '\t' << vehicle.price
				   << '\t' << vehicle.power << '\t' << vehicle.year_of_manufacturer << endl;
	}

	outputFile.close();
	cout << "\n";
	cout << "The Library is sorted and updated in the file successfully." << endl;
}

void printLine() {
	cout << "\n" << "----------------------------------------" << endl;
}

void printMenu() {
	cout << "1. Add a new vehicle to the library. " << endl;
	cout << "2. Search a vehicle by the manufacturer. " << endl;
	cout << "3. Search a vehicle by the model. " << endl;
	cout << "4. Search a vehicle by the price. " << endl;
	cout << "5. Search a vehicle by the power. " << endl;
	cout << "6. Search a vehicle by the year of manufacture. " << endl;
	cout << "7. See the entire library. " << endl;
	cout << "8. Modify a vehicle in the library. " << endl;
	cout << "9. Delete a vehicle. " << endl;
	cout << "10. Sort the library. " << endl;
	cout << "----------------------------------------" << endl;
}
