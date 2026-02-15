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
        cout << "==================== Library System Menu ====================" << endl;
        ifstream menu("menu.txt");
        if (!menu.is_open())
        {
            cout << "Failed to open menu.txt" << endl;
            return;
        }
        cout << menu.rdbuf();
        menu.close();

        int tmpChoice;
        cin >> tmpChoice;
        choice = static_cast<MenuOption>(tmpChoice);
        Book newBook{"", "", "", "", 0, 0, {}};
        switch (choice)
        {
        case MenuOption::ADD_BOOK:

            addBook();

            break;
        case MenuOption::SEARCH_BOOK_BY_PREFIX:
            searchBookByPrefix();

            break;

        case MenuOption::PRINT_WHO_BORROWED_BOOK_BY_NAME:
            printWhoBorrowedBook();

            break;
        case MenuOption::PRINT_LIBRARY_BY_ID:
            printByID();
            break;
        case MenuOption::PRINT_LIBRARY_BY_NAME:
            printByName();
            break;

        case MenuOption::ADD_USER:
            addUser();
            break;
        case MenuOption::USER_BORROW_BOOK:
            borrowBook();
            break;
        case MenuOption::USER_RETURN_BOOK:
            returnBook();

            break;
        case MenuOption::PRINT_USERS:
            printUsers();
            break;

        case MenuOption::Exit:

            break;

        default:
            cout << "Invalid choice." << endl;
            cin.clear(); // Clear the error flags
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            break;
        }
        saveData();
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
    jsonToBooks(LibraryData["books"], books);
    jsonToUsers(LibraryData["users"], users);
    lastBookId = LibraryData["lastBookId"];
    lastUserId = LibraryData["lastUserId"];
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
}

void LibrarySystem::addUser(void)
{
    User newUser = {"", "", "", {}};
    cin.ignore();
    cout << "Enter user name: ";
    getline(cin, newUser.name);
    if (newUser.name.empty())
    {
        cout << "User name cannot be empty." << endl;
        return;
    }
    cout << "Enter user email: ";
    getline(cin, newUser.email);
    if (newUser.email.empty())
    {
        cout << "User email cannot be empty." << endl;
        return;
    }
    newUser.id = IDGenerator::generateUserID(++lastUserId);
    users.push_back(newUser);
    cout << "User added successfully with ID: " << newUser.id << endl;
}
bool operator==(const User &u, const string &userId)
{
    return u.id == userId;
}
bool operator==(const Book &b, const string &bookId)
{
    return b.id == bookId;
}
void LibrarySystem::borrowBook(void)
{
    string userId, bookId;
    cin.ignore();
    cout << "Enter user ID: ";
    getline(cin, userId);
    cout << "Enter book ID: ";
    getline(cin, bookId);
    if (userId.empty() || bookId.empty())
    {
        cout << "User ID and Book ID cannot be empty." << endl;
        return;
    }

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
void LibrarySystem::searchBookByPrefix(void)
{
    cin.ignore();
    cout << "Enter book title prefix: ";
    string prefix;
    getline(cin, prefix);
    for (const auto &book : books)
    {

        if (book.title.rfind(prefix, 0) == 0)
        {
            cout << "ID: " << book.id << " | Title: " << book.title << " | Author: " << book.author << " | Year: " << book.year << " | Available Copies: " << book.getAvailableCopies() << endl;
        }
    }
}

void LibrarySystem::printWhoBorrowedBook(void) const
{
    cin.ignore();
    cout << "Enter book title: ";
    string title;
    getline(cin, title);
    auto bookIt = find_if(books.begin(), books.end(), [&](const Book &b)
                          { return b.title == title; });
    if (bookIt == books.end())
    {
        cout << "Book with title " << title << " not found." << endl;
        return;
    }
    if (bookIt->borrowedBy.empty())
    {
        cout << "No one has borrowed this book." << endl;
        return;
    }
    cout << "Users who borrowed \"" << bookIt->title << "\":" << endl;
    for (const auto &userId : bookIt->borrowedBy)
    {
        cout << "User ID: " << userId << endl;
    }
}

void LibrarySystem::printByID(void) const
{
    vector<Book> sortedBooks = books;
    sort(sortedBooks.begin(), sortedBooks.end(), [](const Book &a, const Book &b)
         { return a.id < b.id; });
    for (const auto &book : sortedBooks)
    {
        cout << "ID: " << book.id << " | Title: " << book.title << " | Author: " << book.author << " | Year: " << book.year << " | Available Copies: " << book.getAvailableCopies() << endl;
    }
}

void LibrarySystem::printByName(void) const
{
    vector<Book> sortedBooks = books;
    sort(sortedBooks.begin(), sortedBooks.end(), [](const Book &a, const Book &b)
         { return a.title < b.title; });
    for (const auto &book : sortedBooks)
    {
        cout << "ID: " << book.id << " | Title: " << book.title << " | Author: " << book.author << " | Year: " << book.year << " | Available Copies: " << book.getAvailableCopies() << endl;
    }
}

void LibrarySystem::returnBook(void)
{
    cin.ignore();
    cout << "Enter user ID" << endl;
    string userID;
    getline(cin, userID);
    cout << "Enter book ID" << endl;
    string bookID;
    getline(cin, bookID);
    if (userID.empty() || bookID.empty())
    {
        cout << "User ID and book ID can't be empty" << endl;
        return;
    }
    auto userIt = find_if(users.begin(), users.end(), [&](const User &u)
                          { return u == userID; });
    auto bookIt = find_if(books.begin(), books.end(), [&](const Book &b)
                          { return b == bookID; });
    if (userIt == users.end())
    {
        cout << "User with ID " << userID << " not found." << endl;
        return;
    }
    if (bookIt == books.end())
    {
        cout << "Book with ID " << bookID << " not found." << endl;
        return;
    }
    auto &borrowed = userIt->borrowedBooks;
    auto borrowedIt = find(borrowed.begin(), borrowed.end(), bookID);
    if (borrowedIt == borrowed.end())
    {
        cout << "User with ID " << userID << " didn't borrow book with ID" << bookID << "." << endl;
        return;
    }
    borrowed.erase(borrowedIt);

    auto &borrowers = bookIt->borrowedBy;
    auto borrowerIt = find(borrowers.begin(), borrowers.end(), userID);
    if (borrowerIt == borrowers.end())
    {
        cout << "Book with ID " << bookID << " wasn't borrowed by user with ID " << userID << "." << endl;
        return;
    }
    borrowers.erase(borrowerIt);
}

void LibrarySystem::printUsers(void) const
{
    for (const auto &user : users)
    {
        cout << "ID: " << user.id << " | Name: " << user.name << " | Email: " << user.email << endl;
    }
}