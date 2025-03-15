#include <iostream>
#include <cstdlib>
#include <ctime>
#include <conio.h>
#include <windows.h>
#include <list>
#include <algorithm>
#include <fstream>
#include <map>
#include <vector>

#define SCREEN_WIDTH 40
#define SCREEN_HEIGHT 20
#define WIN_WIDTH 40

using namespace std;

// Handle Console Output
HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);
COORD CursorPosition;

// Move Cursor to Specific Position
void gotoxy(int x, int y) {
    CursorPosition.X = x;
    CursorPosition.Y = y;
    SetConsoleCursorPosition(console, CursorPosition);
}

// Control Cursor Visibility
void setCursor(bool visible, DWORD size) {
    CONSOLE_CURSOR_INFO lpCursor;
    lpCursor.bVisible = visible;
    lpCursor.dwSize = size;
    SetConsoleCursorInfo(console, &lpCursor);
}

// Enemy Structure
struct Enemy {
    int x, y;
};

// Player Class
class Player {
public:
    string name;
    int score;

    Player(string name, int score = 0) : name(name), score(score) {}

    void saveScore(map<string, Player>& highScores) {
        if (highScores.find(name) == highScores.end() || highScores[name].score < score) {
            highScores[name] = *this;
        }
    }

    void display() const {
        cout << name << ": " << score << endl;
    }
};

// Game Class
class Game {
private:
    int carPos;
    bool gameOver;
    list<Enemy> enemies;
    Player* currentPlayer;
    map<string, Player> highScores;

public:
    Game() : carPos(WIN_WIDTH / 2), gameOver(false), currentPlayer(nullptr) {}

    void drawBorder() {
        for (int i = 0; i < SCREEN_HEIGHT; i++) {
            gotoxy(0, i);
            cout << "|";
            gotoxy(WIN_WIDTH, i);
            cout << "|";
        }
    }

    void drawCar() {
        gotoxy(carPos, SCREEN_HEIGHT - 2);
        cout << "  M ";
        gotoxy(carPos, SCREEN_HEIGHT - 1);
        cout << " WMW ";
    }

    void eraseCar() {
        gotoxy(carPos, SCREEN_HEIGHT - 2);
        cout << "     ";
        gotoxy(carPos, SCREEN_HEIGHT - 1);
        cout << "     ";
    }

    void spawnEnemy() {
        Enemy newEnemy = {rand() % (WIN_WIDTH - 4), 0};
        if (enemies.empty()) {
            enemies.push_back(newEnemy);
        } else {
            auto it = lower_bound(enemies.begin(), enemies.end(), newEnemy, [](const Enemy& a, const Enemy& b) {
                return a.y < b.y;
            });
            enemies.insert(it, newEnemy);
        }
    }

    void drawEnemies() {
        for (const auto& e : enemies) {
            gotoxy(e.x, e.y);
            cout << "####";
        }
    }

    void eraseEnemies() {
        for (const auto& e : enemies) {
            gotoxy(e.x, e.y);
            cout << "    ";
        }
    }

    bool checkCollision() {
        for (const auto& e : enemies) {
            if (e.y >= SCREEN_HEIGHT - 2 && e.x >= carPos && e.x < carPos + 4) {
                return true;
            }
        }
        return false;
    }

    void updateEnemies() {
        for (auto it = enemies.begin(); it != enemies.end();) {
            it->y++;
            if (it->y >= SCREEN_HEIGHT) {
                it = enemies.erase(it);
                currentPlayer->score++;
            } else {
                ++it;
            }
        }
        if (rand() % 10 < 2) { // Random chance to spawn a new enemy
            spawnEnemy();
        }
    }

    void updateScore() {
        gotoxy(WIN_WIDTH + 2, 5);
        cout << "Score: " << currentPlayer->score;
    }

    void gameOverScreen() {
        system("cls");
        cout << "\n\n\t\t--------------------------\n";
        cout << "\t\t-------- GAME OVER -------\n";
        cout << "\t\t--------------------------\n\n";
        cout << "\t\tYour Score: " << currentPlayer->score << endl;
        currentPlayer->saveScore(highScores);
        saveScores();
        cout << "\n\n\t\tPress any key to exit.";
        getch();
    }

    void play() {
        carPos = WIN_WIDTH / 2;
        gameOver = false;
        int speed = 200; // Slower initial speed (increased sleep time)
        enemies.clear(); // Clear enemies list

        system("cls");
        drawBorder();
        updateScore();
        spawnEnemy();

        while (!gameOver) {
            if (_kbhit()) {
                char ch = _getch();
                if (ch == 'a' || ch == 'A') {
                    if (carPos > 1) { // Ensure car doesn't move out of bounds
                        eraseCar();
                        carPos -= 2;
                    }
                } else if (ch == 'd' || ch == 'D') {
                    if (carPos < WIN_WIDTH - 7) { // Ensure car doesn't move out of bounds
                        eraseCar();
                        carPos += 2;
                    }
                } else if (ch == 27) { // ESC key
                    break;
                }
            }

            eraseEnemies();
            updateEnemies();
            drawCar();
            drawEnemies();
            updateScore();

            if (checkCollision()) {
                gameOver = true;
            }

            Sleep(speed); // Dynamic sleep time based on speed

            // Increase speed as the score increases
            if (currentPlayer->score % 10 == 0 && speed > 50) { // Increase speed every 10 points, slower increment
                speed -= 10; // Decrease sleep time to increase speed
            }
        }

        gameOverScreen();
    }

    void showMenu() {
        while (true) {
            system("cls");
            gotoxy(10, 5);
            cout << "--------------------------";
            gotoxy(10, 6);
            cout << "|       NEVER BACK DOWN         |";
            gotoxy(10, 7);
            cout << "--------------------------";
            gotoxy(10, 9);
            cout << "1. Start Game";
            gotoxy(10, 10);
            cout << "2. View Scores";
            gotoxy(10, 11);
            cout << "3. Quit";
            gotoxy(10, 13);
            cout << "Select an option: ";
            char op = _getch();

            if (op == '1') {
                login();
                play();
            } else if (op == '2') {
                showScores();
            } else if (op == '3') {
                exit(0);
            }
        }
    }

    void login() {
        system("cls");
        string name;
        cout << "Enter your name: ";
        cin >> name;
        currentPlayer = new Player(name);
        loadScores();
    }

    void saveScores() {
        ofstream file("scores.txt");
        for (const auto& entry : highScores) {
            file << entry.second.name << " " << entry.second.score << endl;
        }
        file.close();
    }

    void loadScores() {
        highScores.clear();
        ifstream file("scores.txt");
        string name;
        int score;
        while (file >> name >> score) {
            highScores[name] = Player(name, score);
        }
        file.close();
    }

    void showScores() {
        system("cls");
        loadScores();
        cout << "Player Scores:\n";
        cout << "--------------\n";
        // Create a vector of pairs from the map for sorting
        vector<pair<string, Player>> scoreVector(highScores.begin(), highScores.end());
        // Sort the scores in descending order
        sort(scoreVector.begin(), scoreVector.end(), [](const pair<string, Player>& a, const pair<string, Player>& b) {
            return b.second.score < a.second.score;
        });
        // Display the scores
        for (const auto& entry : scoreVector) {
            entry.second.display();
            cout << "--------------\n";
        }
        cout << "\nPress any key to return to the menu.";
        getch();
    }
};

// Main Function
int main() {
    setCursor(0, 0);
    srand(static_cast<unsigned>(time(NULL))); // Seed random number generator
    Game game;
    game.showMenu();
    return 0;
}
