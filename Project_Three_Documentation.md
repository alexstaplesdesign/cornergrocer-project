# CS 210 Project Three: Corner Grocer Documentation
**Student:** Alex Staples  
**Date:** October 18, 2025  
**Course:** CS 210 Programming Languages  

## Program Overview
The Corner Grocer application is a C++ inventory tracking system designed to analyze item frequencies from input data. The program reads a list of grocery items, counts their occurrences, and provides multiple visualization options for the data. This solution demonstrates object-oriented programming principles, STL container usage, and user input validation.

## Design Architecture
The application follows a modular design with two primary components:

**FrequencyTracker Class:** This class encapsulates all inventory management functionality using a std::map<string, int> as the core data structure. The map automatically maintains items in alphabetical order while providing efficient O(log n) lookup times. Key methods include load() for reading input files, countOf() for individual item queries, printAll() for complete inventory display, and printHistogram() for visual representation.

**Main Program (main.cpp):** Implements the user interface and program flow control. Features robust input validation that checks for empty input, length limits, and character restrictions (letters and spaces only). The validation system also normalizes input by removing extra whitespace and converting to lowercase for case-insensitive matching.

## Key Features
**Data Processing:** The program reads the CS210_Project_Three_Input_File.txt and processes each line as an individual item name. All items are converted to lowercase to ensure case-insensitive tracking, treating "Apple" and "apple" as the same item.

**User Interface:** A menu-driven system offers four options: individual item frequency search, complete inventory listing, histogram visualization, and program exit. Input validation prevents crashes from invalid user entries and provides clear error messages.

**File Operations:** Automatic backup file creation (frequency.dat) stores item counts in "item count" format for data persistence and external use.

## Technical Implementation
The application leverages several C++ Standard Library features:
- **std::map** for efficient key-value storage and automatic sorting
- **std::string** manipulation with transform() for case conversion
- **std::ifstream/ofstream** for file input/output operations
- **Input validation** using character type checking functions (isalpha, isspace)

The program demonstrates industry-standard coding practices including comprehensive inline comments in plain language, meaningful variable names, and proper error handling. Function documentation follows clear parameter and return value specifications.

## Testing and Validation
The program successfully handles various input scenarios including mixed-case entries, items with spaces, and invalid input types. The validation system provides informative error messages and recovery mechanisms. The histogram feature creates visual representations using asterisk characters, with each symbol representing one occurrence of an item.

This implementation effectively demonstrates proficiency in C++ programming fundamentals, object-oriented design, STL container usage, and file processing while maintaining clean, readable code suitable for academic and professional environments.