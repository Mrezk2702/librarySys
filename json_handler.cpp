#include "json_handler.hpp"


void userTo_json(json &j, const User &u)
{
    j = json{{"id", u.id},
             {"name", u.name},
             {"email", u.email},
             {"borrowedBooks", u.borrowedBooks}};
}
void usersToJson(json &j, const vector<User> &users)
{
    j = json::array();
    for (const auto &user : users)
    {
        json jUser;
        userTo_json(jUser, user);
        j.push_back(jUser);
    }
}

void jsonToUser(const json &j,User &u)
{
    u.id= j["id"];
    u.name =j["name"];
    u.email = j["email"];
    u.borrowedBooks.clear();
    for(const auto &borrowedBook : j["borrowedBooks"])
    {
        u.borrowedBooks.push_back(borrowedBook);
    }
}

void jsonToUsers(const json &j, vector<User> &users)
{
    users.clear();
    for(const auto &jUser : j)
    {
        User user;
        jsonToUser(jUser,user);
        users.push_back(user);
    }
}



void bookTo_json(json &j, const Book &b)
{
    j = json{{"id", b.id},
             {"title", b.title},
             {"author", b.author},
             {"year", b.year},
             {"totalCopies", b.totalCopies},
             {"availableCopies", b.getAvailableCopies()},
             {"borrowedBy", b.borrowedBy}};
}

void booksToJson(json &j, const vector<Book> &books)
{
    j = json::array();
    for (const auto &book : books)
    {
        json jBook;
        bookTo_json(jBook, book);
        j.push_back(jBook);
    }
}

void jsonToBook(const json &j, Book &b)
{
    b.id = j["id"];
    b.title = j["title"];
    b.author = j["author"];
    b.year = j["year"];
    b.totalCopies = j["totalCopies"];
    b.availableCopies = j["availableCopies"];
    b.borrowedBy.clear();
    for (const auto &borrower : j["borrowedBy"])
    {
        b.borrowedBy.push_back(borrower);
    }
}

void jsonToBooks(const json &j, vector<Book> &books)
{
    books.clear();
    for (const auto &jBook : j)
    {
        Book book;
        jsonToBook(jBook, book);
        books.push_back(book);
    }
}