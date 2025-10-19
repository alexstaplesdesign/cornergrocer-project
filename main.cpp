/*
 * Author: Alex Staples
 * Last updated: October 18, 2025
 * SNHU CS210 Project Three - Corner Grocer item tracking program
 */

#include <iostream>
#include <limits>
#include <string>
#include <cctype>

#include "FrequencyTracker.h"

using namespace std;

// Program constants for maintainability and consistency
const int MAX_ITEM_NAME_LENGTH = 50;        // Maximum characters for item input
const int MENU_OPTION_MIN = 1;              // Minimum valid menu choice
const int MENU_OPTION_MAX = 4;              // Maximum valid menu choice

/**
 * Gets a valid item name from the user
 * Checks that input has only letters and spaces, isn't too long or empty
 * @return clean item name ready to search for
 */
static string getValidatedItemInput() {
    string userInput;
    bool isInputValid = false;
    
    // Input validation loop - continues until valid input received
    while (!isInputValid) {
        cout << "Enter item to search (letters only, no numbers/symbols): ";
        getline(cin, userInput);
        
        // Basic validation checks
        if (userInput.empty()) {
            cout << "Error: Input cannot be empty. Please try again.\n";
            continue;
        }
        
        if (userInput.length() > MAX_ITEM_NAME_LENGTH) {
            cout << "Error: Item name too long (max " << MAX_ITEM_NAME_LENGTH 
                 << " characters). Please try again.\n";
            continue;
        }
        
        // Character validation - ensure only letters and spaces
        bool hasValidCharacters = true;
        bool containsLetters = false;
        
        // Loop through each character to validate content
        for (char currentChar : userInput) {
            if (!isalpha(currentChar) && !isspace(currentChar)) {
                hasValidCharacters = false;
                break;
            }
            if (isalpha(currentChar)) {
                containsLetters = true;
            }
        }
        
        if (!hasValidCharacters) {
            cout << "Error: Item name can only contain letters and spaces. Please try again.\n";
            continue;
        }
        
        if (!containsLetters) {
            cout << "Error: Item name must contain at least one letter. Please try again.\n";
            continue;
        }
        
        // Clean up the input by removing extra spaces
        size_t firstNonSpace = userInput.find_first_not_of(" \t");
        if (firstNonSpace == string::npos) {
            cout << "Error: Input contains only spaces. Please try again.\n";
            continue;
        }
        
        // Remove leading and trailing spaces
        size_t lastNonSpace = userInput.find_last_not_of(" \t");
        userInput = userInput.substr(firstNonSpace, lastNonSpace - firstNonSpace + 1);
        
        // Turn multiple spaces into single spaces
        string normalizedInput;
        bool previousCharWasSpace = false;
        
        // Go through each character and fix spacing
        for (char currentChar : userInput) {
            if (isspace(currentChar)) {
                // Only add a space if the last character wasn't a space
                if (!previousCharWasSpace) {
                    normalizedInput += ' ';
                    previousCharWasSpace = true;
                }
            } else {
                normalizedInput += currentChar;
                previousCharWasSpace = false;
            }
        }
        userInput = normalizedInput;
        
        if (userInput.empty()) {
            cout << "Error: No valid content after cleaning. Please try again.\n";
            continue;
        }
        
        isInputValid = true;
    }
    
    return userInput;
}

/**
 * Gets a valid menu choice from the user
 * Keeps asking until they enter a number in the right range
 * @param minimumOption lowest acceptable number
 * @param maximumOption highest acceptable number  
 * @return valid menu choice number
 */
static int getValidatedMenuChoice(int minimumOption, int maximumOption) {
    int userChoice;
    
    // Keep trying until we get valid input
    while (true) {
        // Check if input is a number in the right range
        if (cin >> userChoice && userChoice >= minimumOption && userChoice <= maximumOption) {
            cin.ignore(numeric_limits<streamsize>::max(), '\n'); // clear leftover input
            return userChoice;
        }
        
        // Tell user what went wrong and try again
        cout << "Invalid input. Enter a number " << minimumOption << "-" 
             << maximumOption << ": ";
        
        // Clear the error and bad input
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }
}

/**
 * Main function - runs the Corner Grocer program
 * Loads data, shows menu, and handles user choices until they exit
 */
int main() {
    FrequencyTracker inventoryTracker;

    // Try to load the data file first - can't do anything without it
    cout << "Loading inventory data...\n";
    if (!inventoryTracker.load()) {
        cerr << "Fatal Error: Unable to load CS210_Project_Three_Input_File.txt" 
             << "\nPlease ensure the input file is in the same directory as the executable.\n";
        cout << "Press Enter to exit...";
        cin.get();
        return 1; // Exit with error code
    }

    // Create backup file as required
    cout << "Data loaded successfully. Creating backup...\n";
    inventoryTracker.writeBackup();

    // Main program loop - keep showing menu until user wants to quit
    bool isProgramRunning = true;
    while (isProgramRunning) {
        cout << "\n===== Corner Grocer Menu =====\n";
        cout << "1. Search item frequency\n";
        cout << "2. Print all item frequencies\n";
        cout << "3. Print histogram\n";
        cout << "4. Exit\n";
        cout << "Choose an option (1-4): ";

        int userMenuChoice = getValidatedMenuChoice(MENU_OPTION_MIN, MENU_OPTION_MAX);

        // Handle the user's choice
        switch (userMenuChoice) {
            case 1: {
                // Search for a specific item
                string searchItem = getValidatedItemInput();
                int itemFrequency = inventoryTracker.countOf(searchItem);
                
                // Show the search results
                cout << "\n=== SEARCH RESULT ===\n";
                cout << "Item: \"" << searchItem << "\"\n";
                cout << "Frequency: " << itemFrequency;
                
                // Give helpful context about the result
                if (itemFrequency == 0) {
                    cout << " (Item not found in inventory)";
                } else if (itemFrequency == 1) {
                    cout << " (Found once)";
                } else {
                    cout << " (Found " << itemFrequency << " times)";
                }
                cout << "\n";
                break;
            }
            case 2:
                // Show all items and their frequencies
                inventoryTracker.printAll(cout);
                break;
            case 3:
                // Show histogram visualization
                inventoryTracker.printHistogram(cout, '*');
                break;
            case 4:
                // User wants to quit
                cout << "Thank you for using Corner Grocer! Goodbye.\n";
                isProgramRunning = false;
                break;
        }
    }

    return 0;
}
