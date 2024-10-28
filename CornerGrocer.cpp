#include <iostream>
#include <fstream>
#include <map>
#include <string>
#include <limits> // For input validation

class ItemTracker {
private:
    std::map<std::string, int> itemFrequencies; // Map to store items and their frequencies

public:
    // Function to load data from the input file
    void LoadData(const std::string& fileName) {
        std::ifstream inputFile(fileName);
        if (!inputFile.is_open()) {
            std::cerr << "Error: Unable to open file " << fileName << std::endl;
            return;
        }

        std::string item;
        while (inputFile >> item) {
            itemFrequencies[item]++; // Increase the frequency of each item
        }
        inputFile.close();
    }

    // Function to write frequencies to a backup file
    void WriteBackupFile() {
        std::ofstream backupFile("frequency.dat");
        if (!backupFile.is_open()) {
            std::cerr << "Error: Unable to create backup file!" << std::endl;
            return;
        }

        for (const auto& entry : itemFrequencies) {
            backupFile << entry.first << " " << entry.second << std::endl;
        }
        backupFile.close();
    }

    // Function to get the frequency of a specific item
    int GetItemFrequency(const std::string& item) const {
        auto it = itemFrequencies.find(item);
        if (it != itemFrequencies.end()) {
            return it->second;
        }
        else {
            return 0; // Item not found
        }
    }

    // Function to print all items and their frequencies
    void PrintAllItems() const {
        for (const auto& entry : itemFrequencies) {
            std::cout << entry.first << " " << entry.second << std::endl;
        }
    }

    // Function to print a histogram of item frequencies
    void PrintHistogram() const {
        for (const auto& entry : itemFrequencies) {
            std::cout << entry.first << " ";
            for (int i = 0; i < entry.second; ++i) {
                std::cout << "*"; // Print asterisks equal to the frequency
            }
            std::cout << std::endl;
        }
    }
};

int main() {
    ItemTracker tracker;
    tracker.LoadData("CS210_Project_Three_Input_File.txt");
    tracker.WriteBackupFile(); // Backup the frequency data at the start

    int choice;

    do {
        // Display menu options
        std::cout << "1. Find item frequency\n";
        std::cout << "2. Print all items\n";
        std::cout << "3. Print histogram\n";
        std::cout << "4. Exit\n";
        std::cout << "Enter your choice: ";

        // Validate input and ensure it is an integer
        if (!(std::cin >> choice)) {
            std::cin.clear();  // Clear the error flag
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');  // Ignore invalid input
            std::cout << "Invalid input! Please enter a number between 1 and 4." << std::endl;
            continue;
        }

        // Check if input is within the valid range
        if (choice < 1 || choice > 4) {
            std::cout << "Invalid option, please try again." << std::endl;
            continue;
        }

        // Handle the different menu options
        if (choice == 1) {
            std::string item;
            std::cout << "Enter the item name: ";
            std::cin >> item;
            std::cout << "Frequency: " << tracker.GetItemFrequency(item) << std::endl;
        }
        else if (choice == 2) {
            tracker.PrintAllItems();
        }
        else if (choice == 3) {
            tracker.PrintHistogram();
        }
    } while (choice != 4);

    std::cout << "Exiting program." << std::endl;
    return 0;
}
