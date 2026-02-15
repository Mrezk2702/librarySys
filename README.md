# Library System

A command-line library management system written in C++ that handles book inventory and user borrowing operations with persistent JSON-based data storage.

## Overview

This project provides a comprehensive library management solution that allows administrators to manage books, users, and borrowing transactions. The system maintains data persistence through JSON serialization and provides an interactive menu-driven interface.

## Features

- **Book Management**
  - Add new books with title, author, publication year, and copy count
  - Search books by prefix
  - View library inventory sorted by ID or title
  - Track available and borrowed copies per book

- **User Management**
  - Register new library users with email
  - View all registered users
  - Track user borrowing history

- **Borrowing System**
  - Users can borrow available books
  - Track which users have borrowed specific books
  - Return borrowed books with automatic inventory updates
  - View who borrowed a particular book by name

- **Data Persistence**
  - Automatic JSON serialization/deserialization
  - Persistent storage in `library_data/library_data.json`
  - Auto-load on startup, auto-save on exit

## Project Structure

```
libSys/
├── main.cpp                 # Application entry point
├── librarySystem.cpp        # Core library system implementation
├── librarySystem.hpp        # Library system class definition
├── types.hpp                # Data structures (Book, User, MenuOption)
├── json_handler.cpp         # JSON serialization/deserialization
├── json_handler.hpp         # JSON handler declarations
├── id_generator.hpp         # ID generation utilities for books and users
├── menu.txt                 # Menu display text
├── library_data/
│   └── library_data.json    # Persistent data storage
└── test.json                # Sample test data
```

## Data Structures

### Book
- **id**: Unique identifier (format: B-XXX)
- **title**: Book title
- **author**: Author name
- **year**: Publication year
- **totalCopies**: Total copies in inventory
- **availableCopies**: Currently available copies
- **borrowedBy**: List of user IDs who borrowed this book

### User
- **id**: Unique identifier (format: U-XXX)
- **name**: User name
- **email**: Email address
- **borrowedBooks**: List of currently borrowed book IDs

## Menu Options

1. Add Book - Register a new book in the system
2. Search Books by Prefix - Find books by title prefix
3. Print Who Borrowed Book by Name - View borrowers of a specific book
4. Print Library by ID - Display all books sorted by ID
5. Print Library by Name - Display all books sorted by title
6. Add User - Register a new library user
7. User Borrow Book - Record a book borrowing transaction
8. User Return Book - Record a book return transaction
9. Print Users - Display all registered users
10. Exit - Close the application

## Requirements

- **C++17** or later
- **nlohmann/json** library for JSON handling
- **Standard library** components: `<vector>`, `<string>`, `<fstream>`, `<filesystem>`

## Building

### On Linux/macOS

```bash
g++ -std=c++17 -o libsys main.cpp librarySystem.cpp json_handler.cpp -I/usr/include
```

Or using CMake:

```bash
mkdir build
cd build
cmake ..
make
```

## Running

```bash
./libsys
```

The application will display an interactive menu. Enter the number corresponding to your desired action and follow the prompts.

## Data Storage

Library data is automatically saved to `library_data/library_data.json` in JSON format, allowing for:
- Easy inspection and debugging
- Integration with external tools
- Backup and migration capabilities

Example data structure:

```json
{
  "books": [
    {
      "id": "B-001",
      "title": "Sample Book",
      "author": "Author Name",
      "year": "2024",
      "totalCopies": 5,
      "availableCopies": 3,
      "borrowedBy": ["U-001", "U-002"]
    }
  ],
  "users": [
    {
      "id": "U-001",
      "name": "John Doe",
      "email": "john@example.com",
      "borrowedBooks": ["B-001"]
    }
  ],
  "lastBookId": 1,
  "lastUserId": 1
}
```

## Dependencies

- **nlohmann/json**: Modern JSON for C++ (https://github.com/nlohmann/json)

Install via:

```bash
# Ubuntu/Debian
sudo apt-get install nlohmann-json3-dev

# macOS
brew install nlohmann-json
```


## Author

Mohamed Rezk-Bayoumi

---

For issues, feature requests, or contributions, please open an issue or submit a pull request.
