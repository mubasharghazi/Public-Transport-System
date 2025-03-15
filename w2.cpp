#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <unordered_map>
#include <queue>
#include <climits>
#include <sstream>

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
    vector<string> tripHistory;
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
unordered_map<string, vector<string>> userReservations; // Store user reservations

// Function Declarations
void welcome();
void loading();
void process();
void userPanel(User& user);
void adminPanel();
void userLogin();
void userRegistration();
void adminLogin();
void manageRoutes();
void manageStations();
void manageBuses();
void showFare();
void reserveSeat(User& user);
void showRoutes();
void shortestPath();
void cancelReservation(User& user);
void tripHistory(User& user);
void exitSystem();

// Helper Functions
bool validateUser(const string& username, const string& password);
bool validateAdmin(const string& username, const string& password);
void clearScreen();
void addRoute();
void addStation();
void addBus();
void addFare();
int dijkstra(const string& start, const string& end);

// Data Persistence
void loadData();
void saveData();

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
    for (int i = 0; i < 3; i++) {
        cout << ".";
        cout.flush();
        this_thread::sleep_for(chrono::milliseconds(500));
    }
    cout << endl;
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

// Exit the system
void exitSystem() {
    cout << "Exiting the system. Goodbye!" << endl;
}

// Validate user credentials
bool validateUser(const string& username, const string& password) {
    for (const auto& user : users) {
        if (user.username == username && user.password == password) {
            return true;
        }
    }
    return false;
}

// Validate admin credentials
bool validateAdmin(const string& username, const string& password) {
    return username == admin.username && password == admin.password;
}

// Clear console screen
void clearScreen() {
#ifdef _WIN32
    system("cls");
#else
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
            int tripCount;
            file >> tripCount;
            users[i].tripHistory.resize(tripCount);
            file.ignore();
            for (int j = 0; j < tripCount; ++j) {
                getline(file, users[i].tripHistory[j]);
            }
        }

        // Load stations
        int stationCount;
        file >> stationCount;
        stations.resize(stationCount);
        for (int i = 0; i < stationCount; ++i) {
            file >> stations[i].name;
            int routeCount;
            file >> routeCount;
            stations[i].routes.resize(routeCount);
            file.ignore();
            for (int j = 0; j < routeCount; ++j) {
                getline(file, stations[i].routes[j]);
            }
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

        // Load user reservations
        int reservationCount;
        file >> reservationCount;
        for (int i = 0; i < reservationCount; ++i) {
            string username, reservation;
            file >> username;
            int resCount;
            file >> resCount;
            file.ignore();
            for (int j = 0; j < resCount; ++j) {
                getline(file, reservation);
                userReservations[username].push_back(reservation);
            }
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
            file << user.tripHistory.size() << endl;
            for (const auto& trip : user.tripHistory) {
                file << trip << endl;
            }
        }

        // Save stations
        file << stations.size() << endl;
        for (const auto& station : stations) {
            file << station.name << endl;
            file << station.routes.size() << endl;
            for (const auto& route : station.routes) {
                file << route << endl;
            }
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

        // Save user reservations
        file << userReservations.size() << endl;
        for (const auto& reservation : userReservations) {
            file << reservation.first << " " << reservation.second.size() << endl;
            for (const auto& res : reservation.second) {
                file << res << endl;
            }
        }

        file.close();
    }
}


// Shortest Path Function using Dijkstra's Algorithm
int dijkstra(const string& start, const string& end) {
    unordered_map<string, int> distances;
    for (const auto& station : graph) {
        distances[station.first] = INT_MAX;
    }
    distances[start] = 0;

    priority_queue<pair<int, string>, vector<pair<int, string>>, greater<pair<int, string>>> pq;
    pq.push({0, start});

    while (!pq.empty()) {
        int currentDistance = pq.top().first;
        string currentNode = pq.top().second;
        pq.pop();

        if (currentNode == end) {
            return currentDistance;
        }

        for (const auto& neighbor : graph[currentNode]) {
            int newDistance = currentDistance + neighbor.second;
            if (newDistance < distances[neighbor.first]) {
                distances[neighbor.first] = newDistance;
                pq.push({newDistance, neighbor.first});
            }
        }
    }
    return -1; // If no path exists
}
