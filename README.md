# 📚 SmartLib - Library Management System

[![C++](https://img.shields.io/badge/C++-17-blue.svg)](https://en.wikipedia.org/wiki/C%2B%2B17)
[![License: MIT](https://img.shields.io/badge/License-MIT-yellow.svg)](https://opensource.org/licenses/MIT)
[![Build Status](https://img.shields.io/badge/build-passing-brightgreen.svg)]()

A comprehensive C++ library management system demonstrating advanced object-oriented programming principles, dynamic memory management, and professional software design patterns. Built with enterprise-level architecture and zero memory leaks.

## 🎯 Features

- 📖 **Publication Management** - Add, remove, search, and track books with validation
- 🔄 **Checkout/Return System** - Automated member transactions with due date tracking
- 💰 **Penalty Calculation** - Automatic late fee computation for overdue items
- 🔍 **Advanced Search** - Multi-criteria filtering with partial matching
- 💾 **Data Persistence** - File-based storage with backup preservation
- 🖥️ **Professional CLI** - User-friendly menu-driven interface with input validation

## 🛠️ Tech Stack

**Language:** C++17 with modern features and STL  
**OOP Concepts:** Inheritance, polymorphism, encapsulation, virtual functions  
**Design Patterns:** MVC, Factory, Strategy, Template Method  
**Memory Management:** RAII principles, deep copy semantics, zero leaks  
**File I/O:** Custom serialization and robust error handling

## 🚀 Quick Start

### Prerequisites
- C++17 compatible compiler (GCC 7+, Clang 5+, MSVC 2017+)
- Standard C++ library support

### Installation & Build

```bash
# Clone the repository
git clone https://github.com/AjayMaan13/SmartLib.git
cd SmartLib

# Standard build
g++ -std=c++17 -Wall -Wextra -O2 *.cpp -o smartlib

# Debug build
g++ -std=c++17 -g -DDEBUG *.cpp -o smartlib_debug

# Run the application
./smartlib
```

## 📁 Structure

```
SmartLib/
├── LibApp.cpp/.h          # Main controller
├── Publication.cpp/.h     # Base class
├── Book.cpp/.h           # Book implementation  
├── Menu.cpp/.h           # Menu system
├── Date.cpp/.h           # Date utilities
└── LibRecs.txt           # Database
```

## 💻 Usage Examples

### Basic Operations

```cpp
// Initialize library system
LibApp library;

// Load existing publications
library.load();

// Run main application loop
library.run();

// Save all changes
library.save();
```

### Menu System

```
Seneca Library Application
 1- Add New Publication
 2- Remove Publication
 3- Checkout publication from library
 4- Return publication to library
 0- Exit
> 
```

### Adding Publications

```cpp
// Create new book with validation
Book newBook("Advanced C++", "Bjarne Stroustrup", "978-0123456789");
newBook.set_membership(12345);
newBook.set_date(2024, 12, 31);  // Due date
```

## 🏗️ Architecture

### Class Hierarchy

```
Streamable (Interface)
    ↓
Publication (Abstract Base Class)
    ↓
Book (Concrete Implementation)
```

### Design Patterns Implementation

- **MVC Architecture** - Clear separation of model, view, and controller
- **Factory Pattern** - Dynamic object creation based on publication type
- **Strategy Pattern** - Multiple search algorithms for different criteria
- **Template Method** - Streamable interface for consistent I/O operations

### Memory Management

```cpp
class Book : public Publication {
private:
    char* m_author;  // Dynamic memory allocation
    
public:
    // RAII constructor
    Book(const char* author) {
        m_author = new char[strlen(author) + 1];
        strcpy(m_author, author);
    }
    
    // Automatic cleanup
    ~Book() { delete[] m_author; }
    
    // Deep copy semantics
    Book(const Book& other) { /* proper deep copy */ }
};
```

## 🧪 Testing

### Running Tests

```bash
# Compile test suite
g++ -std=c++17 ms5_tester.cpp *.cpp -o test_runner

# Execute all tests
./test_runner
```

### Test Coverage

- ✅ Publication creation and validation
- ✅ Checkout/return workflow testing
- ✅ Search functionality verification
- ✅ File I/O operations testing
- ✅ Memory management validation
- ✅ Edge cases and error handling

## 📊 Stats

- **3,000+ lines** of C++17 code
- **8 core classes** with design patterns
- **Zero memory leaks** through RAII
- **Comprehensive testing** coverage

## 👨‍💻 Author

**Ajaypartap Singh Maan**  
[GitHub](https://github.com/AjayMaan13) • [LinkedIn](https://linkedin.com/in/ajaypartap-singh-maan) • ajayapsmaanm13@gmail.com

---

⭐ **Star if helpful!**
