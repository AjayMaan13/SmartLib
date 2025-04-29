# 📚 SmartLib, The Smart Library Management System

**May 2024 - June 2024**  
**Language:** C++ | **Concepts:** Object-Oriented Programming (OOP), Dynamic Memory Management, Operator Overloading, File Handling, Data Persistence, Command-Line Interface (CLI) Design

---

## Overview

The **Smart Library Management System** is a professional C++ project that simulates a real-world library’s core functionalities. Developed using **Object-Oriented Principles**, **dynamic memory management**, and **file handling**, the application features a clean and user-friendly **command-line interface** for managing publications and book records.  
This project reflects not only technical proficiency but also strong **software design practices**, **problem-solving skills**, and an emphasis on **maintainable, scalable code**.

Key highlights include:
- Managing book and publication records.
- Handling loaning, returning, and tracking due dates.
- Ensuring data persistence across sessions.
- Robust input validation and error management.
- Dynamic and modular system architecture.

---

## ✨ Key Features

- 📅 **Date Management** — Full date validation, comparison, and manipulation.
- 📜 **Dynamic Menu System** — User-friendly, modular CLI navigation.
- 📚 **Publication and Book Handling** — Streamlined management using inheritance and polymorphism.
- 💾 **Persistent Storage** — Load and save publication records via text files.
- 🔍 **Search & Selection Tools** — Powerful selector for finding publications based on custom criteria.
- 🛡️ **Input Validation** — Strong user input checking and error reporting system.
- 🔗 **Modular C++ Architecture** — Clean separation of concerns with reusable components.

---

## 🛠️ Technologies and Concepts Used

- **C++17 Standard**
- **Object-Oriented Programming (OOP)**
- **Dynamic Memory Management (New/Delete, Deep Copy)**
- **File Input/Output (Text-based Persistence)**
- **Operator Overloading**
- **Exception and Error Handling**
- **Command-Line Interface (CLI) Design**
- **Polymorphism, Inheritance, Encapsulation**

---

## 📂 Project Structure

```bash
├── Book.cpp / Book.h                 # Book class (derived from Publication)
├── Publication.cpp / Publication.h   # Publication base class
├── Streamable.cpp / Streamable.h      # Abstract interface for file operations
├── Date.cpp / Date.h                  # Date utilities and validation
├── Menu.cpp / Menu.h                  # CLI menu system
├── Lib.cpp / Lib.h                    # Core Library management (database)
├── LibApp.cpp / LibApp.h              # Application controller (workflow manager)
├── PublicationSelector.cpp / PublicationSelector.h # Search and selection logic
├── Utils.cpp / Utils.h                # Utility functions (helper methods)
├── LibAppMain.cpp                     # Main entry point for the app
├── LibAppMain_prof.cpp                # (Optional) Profile/main alternate
├── pubSel_Tester.cpp                  # PublicationSelector tester
├── LibRecs.txt / LibRecsSmall.txt     # Main persistent data files
├── origLibRecs.txt / origLibRecsSmall.txt # Sample/original datasets
├── ms5                               # Milestone 5 build (final product)
```

---

## 🧩 Milestone Roadmap

### Milestone 1: Core Utilities
- Created `Date`, `MenuItem`, and `Menu` classes with dynamic memory.
- Input validation and error status tracking in the Date module.

### Milestone 2: Streamable Interface
- Introduced `Streamable` abstract class for serialization/deserialization.

### Milestone 3: Publications and Books
- Designed `Publication` and `Book` classes leveraging polymorphism.
- Implemented dynamic memory management principles (deep copying).

### Milestone 4: Core Library Functionality
- Developed the `Lib` class for full publication lifecycle management.

### Milestone 5: Application Assembly
- Assembled the complete system through the `LibApp` controller.
- Added persistent file handling for seamless user experiences across sessions.

---

## 🚀 How to Run

1. Clone or download the repository.
2. Ensure a C++17 compliant compiler is available.
3. Build and run the application.

Example (Linux/MacOS):
```bash
g++ -std=c++17 -o libraryApp *.cpp
./libraryApp
```

Example (Windows):
```bash
g++ -std=c++17 -o libraryApp.exe *.cpp
libraryApp.exe
```

---

## 📈 Skills Demonstrated

- Advanced **C++ Programming**
- Practical **Dynamic Memory Management**
- **Object-Oriented System Design**
- **CLI Application Development**
- **File Handling & Persistence**
- **Software Engineering Best Practices** (SRP, modularity, reusability)

---

## 📣 Why This Project Stands Out

This is more than a simple class assignment — it’s a **full-cycle professional software project**.  
It demonstrates:
- **Problem-solving** in real-world inspired scenarios.
- **Attention to maintainability** through clean, modular code structure.
- **Solid mastery** of dynamic memory, error handling, data persistence, and complex OOP patterns.  
It reflects skills critical for **software development**, **system programming**, and **C++ application development** roles.

---

# 📬 Contact

> **Ajaypartap Singh Maan**  
> 📧 ajayapsmaanm13@gmail.com  
> 💼 Ajaypartap Singh Maan | AjayMaan13

---

# 🔖 Tags

`C++` `OOP` `Dynamic Memory` `Library Management System` `CLI Application` `File Handling` `Data Persistence` `Software Engineering` `Object-Oriented Design`

