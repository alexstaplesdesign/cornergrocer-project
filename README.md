# Corner Grocer Inventory Tracker

A C++ application for tracking grocery item frequencies with professional input validation and multiple display options.

## 📋 Project Overview

This Corner Grocer application was developed as part of CS 210 Programming Languages coursework. It demonstrates object-oriented programming principles, STL container usage, and robust input validation techniques.

## ✨ Features

- **Item Frequency Tracking**: Count occurrences of grocery items from input data
- **Multiple Display Options**: 
  - Individual item search
  - Complete inventory listing
  - Visual histogram representation
- **Robust Input Validation**: Handles invalid input gracefully with clear error messages
- **Case-Insensitive Processing**: Treats "Apple" and "apple" as the same item
- **Automatic Backup**: Creates frequency.dat backup file for data persistence

## 🛠️ Technical Implementation

### Core Technologies
- **C++ Standard Library**: STL containers and algorithms
- **std::map**: Efficient key-value storage with automatic sorting
- **File I/O**: Input file processing and backup file creation
- **Input Validation**: Character type checking and format validation

### Key Classes
- **FrequencyTracker**: Handles all inventory management functionality
- **Main Program**: User interface and program flow control

## 📁 File Structure

```
├── main.cpp                                    # Main program with user interface
├── FrequencyTracker.h                         # FrequencyTracker class declaration
├── FrequencyTracker.cpp                       # FrequencyTracker class implementation
├── CS210_Project_Three_Input_File.txt         # Sample input data
└── README.md                                  # Project documentation
```

## 🚀 Getting Started

### Prerequisites
- C++ compiler (Visual Studio Build Tools or MinGW)
- Windows environment (tested on Windows 10/11)

### Compilation
```bash
# Using Visual Studio Build Tools
cl.exe /EHsc main.cpp FrequencyTracker.cpp /Fe:CornerGrocer.exe

# Using MinGW
g++ -std=c++11 main.cpp FrequencyTracker.cpp -o CornerGrocer.exe
```

### Running the Program
```bash
./CornerGrocer.exe
```

## 💡 Usage

1. **Search Item Frequency**: Enter an item name to find its occurrence count
2. **View Complete Inventory**: Display all items with their frequencies
3. **Generate Histogram**: Visual representation using asterisk symbols
4. **Exit**: Close the application

### Sample Input Data
The program reads from `CS210_Project_Three_Input_File.txt` containing grocery items like:
```
Spinach
Radishes
Broccoli
Peas
Cranberries
```

## 🎯 Programming Concepts Demonstrated

- **Object-Oriented Programming**: Class design and encapsulation
- **STL Containers**: std::map for efficient data storage and retrieval
- **Input Validation**: Comprehensive user input checking
- **File Processing**: Reading input files and creating backup files
- **Error Handling**: Graceful handling of file and input errors
- **Code Documentation**: Industry-standard inline comments in plain language

## 📊 Key Features Showcase

### Map Usage
```cpp
std::map<std::string, int> itemFrequencyMap;  // Automatic sorting and fast lookup
itemFrequencyMap[normalizedItemName]++;       // Efficient counting
```

### Input Validation
```cpp
// Ensures only letters and spaces are accepted
for (char currentChar : userInput) {
    if (!isalpha(currentChar) && !isspace(currentChar)) {
        hasValidCharacters = false;
        break;
    }
}
```

## 👨‍💻 Author

**Alex Staples**  
CS 210 Programming Languages  
Southern New Hampshire University

## 📝 Academic Context

This project demonstrates proficiency in:
- C++ programming fundamentals
- Object-oriented design principles
- STL container implementation
- Professional coding standards
- Input validation techniques
- File I/O operations

---

*Developed as coursework for CS 210 Programming Languages, showcasing industry-standard C++ development practices.*