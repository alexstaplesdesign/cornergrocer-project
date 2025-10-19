/*
 * Author: Alex Staples
 * Last updated: October 18, 2025
 * SNHU CS210 Project Three - Corner Grocer item tracking program
 */

#ifndef FREQUENCY_TRACKER_H
#define FREQUENCY_TRACKER_H

#include <map>
#include <string>
#include <iosfwd>   // Forward declaration for std::ostream

/**
 * FrequencyTracker class
 * Counts how many times each item appears in an input file
 * Can save the counts to a backup file and display results different ways
 */
class FrequencyTracker {
public:
    /**
     * Constructor - sets up file names to use
     * @param inputFilePath name of file to read items from
     * @param backupFilePath name of file to save counts to
     */
    explicit FrequencyTracker(const std::string& inputFilePath = "CS210_Project_Three_Input_File.txt",
                              const std::string& backupFilePath = "frequency.dat");

    /**
     * Loads items from the input file and counts them
     * @return true if file loaded successfully, false if there was a problem
     */
    bool load();

    /**
     * Saves the item counts to a backup file
     * @return true if backup created successfully, false if there was a problem
     */
    bool writeBackup() const;

    /**
     * Gets the count for one specific item
     * @param itemName the item to look up (case doesn't matter)
     * @return how many times that item appears, or 0 if not found
     */
    int countOf(const std::string& itemName) const;

    /**
     * Prints all items and their counts in a neat list
     * @param outputStream where to send the output (usually cout)
     */
    void printAll(std::ostream& outputStream) const;

    /**
     * Prints a visual chart showing item frequencies
     * @param outputStream where to send the output (usually cout)
     * @param displaySymbol what character to use for the bars (default is *)
     */
    void printHistogram(std::ostream& outputStream, char displaySymbol = '*') const;

private:
    std::map<std::string, int> itemFrequencyMap; // stores item names and counts
    std::string inputDataFilePath;               // input file path
    std::string backupDataFilePath;              // backup file path
};

#endif // FREQUENCY_TRACKER_H
