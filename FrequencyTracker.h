#ifndef FREQUENCY_TRACKER_H
#define FREQUENCY_TRACKER_H

#include <map>
#include <string>
#include <iosfwd>   // for std::ostream forward-declare

// Tracks item frequencies from an input file and writes a backup file.
class FrequencyTracker {
public:
    // Construct with input and backup file paths.
    explicit FrequencyTracker(const std::string& t_inputPath = "CS210_Project_Three_Input_File.txt",
                              const std::string& t_backupPath = "frequency.dat");

    // Read items from input file (one item per line), case-insensitive.
    bool load();

    // Write "item count" lines to the backup file.
    bool writeBackup() const;

    // Return frequency for a single item (0 if not present). Case-insensitive.
    int countOf(const std::string& t_item) const;

    // Print "item count" for every item, sorted alphabetically.
    void printAll(std::ostream& os) const;

    // Print a histogram "item *****" with one symbol per count.
    void printHistogram(std::ostream& os, char symbol = '*') const;

private:
    std::map<std::string, int> m_freq; // sorted by item name (lowercased)
    std::string m_inputPath;
    std::string m_backupPath;
};

#endif