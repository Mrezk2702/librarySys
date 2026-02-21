#ifndef LIBRARYSYSTEM_HPP
#define LIBRARYSYSTEM_HPP
#include <vector>
#include "types.hpp"
class LibrarySystem
{
private:
    vector<Book> books;
    vector<User> users;
    int lastBookId;
    int lastUserId;
    const string dataFolder{"..//library_data"};
    const string dataFile{"library_data.json"};

    void loadData(void);
    void saveData(void) const;
    void addBook(void);
    void addUser(void);
    void borrowBook(void);
    void returnBook(const string &userId, const string &bookId);
    void searchBookByPrefix(void);
    void printWhoBorrowedBook(void) const;
    void printByID(void) const;
    void printByName(void) const;
    void returnBook(void);
    void printUsers(void) const;

public:
    void run(void);
    LibrarySystem() 
    {
        loadData();
    }
    ~LibrarySystem()
    {
        saveData();
    }
};
#endif