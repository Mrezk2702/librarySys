#ifndef TYPES_HPP
#define TYPES_HPP
#include <string>
#include <vector>
using namespace std;
struct Book
{
    string id;
    string title;
    string author;
    string year;
    int totalCopies;
    int availableCopies;
    vector<string> borrowedBy;

    int getAvailableCopies() const
    {
        return totalCopies - borrowedBy.size();
    }

    bool isAvailable() const
    {
        return borrowedBy.size() < totalCopies;
    }
};

struct User
{
    string id;
    string name;
    string email;
    vector<string> borrowedBooks;
};

enum class MenuOption
{
    INIT=0,
    ADD_BOOK = 1,
    SEARCH_BOOK_BY_ID = 2,
    PRINT_WHO_BORROWED_BOOK_BY_NAME = 3,
    PRINT_LIBRARY_BY_ID = 4,
    PRINT_LIBRARY_BY_NAME = 5,
    ADD_USER = 6,
    USER_BORROW_BOOK = 7,
    USER_RETURN_BOOK = 8,
    PRINT_USERS = 9,
    Exit = 10
};
#endif