#include <iostream>
#include <string>
#include <windows.h>
#include <fstream>
#include <sstream>
#include <vector>
#include <queue>
#include <map>
#include <limits>
#include <stdexcept>
#include <ctime>

using namespace std;

class User {
public:
    string username, password, email;
    User(string uname, string pwd, string mail) : username(uname), password(pwd), email(mail) {}
    static bool isUsernameTaken(const string& username);
    static void signup();
    static bool login(const string& username, const string& password);
    static void forgotPassword();
    void editUserData();
};

class Admin {
public:
    static bool login(const string& username, const string& password);
    static void manageRoutes();
    static void manageStations();
    static void manageBuses();
    static void manageFare();
};

class TransportSystem {
public:
    map<string, vector<pair<string, int>>> routes; // Adjacency list for routes (station, (destination, distance))
    map<string, int> fareChart; // Fare from one station to another
    map<string, map<int, bool>> reservations; // Reservations (bus number, seat availability)

    void loadRoutes();
    void loadFares();
    void loadReservations();
    void saveRoutesToFile();
    void saveFaresToFile();
    void saveReservationsToFile();
    void showRoutes();
    void showFare();
    void reserveSeat();
    void viewReservations();
    void cancelReservation();
    void findShortestPath();
    void searchRoutes(const string& query);
    void searchStations(const string& query);
    void searchFares(const string& start, const string& end);
    void logError(const string& errorMsg);
};

// Function Declarations
void welcome();
void loading();
void userPanel(const string& username);
void adminPanel();
void exitProgram();
void validateInput(const string& input);
void validateNumericInput(const string& input);
void validateNonEmptyInput(const string& input);
void validatePositiveInput(int input);

// Implementation of User class methods
bool User::isUsernameTaken(const string& username) {
    ifstream file("userData.txt");
    string line, tempUsername;
    while (getline(file, line)) {
        stringstream ss(line);
        ss >> tempUsername;
        if (tempUsername == username) {
            return true;
        }
    }
    return false;
}

void User::signup() {
    string username, password, email;
    cout << "Username: ";
    cin >> username;

    if (isUsernameTaken(username)) {
        cout << "Username is already taken. Please choose a different username." << endl;
        return;
    }

    cout << "Password: ";
    cin >> password;
    cout << "Email: ";
    cin >> email;

    ofstream file("userData.txt", ios::app); // append mode to add new user data to the file without deleting the previous data in the file
    file << username << " " << password << " " << email << endl;
    file.close();

    cout << "User registered successfully!" << endl;
}

bool User::login(const string& username, const string& password) {
    ifstream file("userData.txt");
    if (file.is_open()) {
        string u, p, e;
        while (file >> u >> p >> e) {
            if (u == username && p == password) {
                return true;
            }
        }
    }
    return false;
}

void User::forgotPassword() {
    ifstream file("userData.txt");
    ofstream tempFile("temp.txt");
    string line, username, password, email, inputUsername, newPassword;
    bool userFound = false;

    cout << "Enter your username: ";
    cin >> inputUsername;

    while (getline(file, line)) {
        stringstream ss(line);
        ss >> username >> password >> email;
        if (username == inputUsername) {
            userFound = true;
            cout << "Enter new password: ";
            cin >> newPassword;
            password = newPassword;
        }
        tempFile << username << " " << password << " " << email << endl;
    }

    file.close();
    tempFile.close();

    remove("userData.txt");
    rename("temp.txt", "userData.txt");

    if (userFound) {
        cout << "Password reset successfully!" << endl;
    } else {
        cout << "Username not found." << endl;
    }
}

