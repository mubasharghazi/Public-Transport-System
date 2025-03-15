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
using namespace std;

// Function Declarations
void welcome();
void loading();
void process();
void userPanel(const string& username);
void adminPanel();
void edit_userdata(const string& currentUsername);
void forgot_password();
void userSignup();
bool validateUser(const string& username, const string& password);
void userLogin();
void adminLogin();
void userRegistration();
bool isUsernameTaken(const string& username);
void manageRoutes();
void manageStations();
void manageBuses();
void manageFare();
void showFare();
void reserveSeat();
void showRoutes();
void shortestPath();
void exitProgram();
void validateInput(string &input);
void validateNumericInput(string &input);
void saveRoutesToFile();
void saveFaresToFile();

// Data Structures
map<string, vector<pair<string, int>>> routes; // Adjacency list for routes (station, (destination, distance))
map<string, int> fareChart; // Fare from one station to another

// Helper Functions
void loadRoutes();
void loadFares();

int main() {
    loadRoutes();
    loadFares();
    welcome();
    loading();
    int choice;
    cout << "1. User Signup\n2. User Login\n3. Admin Login\nChoose an option: ";
    cin >> choice;

    switch (choice) {
        case 1:
            userSignup();
            break;
        case 2:
            userLogin();
            break;
        case 3:
            adminLogin();
            break;
        default:
            cout << "Invalid choice!" << endl;
    }
    return 0;
}

// Function Definitions
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

void process() {
    // Adding Some Visuals for the GUI
    system("pause");
    system("cls");
    system("color A");
    cout << "\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\t\t\t\t\t\t\t    Please Wait for a moment...\n" << endl;
    cout << "\t\t\t\t\t\t Processing <<<|||||||                                                 |>>> 17% ....";
    Sleep(500);
    system("cls");
    system("color C");
    cout << "\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\t\t\t\t\t\t\t    Please Wait for a moment...\n" << endl;
    cout << "\t\t\t\t\t\t Processing <<<|||||||||||||||||||                                     |>>> 47% ....";
    Sleep(630);
    system("color B");
    system("cls");
    cout << "\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\t\t\t\t\t\t\t    Please Wait for a moment...\n" << endl;
    cout << "\t\t\t\t\t\t Processing <<<|||||||||||||||||||||||||||||||||                       |>>> 61% ....";
    Sleep(570);
    system("cls");
    system("color C");
    cout << "\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\t\t\t\t\t\t\t    Please Wait for a moment...\n" << endl;
    cout << "\t\t\t\t\t\t Processing <<<||||||||||||||||||||||||||||||||||||||||||||||||        |>>> 95% ....";
    Sleep(470);
    system("cls");
    system("color D");
    cout << "\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\t\t\t\t\t\t\t    Please Wait for a moment...\n" << endl;
    cout << "\t\t\t\t\t\t Proceesing <<<|||||||||||||||||||||||||||||||||||||||||||||||||||||||||>>> 100% ....\n";
    Sleep(580);
    cout << endl << "\t\t\t\t\t\t\t";
    system("cls");
    cout << endl;
}

