#include <iostream>
#include <limits>
#include <string>
#include <cctype>
#include <vector>
#include <algorithm>
#include <map>

#include "FrequencyTracker.h"

using namespace std;

// Calculate Levenshtein distance between two strings (measure of similarity)
static int calculateDistance(const string& s1, const string& s2) {
    int len1 = s1.length();
    int len2 = s2.length();
    
    vector<vector<int>> dp(len1 + 1, vector<int>(len2 + 1));
    
    for (int i = 0; i <= len1; i++) {
        for (int j = 0; j <= len2; j++) {
            if (i == 0) {
                dp[i][j] = j;
            } else if (j == 0) {
                dp[i][j] = i;
            } else if (s1[i-1] == s2[j-1]) {
                dp[i][j] = dp[i-1][j-1];
            } else {
                dp[i][j] = 1 + min({dp[i-1][j], dp[i][j-1], dp[i-1][j-1]});
            }
        }
    }
    
    return dp[len1][len2];
}

// Find similar items based on edit distance and other factors
static vector<pair<string, int>> findSimilarItems(const string& input, const FrequencyTracker& tracker) {
    vector<pair<string, int>> suggestions;
    
    // Get all items from the tracker (we'll need to add a method to FrequencyTracker for this)
    // For now, let's use a predefined list of known items
    vector<string> knownItems = {
        "apples", "beets", "broccoli", "cantaloupe", "cauliflower", 
        "celery", "cranberries", "cucumbers", "garlic", "limes", 
        "onions", "peaches", "pears", "peas", "potatoes", 
        "pumpkins", "radishes", "spinach", "yams", "zucchini"
    };
    
    string lowerInput = input;
    transform(lowerInput.begin(), lowerInput.end(), lowerInput.begin(), ::tolower);
    
    for (const string& item : knownItems) {
        int distance = calculateDistance(lowerInput, item);
        int maxLen = max(lowerInput.length(), item.length());
        
        // Consider items similar if:
        // 1. Edit distance is small relative to word length
        // 2. Or if one string contains the other (substring match)
        // 3. Or if they start with the same letters
        
        bool isSimilar = false;
        
        // Edit distance threshold (allow 1-2 character differences for short words, more for longer)
        int threshold = maxLen <= 4 ? 1 : (maxLen <= 7 ? 2 : 3);
        if (distance <= threshold) {
            isSimilar = true;
        }
        
        // Substring matching (partial match)
        if (item.find(lowerInput) != string::npos || lowerInput.find(item) != string::npos) {
            isSimilar = true;
            distance = max(0, distance - 1); // Boost substring matches
        }
        
        // Starting letters match (good for partial typing)
        if (lowerInput.length() >= 2 && item.length() >= 2) {
            if (item.substr(0, 2) == lowerInput.substr(0, 2)) {
                isSimilar = true;
                distance = max(0, distance - 1); // Boost prefix matches
            }
        }
        
        if (isSimilar) {
            suggestions.push_back({item, distance});
        }
    }
    
    // Sort by similarity (lower distance = more similar)
    sort(suggestions.begin(), suggestions.end(), 
         [](const pair<string, int>& a, const pair<string, int>& b) {
             return a.second < b.second;
         });
    
    return suggestions;
}