void User::editUserData() {
    ifstream file("userData.txt");
    ofstream tempFile("temp.txt");
    string line, username, password, email;
    bool userFound = false;

    while (getline(file, line)) {
        stringstream ss(line);
        ss >> username >> password >> email;
        if (username == this->username) {
            userFound = true;
            cout << "Edit Username (current: " << username << "): ";
            cin >> username;
            cout << "Edit Password (current: " << password << "): ";
            cin >> password;
            cout << "Edit Email (current: " << email << "): ";
            cin >> email;
        }
        tempFile << username << " " << password << " " << email << endl;
    }

    file.close();
    tempFile.close();

    remove("userData.txt");
    rename("temp.txt", "userData.txt");

    if (userFound) {
        cout << "User data updated successfully!" << endl;
    } else {
        cout << "User not found." << endl;
    }
}

// Implementation of Admin class methods
bool Admin::login(const string& username, const string& password) {
    // Here you can hardcode the admin credentials or read from a secure file
    return (username == "admin" && password == "admin123");
}

void Admin::manageRoutes() {
    string station, destination;
    int distance;
    cout << "Enter the route's station: ";
    cin >> station;
    validateNonEmptyInput(station);
    cout << "Enter the route's destination: ";
    cin >> destination;
    validateNonEmptyInput(destination);
    cout << "Enter the distance between them: ";
    cin >> distance;
    validatePositiveInput(distance);

    // Update routes map
    TransportSystem ts;
    ts.routes[station].push_back(make_pair(destination, distance));
    ts.routes[destination].push_back(make_pair(station, distance)); // Assuming the route is bidirectional

    // Save routes to file
    ofstream file("routes.txt", ios::app);
    file << station << " " << destination << " " << distance << endl;
    file.close();

    cout << "Route added successfully!" << endl;
}

void Admin::manageStations() {
    string station;
    cout << "Enter the station to add: ";
    cin >> station;
    validateNonEmptyInput(station);
    TransportSystem ts;
    if (ts.routes.find(station) == ts.routes.end()) {
        ts.routes[station] = vector<pair<string, int>>();
        cout << "Station added successfully!" << endl;
    } else {
        cout << "Station already exists!" << endl;
    }
}

void Admin::manageBuses() {
    string busNumber;
    cout << "Enter the bus number to add: ";
    cin >> busNumber;
    validateNonEmptyInput(busNumber);
    TransportSystem ts;
    if (ts.reservations.find(busNumber) == ts.reservations.end()) {
        ts.reservations[busNumber] = map<int, bool>(); // Initialize seat availability map
        cout << "Bus added successfully!" << endl;
    } else {
        cout << "Bus already exists!" << endl;
    }
}

void Admin::manageFare() {
    string start, end;
    int fare;
    cout << "Enter the starting station: ";
    cin >> start;
    validateNonEmptyInput(start);
    cout << "Enter the destination station: ";
    cin >> end;
    validateNonEmptyInput(end);
    cout << "Enter the fare between them: ";
    cin >> fare;
    validatePositiveInput(fare);

    TransportSystem ts;
    ts.fareChart[start + end] = fare;

    // Save fare to file
    ofstream file("fare.txt", ios::app);
    file << start << " " << end << " " << fare << endl;
    file.close();

    cout << "Fare added successfully!" << endl;
}

// Implementation of TransportSystem class methods
void TransportSystem::loadRoutes() {
    ifstream file("routes.txt");
    string station, destination;
    int distance;
    while (file >> station >> destination >> distance) {
        routes[station].push_back(make_pair(destination, distance));
        routes[destination].push_back(make_pair(station, distance));
    }
    file.close();
}

void TransportSystem::loadFares() {
    ifstream file("fare.txt");
    string start, end;
    int fare;
    while (file >> start >> end >> fare) {
        fareChart[start + end] = fare;
    }
    file.close();
}

void TransportSystem::loadReservations() {
    ifstream file("reservations.txt");
    string busNumber;
    int seatNumber;
    bool isReserved;
    while (file >> busNumber >> seatNumber >> isReserved) {
        reservations[busNumber][seatNumber] = isReserved;
    }
    file.close();
}

