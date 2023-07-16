#include <iostream>
#include <stdio.h>
#include <string>
#include <thread>
#include <chrono>

using namespace std;

void printProgress(int progress, int total, int maxScale) {
    float percentage = static_cast<float>(progress) / total * 100;
    std::cout << "Progress: [";
    int completed = static_cast<int>(percentage / (100/ maxScale));
    for (int i = 0; i < completed; i++) {
        std::cout << "#";
    }
    for (int i = completed; i < maxScale; i++) {
        std::cout << " ";
    }
    std::cout << "] " << static_cast<int>(percentage) << "%\r";
    std::cout.flush();
}

void simulateWork(int duration, int total) {
    for (int i = 0; i <= total; i++) {
        printProgress(i, total, 50);
        std::this_thread::sleep_for(std::chrono::milliseconds(duration));
    }
    std::cout << std::endl << "Work completed!" << std::endl;
}

int main() {
    int total = 100;
    int duration = 100; // milliseconds
    simulateWork(duration, total);
    return 0;
}
