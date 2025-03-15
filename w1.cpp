#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>
#include <queue>
#include <fstream>
#include <climits> // For INT_MAX

using namespace std;

// Global Constants
const int MAX_USERS = 100;
const int MAX_BUSES = 50;
const int MAX_STATIONS = 20;

// Struct definitions
struct User {
    string username;
    string password;
    string email;
};

struct Admin {
    string username;
    string password;
};

struct Station {
    string name;
    vector<string> routes; // List of routes passing through this station
};

struct Bus {
    string number;
    string route;
    int totalSeats;
    unordered_map<int, bool> seatAvailability; // Seat availability map
};

struct Fare {
    string route;
    double price;
};

// Global Variables
vector<User> users;
Admin admin = {"admin", "123"};
vector<Station> stations;
vector<Bus> buses;
vector<Fare> fares;
unordered_map<string, vector<pair<string, int>>> graph; // Graph for shortest path

// Function Declarations
void welcome();
void loading();
void process();
void userPanel();
void adminPanel();
void userLogin();
void userRegistration();
void adminLogin();
void manageRoutes();
void manageStations();
void manageBuses();
void showFare();
void reserveSeat();
void showRoutes();
void shortestPath();
void exitSystem();
void loadData();
void saveData();

// Helper Functions
bool validateUser(const string& username, const string& password);
bool validateAdmin(const string& username, const string& password);
void clearScreen();
void addRoute();
void addStation();
void addBus();
void addFare();
int dijkstra(const string& start, const string& end);

// Main function
int main() {
    loadData();
    welcome();
    loading();
    process();
    saveData();
    return 0;
}

void welcome() {
    clearScreen();
    cout << "Welcome to the Public Transport System!" << endl;
    cout << "Developed by Mubashar Ghazi" << endl;
}

void loading() {
    cout << "Loading..." << endl;
    // Simulate loading
}

void process() {
    int choice;
    while (true) {
        clearScreen();
        cout << "1. User Login" << endl;
        cout << "2. User Registration" << endl;
        cout << "3. Admin Login" << endl;
        cout << "4. Exit" << endl;
        cin >> choice;
        switch (choice) {
            case 1:
                userLogin();
                break;
            case 2:
                userRegistration();
                break;
            case 3:
                adminLogin();
                break;
            case 4:
                exitSystem();
                return;
            default:
                cout << "Invalid choice. Please try again." << endl;
                break;
        }
    }
}

void userPanel() {
    int choice;
    while (true) {
        clearScreen();
        cout << "User Panel" << endl;
        cout << "1. View Routes" << endl;
        cout << "2. View Fare" << endl;
        cout << "3. Reserve Seat" << endl;
        cout << "4. Find Shortest Path" << endl;
        cout << "5. Logout" << endl;
        cin >> choice;
        clearScreen();
        switch (choice) {
            case 1:
                showRoutes();
                break;
            case 2:
                showFare();
                break;
            case 3:
                reserveSeat();
                break;
            case 4:
                shortestPath();
                break;
            case 5:
                return;
            default:
                cout << "Invalid choice. Please try again." << endl;
                break;
        }
    }
}

void adminPanel() {
    int choice;
    while (true) {
        clearScreen();
        cout << "Admin Panel" << endl;
        cout << "1. Manage Routes" << endl;
        cout << "2. Manage Stations" << endl;
        cout << "3. Manage Buses" << endl;
        cout << "4. Manage Fares" << endl;
        cout << "5. Logout" << endl;
        cin >> choice;
        clearScreen();
        switch (choice) {
            case 1:
                manageRoutes();
                break;
            case 2:
                manageStations();
                break;
            case 3:
                manageBuses();
                break;
            case 4:
                addFare();
                break;
            case 5:
                return;
            default:
                cout << "Invalid choice. Please try again." << endl;
                break;
        }
    }
}

void userLogin() {
    string username, password;
    clearScreen();
    cout << "User Login" << endl;
    cout << "Username: ";
    cin >> username;
    cout << "Password: ";
    cin >> password;
    if (validateUser(username, password)) {
        cout << "Login successful!" << endl;
        userPanel();
    } else {
        cout << "Invalid username or password." << endl;
    }
    system("pause");
}