void TransportSystem::saveRoutesToFile() {
    ofstream file("routes.txt");
    for (const auto& route : routes) {
        for (const auto& dest : route.second) {
            file << route.first << " " << dest.first << " " << dest.second << endl;
        }
    }
    file.close();
}

void TransportSystem::saveFaresToFile() {
    ofstream file("fare.txt");
    for (const auto& fare : fareChart) {
        file << fare.first.substr(0, fare.first.size() / 2) << " "
             << fare.first.substr(fare.first.size() / 2) << " "
             << fare.second << endl;
    }
    file.close();
}

void TransportSystem::saveReservationsToFile() {
    ofstream file("reservations.txt");
    for (const auto& bus : reservations) {
        for (const auto& seat : bus.second) {
            file << bus.first << " " << seat.first << " " << seat.second << endl;
        }
    }
    file.close();
}

void TransportSystem::showRoutes() {
    for (const auto& route : routes) {
        cout << "Station: " << route.first << endl;
        for (const auto& dest : route.second) {
            cout << "  -> " << dest.first << " (Distance: " << dest.second << " km)" << endl;
        }
    }
}

void TransportSystem::showFare() {
    string start, end;
    cout << "Enter the starting station: ";
    cin >> start;
    validateNonEmptyInput(start);
    cout << "Enter the destination station: ";
    cin >> end;
    validateNonEmptyInput(end);

    if (fareChart.find(start + end) != fareChart.end()) {
        cout << "The fare from " << start << " to " << end << " is: " << fareChart[start + end] << " PKR" << endl;
    } else {
        cout << "Fare information for the specified route is not available." << endl;
    }
}

void TransportSystem::reserveSeat() {
    string busNumber;
    int seatNumber;
    cout << "Enter the bus number: ";
    cin >> busNumber;
    validateNonEmptyInput(busNumber);
    cout << "Enter the seat number to reserve: ";
    cin >> seatNumber;
    validatePositiveInput(seatNumber);

    if (reservations[busNumber][seatNumber]) {
        cout << "Seat already reserved!" << endl;
    } else {
        reservations[busNumber][seatNumber] = true;
        saveReservationsToFile();
        cout << "Seat reserved successfully!" << endl;
    }
}

void TransportSystem::viewReservations() {
    for (const auto& bus : reservations) {
        cout << "Bus Number: " << bus.first << endl;
        for (const auto& seat : bus.second) {
            cout << "  Seat Number: " << seat.first << " - " << (seat.second ? "Reserved" : "Available") << endl;
        }
    }
}

void TransportSystem::cancelReservation() {
    string busNumber;
    int seatNumber;
    cout << "Enter the bus number: ";
    cin >> busNumber;
    validateNonEmptyInput(busNumber);
    cout << "Enter the seat number to cancel reservation: ";
    cin >> seatNumber;
    validatePositiveInput(seatNumber);

    if (!reservations[busNumber][seatNumber]) {
        cout << "Seat is not reserved!" << endl;
    } else {
        reservations[busNumber][seatNumber] = false;
        saveReservationsToFile();
        cout << "Reservation cancelled successfully!" << endl;
    }
}

void TransportSystem::findShortestPath() {
    string start, end;
    cout << "Enter the starting station: ";
    cin >> start;
    validateNonEmptyInput(start);
    cout << "Enter the destination station: ";
    cin >> end;
    validateNonEmptyInput(end);

    if (routes.find(start) == routes.end() || routes.find(end) == routes.end()) {
        cout << "One or both stations do not exist." << endl;
        return;
    }

    map<string, int> distances;
    map<string, string> previous;
    for (const auto& route : routes) {
        distances[route.first] = numeric_limits<int>::max();
    }
    distances[start] = 0;

    auto compare = [&distances](const string& a, const string& b) {
        return distances[a] > distances[b];
    };
    priority_queue<string, vector<string>, decltype(compare)> pq(compare);
    pq.push(start);

    while (!pq.empty()) {
        string current = pq.top();
        pq.pop();

        for (const auto& neighbor : routes[current]) {
            int newDist = distances[current] + neighbor.second;
            if (newDist < distances[neighbor.first]) {
                distances[neighbor.first] = newDist;
                previous[neighbor.first] = current;
                pq.push(neighbor.first);
            }
        }
    }

    if (distances[end] == numeric_limits<int>::max()) {
        cout << "No path found from " << start << " to " << end << "." << endl;
    } else {
        cout << "Shortest path from " << start << " to " << end << ":" << endl;
        string path = end;
        while (path != start) {
            cout << path << " <- ";
            path = previous[path];
        }
        cout << start << endl;
        cout << "Total distance: " << distances[end] << " km" << endl;
    }
}

