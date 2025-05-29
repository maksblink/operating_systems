#include <iostream>
#include <thread>
#include <mutex>
#include <vector>
#include <chrono>
#include <windows.h>

const int SIMULATION_TIME = 3000000;
// const int SIMULATION_TIME = 3;
const int MAX_MEALS = 3;

std::mutex* forks = nullptr;
std::mutex cout_mutex;

// Zmodyfikowana funkcja setColor z dodatkowymi zabezpieczeniami
void setColor(int color) {
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    if (hConsole != INVALID_HANDLE_VALUE) {
        SetConsoleTextAttribute(hConsole, color);
    }
}

void drawTable(const std::vector<std::string>& states, const std::vector<int>& meals, int NUM_PHILOSOPHERS) {
    std::lock_guard<std::mutex> lock(cout_mutex);
    system("cls");

    // Nagłówek z prostszym formatowaniem
    setColor(9); // Niebieski (bardziej uniwersalny)
    std::cout << "====================================\n";
    std::cout << "      DINING PHILOSOPHERS SIM      \n";
    std::cout << "====================================\n";
    setColor(7); // Powrót do domyślnego koloru

    for (int i = 0; i < NUM_PHILOSOPHERS; ++i) {
        std::cout << "Philosopher " << i << ": ";
        if (states[i] == "thinking...") {
            setColor(10); // Jasny zielony
        } else if (states[i] == "eating!") {
            setColor(12); // Jasny czerwony
        } else if (states[i] == "full") {
            setColor(14); // Jasny żółty
        }
        std::cout << states[i];
        setColor(7); // Powrót do domyślnego koloru
        std::cout << " (meals: " << meals[i] << ")\n";
    }

    // Stopka
    setColor(9); // Niebieski
    std::cout << "====================================\n";
    setColor(7); // Powrót do domyślnego koloru
}

void philosopher(int id, std::vector<std::string>& states, std::vector<int>& meals, int NUM_PHILOSOPHERS) {
    int left_fork = id;
    int right_fork = (id + 1) % NUM_PHILOSOPHERS;

    auto start = std::chrono::steady_clock::now();
    while (std::chrono::steady_clock::now() - start < std::chrono::seconds(SIMULATION_TIME)) {
        if (meals[id] >= MAX_MEALS) {
            states[id] = "full";
            drawTable(states, meals, NUM_PHILOSOPHERS);
            break;
        }

        // Myślenie
        states[id] = "thinking...";
        drawTable(states, meals, NUM_PHILOSOPHERS);
        std::this_thread::sleep_for(std::chrono::milliseconds(1000));

        // Jedzenie
        {
            std::lock_guard<std::mutex> lock1(forks[std::min(left_fork, right_fork)]);
            std::lock_guard<std::mutex> lock2(forks[std::max(left_fork, right_fork)]);

            states[id] = "eating!";
            meals[id]++;
            drawTable(states, meals, NUM_PHILOSOPHERS);
            std::this_thread::sleep_for(std::chrono::milliseconds(1000));
        }
    }
}

int main() {
    int NUM_PHILOSOPHERS;
    std::cout << "Enter the number of philosophers: ";
    std::cin >> NUM_PHILOSOPHERS;

    forks = new std::mutex[NUM_PHILOSOPHERS];

    // Inicjalizacja konsoli - dodatkowe zabezpieczenie
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    if (hConsole == INVALID_HANDLE_VALUE) {
        std::cerr << "Error: Could not get console handle\n";
        return 1;
    }

    // Ustawienie trybu konsoli obsługującego kolory
    DWORD mode = 0;
    if (!GetConsoleMode(hConsole, &mode)) {
        std::cerr << "Error: Could not get console mode\n";
        return 1;
    }
    mode |= ENABLE_VIRTUAL_TERMINAL_PROCESSING;
    if (!SetConsoleMode(hConsole, mode)) {
        std::cerr << "Warning: Could not set console mode, colors may not work properly\n";
    }

    std::vector<std::thread> philosophers;
    std::vector<std::string> states(NUM_PHILOSOPHERS, "thinking...");
    std::vector<int> meals(NUM_PHILOSOPHERS, 0);

    for (int i = 0; i < NUM_PHILOSOPHERS; ++i) {
        philosophers.emplace_back(philosopher, i, std::ref(states), std::ref(meals), NUM_PHILOSOPHERS);
    }

    for (auto& ph : philosophers) {
        ph.join();
    }

    delete[] forks;

    // Komunikat końcowy
    setColor(9); // Niebieski
    std::cout << "\n  Simulation completed successfully!\n";
    setColor(7); // Powrót do domyślnego koloru

    return 0;
}