// Enhanced function to get user input with typo correction
static string getValidItemInputWithCorrection(const FrequencyTracker& tracker) {
    string item;
    bool validInput = false;
    
    while (!validInput) {
        cout << "Enter item to search (letters only, no numbers/symbols): ";
        getline(cin, item);
        
        // Check if input is empty
        if (item.empty()) {
            cout << "Error: Input cannot be empty. Please try again.\n";
            continue;
        }
        
        // Check if input is too long (reasonable limit)
        if (item.length() > 50) {
            cout << "Error: Item name too long (max 50 characters). Please try again.\n";
            continue;
        }
        
        // Check if input contains only letters and spaces
        bool hasValidChars = true;
        bool hasLetters = false;
        
        for (char c : item) {
            if (!isalpha(c) && !isspace(c)) {
                hasValidChars = false;
                break;
            }
            if (isalpha(c)) {
                hasLetters = true;
            }
        }
        
        if (!hasValidChars) {
            cout << "Error: Item name can only contain letters and spaces. Please try again.\n";
            continue;
        }
        
        if (!hasLetters) {
            cout << "Error: Item name must contain at least one letter. Please try again.\n";
            continue;
        }
        
        // Clean up the input (remove extra spaces, etc.)
        size_t start = item.find_first_not_of(" \t");
        if (start == string::npos) {
            cout << "Error: Input contains only spaces. Please try again.\n";
            continue;
        }
        
        size_t end = item.find_last_not_of(" \t");
        item = item.substr(start, end - start + 1);
        
        string cleaned;
        bool prevWasSpace = false;
        for (char c : item) {
            if (isspace(c)) {
                if (!prevWasSpace) {
                    cleaned += ' ';
                    prevWasSpace = true;
                }
            } else {
                cleaned += c;
                prevWasSpace = false;
            }
        }
        item = cleaned;
        
        if (item.empty()) {
            cout << "Error: No valid content after cleaning. Please try again.\n";
            continue;
        }
        
        // Check if item exists exactly
        int frequency = tracker.countOf(item);
        if (frequency > 0) {
            validInput = true;
            break;
        }
        
        // Item not found - look for similar items
        vector<pair<string, int>> suggestions = findSimilarItems(item, tracker);
        
        if (!suggestions.empty()) {
            cout << "\nItem \"" << item << "\" not found. Did you mean one of these?\n";
            
            // Show up to 5 best suggestions
            for (size_t i = 0; i < min(size_t(5), suggestions.size()); i++) {
                int freq = tracker.countOf(suggestions[i].first);
                cout << (i + 1) << ". " << suggestions[i].first 
                     << " (found " << freq << " times)\n";
            }
            
            cout << (suggestions.size() + 1) << ". None of these - try again\n";
            cout << "Choose an option (1-" << (suggestions.size() + 1) << "): ";
            
            int choice;
            if (cin >> choice) {
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                
                if (choice >= 1 && choice <= (int)suggestions.size()) {
                    item = suggestions[choice - 1].first;
                    validInput = true;
                    cout << "Selected: " << item << "\n";
                } else if (choice == (int)suggestions.size() + 1) {
                    cout << "Please try entering the item name again.\n\n";
                    // Continue the loop to ask for input again
                } else {
                    cout << "Invalid choice. Please try again.\n\n";
                }
            } else {
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                cout << "Invalid input. Please try again.\n\n";
            }
        } else {
            cout << "\nItem \"" << item << "\" not found and no similar items detected.\n";
            cout << "Please check your spelling and try again.\n";
            cout << "Type 'list' to see all available items, or try again: ";
            
            string response;
            getline(cin, response);
            
            if (response == "list" || response == "LIST") {
                cout << "\nAvailable items:\n";
                cout << "apples, beets, broccoli, cantaloupe, cauliflower, celery,\n";
                cout << "cranberries, cucumbers, garlic, limes, onions, peaches,\n";
                cout << "pears, peas, potatoes, pumpkins, radishes, spinach, yams, zucchini\n\n";
            }
            // Continue the loop
        }
    }
    
    return item;
}

static int readMenuChoice(int lo, int hi) {
    int x;
    while (true) {
        if (cin >> x && x >= lo && x <= hi) {
            cin.ignore(numeric_limits<streamsize>::max(), '\n'); // clear trailing newline
            return x;
        }
        cout << "Invalid input. Enter a number " << lo << "-" << hi << ": ";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }
}

int main() {
    FrequencyTracker tracker;

    // Load the input file first.
    if (!tracker.load()) {
        cerr << "Fatal: place CS210_Project_Three_Input_File.txt next to the executable.\n";
        return 1;
    }

    // Create backup file at startup (per spec).
    tracker.writeBackup();

    bool running = true;
    while (running) {
        cout << "\n===== Corner Grocer Menu =====\n";
        cout << "1. Search item frequency (with smart suggestions)\n";
        cout << "2. Print all item frequencies\n";
        cout << "3. Print histogram\n";
        cout << "4. Exit\n";
        cout << "Choose an option (1-4): ";

        int choice = readMenuChoice(1, 4);

        switch (choice) {
            case 1: {
                string item = getValidItemInputWithCorrection(tracker);
                int frequency = tracker.countOf(item);
                
                cout << "\nSearch Result:\n";
                cout << "Item: \"" << item << "\"\n";
                cout << "Frequency: " << frequency;
                
                if (frequency == 0) {
                    cout << " (Item not found in inventory)";
                } else if (frequency == 1) {
                    cout << " (Found once)";
                } else {
                    cout << " (Found " << frequency << " times)";
                }
                cout << "\n";
                break;
            }
            case 2:
                tracker.printAll(cout);
                break;
            case 3:
                tracker.printHistogram(cout, '*');
                break;
            case 4:
                cout << "Goodbye.\n";
                running = false;
                break;
        }
    }

    return 0;
}