void TransportSystem::searchRoutes(const string& query) {
    cout << "Searching for routes containing '" << query << "':" << endl;
    for (const auto& route : routes) {
        if (route.first.find(query) != string::npos) {
            cout << "Station: " << route.first << endl;
            for (const auto& dest : route.second) {
                cout << "  -> " << dest.first << " (Distance: " << dest.second << " km)" << endl;
            }
        }
    }
}

void TransportSystem::searchStations(const string& query) {
    cout << "Searching for stations containing '" << query << "':" << endl;
    for (const auto& route : routes) {
        if (route.first.find(query) != string::npos) {
            cout << "Station: " << route.first << endl;
        }
    }
}

void TransportSystem::searchFares(const string& start, const string& end) {
    string key = start + end;
    if (fareChart.find(key) != fareChart.end()) {
        cout << "The fare from " << start << " to " << end << " is: " << fareChart[key] << " PKR" << endl;
    } else {
        cout << "Fare information for the specified route is not available." << endl;
    }
}

void TransportSystem::logError(const string& errorMsg) {
    ofstream file("error.log", ios::app);
    time_t now = time(0);
    char* dt = ctime(&now);
    file << dt << ": " << errorMsg << endl;
    file.close();
}

// Miscellaneous Functions
void welcome() {
    system("cls");
    system("color D"); // for the color of the text
    cout << "\n\n\n\n\n\n\n\n\t\t\t\t\t*************************************************************************************************\n";
    cout << "\t\t\t\t\t^^|+|~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~|+|^^\n";
    cout << "\t\t\t\t\t^^|+|                                           	                                    |+|^^\n";
    cout << "\t\t\t\t\t^^|+|                                           		                            |+|^^\n";
    cout << "\t\t\t\t\t^^|+|                                           		                            |+|^^\n";
    cout << "\t\t\t\t\t^^|+|                                           	                                    |+|^^\n";
    cout << "\t\t\t\t\t^^|+|                                           	                                    |+|^^\n";
    cout << "\t\t\t\t\t^^|+|                                           		                            |+|^^\n";
    cout << "\t\t\t\t\t^^|+|                                       WELCOME  TO                                     |+|^^\n";
    cout << "\t\t\t\t\t^^|+|                                          (-_-)                                        |+|^^\n";
    cout << "\t\t\t\t\t^^|+|                                  PUBLIC TRANSPORT SYSTEM                              |+|^^\n";
    cout << "\t\t\t\t\t^^|+|                                                                                       |+|^^\n";
    cout << "\t\t\t\t\t^^|+|                                                                                       |+|^^\n";
    cout << "\t\t\t\t\t^^|+|                                                                                       |+|^^\n";
    cout << "\t\t\t\t\t^^|+|                                                                                       |+|^^\n";
    cout << "\t\t\t\t\t^^|+|                                                                                       |+|^^\n";
    cout << "\t\t\t\t\t^^|+|                                                                                       |+|^^\n";
    cout << "\t\t\t\t\t^^|+|                                                     Developed By:                     |+|^^\n";
    cout << "\t\t\t\t\t^^|+|                                                                 Mubashar Ghazi        |+|^^\n";
    cout << "\t\t\t\t\t^^|+|                                                                                       |+|^^\n";
    cout << "\t\t\t\t\t^^|+|                                                                                       |+|^^\n";
    cout << "\t\t\t\t\t^^|+|~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~|+|^^\n";
    cout << "\t\t\t\t\t*************************************************************************************************\n\n\n\n\t\t\t\t\t";
    system("pause");
}

