# Corner Grocer — Item Frequency Tracker

CS210 coursework (SNHU). A menu-driven C++ console app that reads a
plain-text transaction log and reports how often each grocery item appears.

## What it does

Four menu options:

1. **Search** — look up a single item by name, get its count
2. **List** — print every item and its frequency, alphabetically
3. **Histogram** — same list but visualized with `*` bars
4. **Exit**

On startup it loads the transaction file and writes a backup (`frequency.dat`)
with each item and its count.

## Project structure

```
cornergrocer-project/
├── main.cpp               # Menu loop and input validation
├── FrequencyTracker.h     # Class interface
├── FrequencyTracker.cpp   # Load, count, print, backup
└── CS210_Project_Three_Input_File.txt  # Sample input (one item per line)
```

## Tech

C++17 · STL (`std::map`, `fstream`, `iostream`) · Visual Studio 2022

## Building

```bash
g++ -std=c++17 main.cpp FrequencyTracker.cpp -o corner_grocer
./corner_grocer
```

The input file must be in the same directory as the executable.

## Implementation notes

- Items stored in `std::map<string, int>` — gives alphabetical order and
  O(log n) lookup for free
- All input is lowercased before storing, so "Apple" and "apple" are the
  same item
- User input is validated for empty strings, length (max 50 chars),
  and character set (letters and spaces only) before any lookup happens
- Output uses ANSI color codes for readability in supported terminals
