/*
 * Author: Alex Staples
 * Last updated: October 18, 2025
 * SNHU CS210 Project Three - Corner Grocer item tracking program
 */

#include "FrequencyTracker.h"
#include <fstream>
#include <iostream>
#include <algorithm>

// ANSI color codes for enhanced output formatting
const std::string COLOR_RESET = "\033[0m";
const std::string COLOR_GREEN = "\033[32m";
const std::string COLOR_YELLOW = "\033[33m";
const std::string COLOR_CYAN = "\033[36m";

// Constructor - just saves the file names for later use
FrequencyTracker::FrequencyTracker(const std::string& inputFilePath, const std::string& backupFilePath)
    : inputDataFilePath(inputFilePath), backupDataFilePath(backupFilePath) {
}

/**
 * Helper function to make strings lowercase
 * This lets us treat "Apple" and "apple" as the same item
 * @param inputString the string to convert
 * @return the same string but all lowercase
 */
std::string toLower(const std::string& inputString) {
    std::string lowercaseResult = inputString;
    std::transform(lowercaseResult.begin(), lowercaseResult.end(), 
                   lowercaseResult.begin(), ::tolower);
    return lowercaseResult;
}

/**
 * Reads the input file and counts how many times each item appears
 * Each line in the file should have one item name
 */
bool FrequencyTracker::load() {
    std::ifstream inputFileStream(inputDataFilePath);
    
    // Make sure we can actually open the file
    if (!inputFileStream.is_open()) {
        std::cerr << "Error: Unable to open input file: " << inputDataFilePath << std::endl;
        return false;
    }

    std::string currentItemName;
    
    // Read the file line by line
    while (std::getline(inputFileStream, currentItemName)) {
        // Skip empty lines
        if (currentItemName.empty()) {
            continue;
        }
        
        // Convert to lowercase so "Apple" and "apple" count as the same thing
        std::string normalizedItemName = toLower(currentItemName);
        // Add 1 to this item's count (creates the item if it's new)
        itemFrequencyMap[normalizedItemName]++;
    }

    inputFileStream.close();
    std::cout << "Successfully loaded " << itemFrequencyMap.size() 
              << " unique items from input file." << std::endl;
    
    return true;
}

bool FrequencyTracker::writeBackup() const {
    std::ofstream backupFileStream(backupDataFilePath);
    
    if (!backupFileStream.is_open()) {
        std::cerr << "Error: Unable to create backup file: " << backupDataFilePath << std::endl;
        return false;
    }

    // Write each item and its count to the backup file
    for (const auto& itemFrequencyPair : itemFrequencyMap) {
        const std::string& itemName = itemFrequencyPair.first;
        const int frequencyCount = itemFrequencyPair.second;
        backupFileStream << itemName << " " << frequencyCount << std::endl;
    }

    backupFileStream.close();
    std::cout << "Backup file '" << backupDataFilePath << "' created successfully." << std::endl;
    
    return true;
}

int FrequencyTracker::countOf(const std::string& itemName) const {
    std::string normalizedSearchTerm = toLower(itemName);
    auto itemIterator = itemFrequencyMap.find(normalizedSearchTerm);
    return (itemIterator != itemFrequencyMap.end()) ? itemIterator->second : 0;
}

void FrequencyTracker::printAll(std::ostream& outputStream) const {
    if (itemFrequencyMap.empty()) {
        outputStream << "No inventory data available to display." << std::endl;
        return;
    }

    outputStream << "\n=== COMPLETE INVENTORY REPORT ===" << std::endl;
    outputStream << "Item Name" << "\t\t" << "Frequency" << std::endl;
    outputStream << "----------------------------------------" << std::endl;

    // Print each item and its frequency count
    for (const auto& inventoryEntry : itemFrequencyMap) {
        const std::string& itemName = inventoryEntry.first;
        const int itemCount = inventoryEntry.second;
        outputStream << itemName << "\t\t" << itemCount << std::endl;
    }
    
    outputStream << "----------------------------------------" << std::endl;
}

void FrequencyTracker::printHistogram(std::ostream& outputStream, char displaySymbol) const {
    if (itemFrequencyMap.empty()) {
        outputStream << "No inventory data available for histogram display." << std::endl;
        return;
    }

    outputStream << "\n=== INVENTORY FREQUENCY HISTOGRAM ===" << std::endl;
    outputStream << "Visual representation of item frequencies:" << std::endl;
    outputStream << "----------------------------------------" << std::endl;

    // Print each item with visual bars showing frequency
    for (const auto& inventoryEntry : itemFrequencyMap) {
        const std::string& itemName = inventoryEntry.first;
        const int frequencyCount = inventoryEntry.second;
        
        outputStream << itemName << " ";
        
        // Print one symbol for each occurrence
        for (int symbolIndex = 0; symbolIndex < frequencyCount; ++symbolIndex) {
            outputStream << displaySymbol;
        }
        
        outputStream << " (" << frequencyCount << ")" << std::endl;
    }
    
    outputStream << "----------------------------------------" << std::endl;
}