bool isUsernameTaken(const string& username) {
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

void userSignup() {
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

bool validateUser(const string& username, const string& password) {
    ifstream file("userData.txt");
    if (file.is_open()) {
        string u, p, e;
        while (file >> u >> p >> e) {
            if (u == username && p == password) {
                file.close();
                return true;
            }
        }
        file.close();
    }
    return false;
}

void userLogin() {
    string username, password;
    cout << "Enter Username: ";
    cin >> username;
    cout << "Enter Password: ";
    cin >> password;

    if (validateUser(username, password)) {
        cout << "Login successful!" << endl;
        userPanel(username);
    } else {
        cout << "Invalid username or password." << endl;
    }
}

void adminLogin() {
    string username, password;
    cout << "Enter Admin Username: ";
    cin >> username;
    cout << "Enter Admin Password: ";
    cin >> password;

    // Here you can hardcode the admin credentials or read from a secure file
    if (username == "admin" && password == "admin123") {
        cout << "Admin login successful!" << endl;
        adminPanel();
    } else {
        cout << "Invalid admin credentials." << endl;
    }
}

void edit_userdata(const string& currentUsername) {
    ifstream file("userData.txt");
    ofstream tempFile("temp.txt");
    string line, username, password, email;
    bool userFound = false;

    while (getline(file, line)) {
        stringstream ss(line);
        ss >> username >> password >> email;
        if (username == currentUsername) {
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

void forgot_password() {
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

void userPanel(const string& username) {
    string option;
    while (true) {
        cout << "\n\n\n\n\n\n\t\t\t\t~~~~~Welcome to the User Panel~~~~~~    " << endl;
        cout << "\t\t\t\t******************************************************************** \n";
        cout << "\t\t\t\t <1>~ Type 'edit'   to edit your account      " << endl;
        cout << "\t\t\t\t <2>~ Type 'forgot' to reset your password    " << endl;
        cout << "\t\t\t\t <3>~ Type 'routes' to show routes            " << endl;
        cout << "\t\t\t\t <4>~ Type 'fare'   to show fare              " << endl;
        cout << "\t\t\t\t <5>~ Type 'reserve' to reserve a seat        " << endl;
        cout << "\t\t\t\t <6>~ Type 'shortest' to find the shortest path" << endl;
        cout << "\t\t\t\t <7>~ Type 'exit'   to exit the program       " << endl;
        cin >> option;

        try {
            validateInput(option);
        } catch (invalid_argument &e) {
            cout << e.what() << endl;
            continue;
        }

        if (option == "edit" || option == "1") {
            edit_userdata(username);
        } else if (option == "forgot" || option == "2") {
            forgot_password();
        } else if (option == "routes" || option == "3") {
            showRoutes();
        } else if (option == "fare" || option == "4") {
            showFare();
        } else if (option == "reserve" || option == "5") {
            reserveSeat();
        } else if (option == "shortest" || option == "6") {
            shortestPath();
        } else if (option == "exit" || option == "7") {
            cout << "Thank You for using our system! " << endl;
            exitProgram();
            break;
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
            manageRoutes();
        } else if (option == "stations" || option == "2") {
            manageStations();
        } else if (option == "buses" || option == "3") {
            manageBuses();
        } else if (option == "fare" || option == "4") {
            manageFare();
        } else if (option == "exit" || option == "5") {
            cout << "Thank You for using our system! " << endl;
            exitProgram();
            break;
        } else {
            cout << "Invalid Option! " << endl;
        }
    }
}

void manageRoutes() {
    string station, destination;
    int distance;
    cout << "Enter the route's station: ";
    cin >> station;
    cout << "Enter the route's destination: ";
    cin >> destination;
    cout << "Enter the distance between them: ";
    cin >> distance;

    // Update routes map
    routes[station].push_back(make_pair(destination, distance));
    routes[destination].push_back(make_pair(station, distance)); // Assuming the route is bidirectional

    // Save routes to file
    ofstream file("routes.txt", ios::app);
    file << station << " " << destination << " " << distance << endl;
    file.close();

    cout << "Route added successfully!" << endl;
}

void manageStations() {
    string station;
    cout << "Enter the station to add: ";
    cin >> station;
    if (routes.find(station) == routes.end()) {
        routes[station] = vector<pair<string, int>>();
        cout << "Station added successfully!" << endl;
    } else {
        cout << "Station already exists!" << endl;
    }
}

void manageBuses() {
    string busNumber;
    cout << "Enter the bus number to add: ";
    cin >> busNumber;
    // Implement the logic to manage buses, e.g., adding, removing, or updating bus information.
    cout << "Bus added successfully!" << endl;
}

void manageFare() {
    string start, end;
    int fare;
    cout << "Enter the starting station: ";
    cin >> start;
    cout << "Enter the destination station: ";
    cin >> end;
    cout << "Enter the fare between them: ";
    cin >> fare;

    fareChart[start + end] = fare;

    // Save fare to file
    ofstream file("fare.txt", ios::app);
    file << start << " " << end << " " << fare << endl;
    file.close();

    cout << "Fare added successfully!" << endl;
}

void showFare() {
    string start, end;
    cout << "Enter the starting station: ";
    cin >> start;
    cout << "Enter the destination station: ";
    cin >> end;

    if (fareChart.find(start + end) != fareChart.end()) {
        cout << "The fare from " << start << " to " << end << " is: " << fareChart[start + end] << " PKR" << endl;
    } else {
        cout << "Fare information for the specified route is not available." << endl;
    }
}

void reserveSeat() {
    string busNumber, seatNumber;
    cout << "Enter the bus number: ";
    cin >> busNumber;
    cout << "Enter the seat number to reserve: ";
    cin >> seatNumber;
    // Implement the logic to reserve a seat in the specified bus.
    cout << "Seat reserved successfully!" << endl;
}

void showRoutes() {
    for (const auto& route : routes) {
        cout << "Station: " << route.first << endl;
        for (const auto& dest : route.second) {
            cout << "  -> " << dest.first << " (Distance: " << dest.second << " km)" << endl;
        }
    }
}

void shortestPath() {
    string start, end;
    cout << "Enter the starting station: ";
    cin >> start;
    cout << "Enter the destination station: ";
    cin >> end;

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
    cout << "\t\t\t\t\t|             (     ||    )                |\n";
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

void validateInput(string &input) {
    // Input validation logic here
    // For simplicity, let's assume we just want to ensure the input is not empty
    if (input.empty()) {
        throw invalid_argument("Input cannot be empty.");
    }
}

void validateNumericInput(string &input) {
    // Ensure the input is a valid number
    for (char c : input) {
        if (!isdigit(c)) {
            throw invalid_argument("Input must be a numeric value.");
        }
    }
}

void loadRoutes() {
    ifstream file("routes.txt");
    string station, destination;
    int distance;
    while (file >> station >> destination >> distance) {
        routes[station].push_back(make_pair(destination, distance));
        routes[destination].push_back(make_pair(station, distance));
    }
    file.close();
}

void loadFares() {
    ifstream file("fare.txt");
    string start, end;
    int fare;
    while (file >> start >> end >> fare) {
        fareChart[start + end] = fare;
    }
    file.close();
}

void saveRoutesToFile() {
    ofstream file("routes.txt");
    for (const auto& route : routes) {
        for (const auto& dest : route.second) {
            file << route.first << " " << dest.first << " " << dest.second << endl;
        }
    }
    file.close();
}

void saveFaresToFile() {
    ofstream file("fare.txt");
    for (const auto& fare : fareChart) {
        file << fare.first.substr(0, fare.first.size() / 2) << " "
             << fare.first.substr(fare.first.size() / 2) << " "
             << fare.second << endl;
    }
    file.close();
}