void userRegistration() {
    if (users.size() >= MAX_USERS) {
        cout << "User limit reached. Cannot register more users." << endl;
        return;
    }
    User newUser;
    clearScreen();
    cout << "User Registration" << endl;
    cout << "Username: ";
    cin >> newUser.username;
    cout << "Password: ";
    cin >> newUser.password;
    cout << "Email: ";
    cin >> newUser.email;
    users.push_back(newUser);
    cout << "Registration successful!" << endl;
    system("pause");
}

void adminLogin() {
    string username, password;
    clearScreen();
    cout << "Admin Login" << endl;
    cout << "Username: ";
    cin >> username;
    cout << "Password: ";
    cin >> password;
    if (validateAdmin(username, password)) {
        cout << "Login successful!" << endl;
        adminPanel();
    } else {
        cout << "Invalid username or password." << endl;
    }
    system("pause");
}

void manageRoutes() {
    int choice;
    while (true) {
        clearScreen();
        cout << "Manage Routes" << endl;
        cout << "1. Add Route" << endl;
        cout << "2. Back" << endl;
        cin >> choice;
        clearScreen();
        switch (choice) {
            case 1:
                addRoute();
                break;
            case 2:
                return;
            default:
                cout << "Invalid choice. Please try again." << endl;
                break;
        }
    }
}

void manageStations() {
    int choice;
    while (true) {
        clearScreen();
        cout << "Manage Stations" << endl;
        cout << "1. Add Station" << endl;
        cout << "2. Back" << endl;
        cin >> choice;
        clearScreen();
        switch (choice) {
            case 1:
                addStation();
                break;
            case 2:
                return;
            default:
                cout << "Invalid choice. Please try again." << endl;
                break;
        }
    }
}

void manageBuses() {
    int choice;
    while (true) {
        clearScreen();
        cout << "Manage Buses" << endl;
        cout << "1. Add Bus" << endl;
        cout << "2. Back" << endl;
        cin >> choice;
        clearScreen();
        switch (choice) {
            case 1:
                addBus();
                break;
            case 2:
                return;
            default:
                cout << "Invalid choice. Please try again." << endl;
                break;
        }
    }
}

void addRoute() {
    string route, start, end;
    int distance;
    clearScreen();
    cout << "Add Route" << endl;
    cout << "Route Name: ";
    cin >> route;
    cout << "Starting Station: ";
    cin >> start;
    cout << "Ending Station: ";
    cin >> end;
    cout << "Distance (in km): ";
    cin >> distance;
    graph[start].push_back(make_pair(end, distance));
    graph[end].push_back(make_pair(start, distance));
    cout << "Route added successfully!" << endl;
    system("pause");
}

void addStation() {
    Station newStation;
    clearScreen();
    cout << "Add Station" << endl;
    cout << "Station Name: ";
    cin >> newStation.name;
    stations.push_back(newStation);
    cout << "Station added successfully!" << endl;
    system("pause");
}

void addBus() {
    Bus newBus;
    clearScreen();
    cout << "Add Bus" << endl;
    cout << "Bus Number: ";
    cin >> newBus.number;
    cout << "Route: ";
    cin >> newBus.route;
    cout << "Total Seats: ";
    cin >> newBus.totalSeats;
    for (int i = 1; i <= newBus.totalSeats; i++) {
        newBus.seatAvailability[i] = false;
    }
    buses.push_back(newBus);
    cout << "Bus added successfully!" << endl;
    system("pause");
}

void addFare() {
    Fare newFare;
    clearScreen();
    cout << "Add Fare" << endl;
    cout << "Route: ";
    cin >> newFare.route;
    cout << "Fare (in USD): ";
    cin >> newFare.price;
    fares.push_back(newFare);
    cout << "Fare added successfully!" << endl;
    system("pause");
}

void showFare() {
    clearScreen();
    cout << "Fare Information" << endl;
    for (const auto& fare : fares) {
        cout << "Route: " << fare.route << ", Price: $" << fare.price << endl;
    }
    system("pause");
}

void reserveSeat() {
    string busNumber;
    int seatNumber;
    clearScreen();
    cout << "Reserve Seat" << endl;
    cout << "Bus Number: ";
    cin >> busNumber;
    cout << "Seat Number: ";
    cin >> seatNumber;
    for (auto& bus : buses) {
        if (bus.number == busNumber) {
            if (bus.seatAvailability[seatNumber] == false) {
                bus.seatAvailability[seatNumber] = true;
                cout << "Seat reserved successfully!" << endl;
            } else {
                cout << "Seat already reserved." << endl;
            }
            system("pause");
            return;
        }
    }
    cout << "Bus not found." << endl;
    system("pause");
}

