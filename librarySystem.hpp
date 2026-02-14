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
    const string dataFolder{"library_data"};
    const string dataFile{"library_data.json"};
    public:
    void loadData(void);
    void saveData(void) const;
    void addBook(void);
    void addUser(void);
    void borrowBook(const string &userId, const string &bookId);
    void returnBook(const string &userId, const string &bookId);
    void run(void);
};
#endif