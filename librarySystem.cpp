#include "librarySystem.hpp"
#include <fstream>
#include <iostream>
#include <nlohmann/json.hpp>
#include "json_handler.hpp"
#include <filesystem>
#include "id_generator.hpp"
using json = nlohmann::json;
namespace fs = std::filesystem;
using namespace std;

void LibrarySystem::run(void)
{
    loadData();
    MenuOption choice = MenuOption::INIT;
    while (choice != MenuOption::Exit)
    {
        ifstream menu("menu.txt");
        if (!menu.is_open())
        {
            cout << "Failed to open menu.txt" << endl;
            return;
        }
        cout << menu.rdbuf();
        menu.close();

        cout << "Enter your choice: ";
        int tmpChoice;
        cin >> tmpChoice;
        choice = static_cast<MenuOption>(tmpChoice);
        Book newBook{"", "", "", "", 0, 0, {}};
        switch (choice)
        {
        case MenuOption::ADD_BOOK:

            addBook();

            break;

        case MenuOption::Exit:
            break;

        default:
            cout << "Invalid choice." << endl;
            break;
        }
    }
    cout << "Exiting the program. Goodbye!" << endl;
}

void LibrarySystem::loadData(void)
{
    auto filename = fs::path(this->dataFolder) / dataFile;
    ifstream inFile(filename);
    if (!inFile.is_open())
    {
        cout << "Failed to open " << filename << " for reading" << endl;
        return;
    }
    json LibraryData;
    inFile >> LibraryData;
    inFile.close();
    cout << LibraryData.dump(4) << endl;
    jsonToBooks(LibraryData["books"], books);
    jsonToUsers(LibraryData["users"], users);
    lastBookId = LibraryData["lastBookId"];
    lastUserId = LibraryData["lastUserId"];
    for (const auto &book : books)
    {
        cout << "Book ID: " << book.id << ", Title: " << book.title << ", Author: " << book.author << ", Year: " << book.year << ", Total Copies: " << book.totalCopies << ", Available Copies: " << book.getAvailableCopies() << endl;
    }
    for (const auto &user : users)
    {
        cout << "User ID: " << user.id << ", Name: " << user.name << ", Email: " << user.email << endl;
    }
}

void LibrarySystem::saveData(void) const
{
    try
    {
        json LibraryData;
        booksToJson(LibraryData["books"], books);
        usersToJson(LibraryData["users"], users);
        LibraryData["lastBookId"] = lastBookId;
        LibraryData["lastUserId"] = lastUserId;

        fs::create_directories(this->dataFolder);
        fs::path fullPath = fs::path(this->dataFolder) / dataFile;

        ofstream outFile(fullPath);
        if (!outFile.is_open())
        {
            cout << "Failed to open " << fullPath << " for writing" << endl;
            return;
        }

        outFile << LibraryData.dump(4) << endl;
        outFile.close();
    }
    catch (const fs::filesystem_error &e)
    {
        std::cerr << e.what() << '\n';
    }
}
void LibrarySystem::addBook(void)
{
    Book newBook{"", "", "", "", 0, 0, {}};
    cin.ignore();

    cout << "Enter book title: ";
    getline(cin, newBook.title);
    if (newBook.title.empty())
    {
        cout << "Book title cannot be empty." << endl;
        return;
    }

    cout << "Enter book author: ";
    getline(cin, newBook.author);
    if (newBook.author.empty())
    {
        cout << "Book author cannot be empty." << endl;
        return;
    }

    cout << "Enter book year: ";
    getline(cin, newBook.year);
    cout << "Enter total copies: ";
    cin >> newBook.totalCopies;
    newBook.id = IDGenerator::generateBookID(++lastBookId);
    books.push_back(newBook);
    cout << "Book added successfully with ID: " << newBook.id << endl;
    saveData();
}

void LibrarySystem::addUser(const User &user)
{
    users.push_back(user);
    lastUserId++;
}
bool operator==(const User &u, const string &userId)
{
    return u.id == userId;
}
bool operator==(const Book &b, const string &bookId)
{
    return b.id == bookId;
}
void LibrarySystem::borrowBook(const string &userId, const string &bookId)
{
    auto userIt = find_if(users.begin(), users.end(), [&](const User &u)
                          { return u == userId; });
    auto bookIt = find_if(books.begin(), books.end(), [&](const Book &b)
                          { return b == bookId; });
    if (userIt == users.end())
    {
        cout << "User with ID " << userId << " not found." << endl;
        return;
    }
    if (bookIt == books.end())
    {
        cout << "Book with ID " << bookId << " not found." << endl;
        return;
    }
    if (bookIt->isAvailable())
    {
        bookIt->borrowedBy.push_back(userId);
        userIt->borrowedBooks.push_back(bookId);
    }
    else
    {
        cout << "Book with ID " << bookId << " is not available." << endl;
    }
}