void loading() {
    // Adding Some Visuals for the GUI
    // Sleep function is used to Pause of Screen for some Intervals
    system("cls");
    system("pause");
    system("color A");
    cout << "\n\n\n\n\n\n\n\n\n\n\n\n\t\t\t\t\t\t ****************************~~Loading~~**************************\n" << endl;
    cout << "\t\t\t\t\t\t Loading |||||||                                                 | 17% ....";
    Sleep(500);
    system("cls");
    system("color C");
    cout << "\n\n\n\n\n\n\n\n\n\n\n\n\t\t\t\t\t\t ****************************~~Loading~~**************************\n" << endl;
    cout << "\t\t\t\t\t\t Loading |||||||||||||||||||                                     | 47% ....";
    Sleep(630);
    system("color B");
    system("cls");
    cout << "\n\n\n\n\n\n\n\n\n\n\n\n\t\t\t\t\t\t ****************************~~Loading~~**************************\n" << endl;
    cout << "\t\t\t\t\t\t Loading |||||||||||||||||||||||||||||||||                       | 61% ....";
    Sleep(570);
    system("cls");
    system("color C");
    cout << "\n\n\n\n\n\n\n\n\n\n\n\n\t\t\t\t\t\t ****************************~~Loading~~**************************\n" << endl;
    cout << "\t\t\t\t\t\t Loading ||||||||||||||||||||||||||||||||||||||||||||||||        | 95% ....";
    Sleep(470);
    system("cls");
    system("color D");
    cout << "\n\n\n\n\n\n\n\n\n\n\n\n\t\t\t\t\t\t ****************************~~Loading~~**************************\n" << endl;
    cout << "\t\t\t\t\t\t Loading ||||||||||||||||||||||||||||||||||||||||||||||||||||||||| 100% ....";
    Sleep(580);
    cout << endl << endl;
}

void validateInput(const string& input) {
    if (input.empty()) {
        throw invalid_argument("Input cannot be empty.");
    }
}

void validateNumericInput(const string& input) {
    for (char c : input) {
        if (!isdigit(c)) {
            throw invalid_argument("Input must be a numeric value.");
        }
    }
}

void validateNonEmptyInput(const string& input) {
    if (input.empty()) {
        throw invalid_argument("Input cannot be empty.");
    }
}

void validatePositiveInput(int input) {
    if (input <= 0) {
        throw invalid_argument("Input must be a positive value.");
    }
}

