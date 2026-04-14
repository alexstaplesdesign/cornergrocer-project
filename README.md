# Corner Grocer — Item Frequency Tracker

CS210 coursework (SNHU). A menu-driven C++ console app that reads a daily
transaction file and analyzes item purchase frequency.

## What it does

- Look up how many times a specific item was purchased
- Print a full frequency list for all items
- Display a histogram of purchase counts
- Back up frequency data to a `.dat` file on each run

## Tech

C++17 · STL (std::map, fstream, iostream) · Visual Studio 2022

## Running it

Open in Visual Studio and build, or compile with:

```bash
g++ -std=c++17 main.cpp FrequencyTracker.cpp -o corner_grocer
./corner_grocer
```

Input file expected at: `CS210_Project_Three_Input_File.txt`

## Notes

Uses `std::map` for O(log n) lookups and automatic alphabetical sorting.
Input validation handles empty strings, length limits, and case normalization.