void showRoutes() {
    clearScreen();
    cout << "Available Routes" << endl;
    for (const auto& station : stations) {
        cout << "Station: " << station.name << endl;
        for (const auto& route : station.routes) {
            cout << "  Route: " << route << endl;
        }
    }
    system("pause");
}

void shortestPath() {
    string start, end;
    clearScreen();
    cout << "Find Shortest Path" << endl;
    cout << "Starting Station: ";
    cin >> start;
    cout << "Ending Station: ";
    cin >> end;
    int distance = dijkstra(start, end);
    if (distance != -1) {
        cout << "Shortest distance from " << start << " to " << end << " is " << distance << " km." << endl;
    } else {
        cout << "Path not found." << endl;
    }
    system("pause");
}

int dijkstra(const string& start, const string& end) {
    unordered_map<string, int> distances;
    for (const auto& station : graph) {
        distances[station.first] = INT_MAX;
    }
    distances[start] = 0;
    priority_queue<pair<int, string>, vector<pair<int, string>>, greater<pair<int, string>>> pq;
    pq.push(make_pair(0, start));
    while (!pq.empty()) {
        int distance = pq.top().first;
        string current = pq.top().second;
        pq.pop();
        if (current == end) {
            return distance;
        }
        for (const auto& neighbor : graph[current]) {
            int newDistance = distance + neighbor.second;
            if (newDistance < distances[neighbor.first]) {
                distances[neighbor.first] = newDistance;
                pq.push(make_pair(newDistance, neighbor.first));
            }
        }
    }
    return -1;
}

void exitSystem() {
    cout << "Exiting the system. Goodbye!" << endl;
    exit(0);
}

bool validateUser(const string& username, const string& password) {
    for (const auto& user : users) {
        if (user.username == username && user.password == password) {
            return true;
        }
    }
    return false;
}

bool validateAdmin(const string& username, const string& password) {
    return (admin.username == username && admin.password == password);
}

void clearScreen() {
    // Clear console screen (platform-specific)
#if defined(_WIN32)
    system("cls");
#elif defined(__linux__) || defined(__APPLE__)
    system("clear");
#endif
}

void loadData() {
    ifstream file("data.txt");
    if (file.is_open()) {
        // Load users
        int userCount;
        file >> userCount;
        users.resize(userCount);
        for (int i = 0; i < userCount; ++i) {
            file >> users[i].username >> users[i].password >> users[i].email;
        }

        // Load stations
        int stationCount;
        file >> stationCount;
        stations.resize(stationCount);
        for (int i = 0; i < stationCount; ++i) {
            file >> stations[i].name;
        }

        // Load buses
        int busCount;
        file >> busCount;
        buses.resize(busCount);
        for (int i = 0; i < busCount; ++i) {
            file >> buses[i].number >> buses[i].route >> buses[i].totalSeats;
            for (int j = 1; j <= buses[i].totalSeats; ++j) {
                bool seatStatus;
                file >> seatStatus;
                buses[i].seatAvailability[j] = seatStatus;
            }
        }

        // Load fares
        int fareCount;
        file >> fareCount;
        fares.resize(fareCount);
        for (int i = 0; i < fareCount; ++i) {
            file >> fares[i].route >> fares[i].price;
        }

        file.close();
    }
}

void saveData() {
    ofstream file("data.txt");
    if (file.is_open()) {
        // Save users
        file << users.size() << endl;
        for (const auto& user : users) {
            file << user.username << " " << user.password << " " << user.email << endl;
        }

        // Save stations
        file << stations.size() << endl;
        for (const auto& station : stations) {
            file << station.name << endl;
        }

        // Save buses
        file << buses.size() << endl;
        for (const auto& bus : buses) {
            file << bus.number << " " << bus.route << " " << bus.totalSeats << endl;
            for (int j = 1; j <= bus.totalSeats; ++j) {
                file << bus.seatAvailability.at(j) << " ";
            }
            file << endl;
        }

        // Save fares
        file << fares.size() << endl;
        for (const auto& fare : fares) {
            file << fare.route << " " << fare.price << endl;
        }

        file.close();
    }
}