#ifndef JSON_HANDLER_HPP
#define JSON_HANDLER_HPP
#include <nlohmann/json.hpp>
#include "types.hpp"
using json = nlohmann::json;
void userTo_json(json &j, const User &u);
void usersToJson(json &j, const vector<User> &users);
void jsonToUsers(const json &j, vector<User> &users);
void jsonToUser(const json &j, User &u);
void bookTo_json(json &j, const Book &b);
void booksToJson(json &j, const vector<Book> &books);
void jsonToBooks(const json &j, vector<Book> &books);
void jsonToBook(const json &j, Book &b);

#endif