void userPanel(const string& username) {
    string option;
    User user(username, "", ""); // Creating a User object with the given username
    TransportSystem ts;
    while (true) {
        cout << "\n\n\n\n\n\n\t\t\t\t~~~~~Welcome to the User Panel~~~~~~    " << endl;
        cout << "\t\t\t\t******************************************************************** \n";
        cout << "\t\t\t\t <1>~ Type 'edit'   to edit your account      " << endl;
        cout << "\t\t\t\t <2>~ Type 'forgot' to reset your password    " << endl;
        cout << "\t\t\t\t <3>~ Type 'routes' to show routes            " << endl;
        cout << "\t\t\t\t <4>~ Type 'fare'   to show fare              " << endl;
        cout << "\t\t\t\t <5>~ Type 'reserve' to reserve a seat        " << endl;
        cout << "\t\t\t\t <6>~ Type 'view'   to view reservations      " << endl;
        cout << "\t\t\t\t <7>~ Type 'cancel' to cancel a reservation   " << endl;
        cout << "\t\t\t\t <8>~ Type 'shortest' to find the shortest path" << endl;
        cout << "\t\t\t\t <9>~ Type 'search' to search routes, stations or fares" << endl;
        cout << "\t\t\t\t <10>~ Type 'exit'  to exit the program       " << endl;
        cin >> option;

        try {
            validateInput(option);
        } catch (invalid_argument &e) {
            cout << e.what() << endl;
            continue;
        }

        if (option == "edit" || option == "1") {
            user.editUserData();
        } else if (option == "forgot" || option == "2") {
            User::forgotPassword();
        } else if (option == "routes" || option == "3") {
            ts.showRoutes();
        } else if (option == "fare" || option == "4") {
            ts.showFare();
        } else if (option == "reserve" || option == "5") {
            ts.reserveSeat();
        } else if (option == "view" || option == "6") {
            ts.viewReservations();
        } else if (option == "cancel" || option == "7") {
            ts.cancelReservation();
        } else if (option == "shortest" || option == "8") {
            ts.findShortestPath();
        } else if (option == "search" || option == "9") {
            string query;
            cout << "Enter search query: ";
            cin.ignore();
            getline(cin, query);
            ts.searchRoutes(query);
            ts.searchStations(query);
            cout << "To search for fares, enter the start and end stations." << endl;
            string start, end;
            cout << "Start station: ";
            cin >> start;
            cout << "End station: ";
            cin >> end;
            ts.searchFares(start, end);
        } else if (option == "exit" || option == "10") {
            cout << "Thank You for using our system! " << endl;
            return; // Exit the user panel loop to return to the main menu
        } else {
            cout << "Invalid Option! " << endl;
        }
    }
}

void adminPanel() {
    string option;
    while (true) {
        cout << "\n\n\n\n\n\n\t\t\t\t~~~~~Welcome to the Admin Panel~~~~~~    " << endl;
        cout << "\t\t\t\t******************************************************************** \n";
        cout << "\t\t\t\t <1>~ Type 'routes'    to manage routes     " << endl;
        cout << "\t\t\t\t <2>~ Type 'stations'  to manage stations   " << endl;
        cout << "\t\t\t\t <3>~ Type 'buses'     to manage buses      " << endl;
        cout << "\t\t\t\t <4>~ Type 'fare'      to manage fare       " << endl;
        cout << "\t\t\t\t <5>~ Type 'exit'      to exit the program  " << endl;
        cin >> option;

        try {
            validateInput(option);
        } catch (invalid_argument &e) {
            cout << e.what() << endl;
            continue;
        }

        if (option == "routes" || option == "1") {
            Admin::manageRoutes();
        } else if (option == "stations" || option == "2") {
            Admin::manageStations();
        } else if (option == "buses" || option == "3") {
            Admin::manageBuses();
        } else if (option == "fare" || option == "4") {
            Admin::manageFare();
        } else if (option == "exit" || option == "5") {
            cout << "Thank You for using our system! " << endl;
            return; // Exit the admin panel loop to return to the main menu
        } else {
            cout << "Invalid Option! " << endl;
        }
    }
}

void exitProgram() {
    cout << endl << endl;
    system("cls");

    // First Animation
    Sleep(60);
    cout << "\n\t\t\t\t\t--------------------------------------------\n";
    cout << "\t\t\t\t\t|              !!!!!!!!!!!                 |\n";
    cout << "\t\t\t\t\t|             (  o      o )                |\n";
    cout << "\t\t\t\t\t|             (     ||    )                |\n";
    cout << "\t\t\t\t\t|              ( ________ )                |\n";
    cout << "\t\t\t\t\t|               ##########                 |\n";
    cout << "\t\t\t\t\t|                                          |\n";
    cout << "\t\t\t\t\t|   Thank you for selecting our service    |\n";
    cout << "\t\t\t\t\t|                                          |\n";
    cout << "\t\t\t\t\t|                                          |\n";
    cout << "\t\t\t\t\t|                                          |\n";
    cout << "\t\t\t\t\t|                                          |\n";
    cout << "\t\t\t\t\t--------------------------------------------";

    Sleep(1000);
    system("cls");

    // Second Animation
    Sleep(999);
    system("color B");
    cout << "\n\t\t\t\t\t--------------------------------------------\n";
    cout << "\t\t\t\t\t|              !!!!!!!!!!!                 |\n";
    cout << "\t\t\t\t\t|             (         o )                |\n";
    cout << "\\t\t\t\t\t|             (     ||    )                |\n";
    cout << "\t\t\t\t\t|              ( ________ )                |\n";
    cout << "\t\t\t\t\t|               ##########                 |\n";
    cout << "\t\t\t\t\t|                                          |\n";
    cout << "\t\t\t\t\t|            Love You Good Luck            |\n";
    cout << "\t\t\t\t\t|                                          |\n";
    cout << "\t\t\t\t\t|                                          |\n";
    cout << "\t\t\t\t\t|                                          |\n";
    cout << "\t\t\t\t\t|                                          |\n";
    cout << "\t\t\t\t\t--------------------------------------------";

    Sleep(1000);
    system("cls");

    // Third Animation
    system("color D");
    Sleep(1000);
    cout << "\n\t\t\t\t\t--------------------------------------------\n";
    cout << "\t\t\t\t\t|              !!!!!!!!!!!                 |\n";
    cout << "\t\t\t\t\t|             (  o      o )                |\n";
    cout << "\t\t\t\t\t|             (     ||    )                |\n";
    cout << "\t\t\t\t\t|              ( ________ )                |\n";
    cout << "\t\t\t\t\t|                                          |\n";
    cout << "\t\t\t\t\t|               ##########                 |\n";
    cout << "\t\t\t\t\t|                                          |\n";
    cout << "\t\t\t\t\t|   Thank you for selecting our service    |\n";
    cout << "\t\t\t\t\t|             _____________                |\n";
    cout << "\t\t\t\t\t|            |   o    o    |               |\n";
    cout << "\t\t\t\t\t|            |     i       |               |\n";
    cout << "\t\t\t\t\t|            |   |----|    |               |\n";
    cout << "\t\t\t\t\t--------------------------------------------\n";
    cout << "\t\t\t\t\t";
    system("pause");
}

int main() {
    TransportSystem ts;
    ts.loadRoutes();
    ts.loadFares();
    ts.loadReservations();
    welcome();
    loading();

    while (true) {
        int choice;
        cout << "1. User Signup\n2. User Login\n3. Admin Login\n4. Exit\nChoose an option: ";
        cin >> choice;

        try {
            validateNumericInput(to_string(choice));
        } catch (invalid_argument &e) {
            cout << e.what() << endl;
            ts.logError(e.what());
            continue;
        }

        switch (choice) {
            case 1:
                User::signup();
                break;
            case 2:
                {
                    string username, password;
                    cout << "Enter Username: ";
                    cin >> username;
                    validateNonEmptyInput(username);
                    cout << "Enter Password: ";
                    cin >> password;
                    validateNonEmptyInput(password);
                    if (User::login(username, password)) {
                        cout << "Login successful!" << endl;
                        userPanel(username);
                    } else {
                        cout << "Invalid username or password." << endl;
                        ts.logError("Invalid username or password.");
                    }
                }
                break;
            case 3:
                {
                    string username, password;
                    cout << "Enter Admin Username: ";
                    cin >> username;
                    validateNonEmptyInput(username);
                    cout << "Enter Admin Password: ";
                    cin >> password;
                    validateNonEmptyInput(password);
                    if (Admin::login(username, password)) {
                        cout << "Admin login successful!" << endl;
                        adminPanel();
                    } else {
                        cout << "Invalid admin credentials." << endl;
                        ts.logError("Invalid admin credentials.");
                    }
                }
                break;
            case 4:
                exitProgram();
                return 0; // Exit the program
            default:
                cout << "Invalid choice!" << endl;
                ts.logError("Invalid choice.");
        }
    }
    return 0;
}
