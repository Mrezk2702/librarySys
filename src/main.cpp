#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <fstream>
#include <nlohmann/json.hpp>
#include "types.hpp"
#include "json_handler.hpp"
#include "librarySystem.hpp"
#include "id_generator.hpp"
using json = nlohmann::json;
using namespace std;





vector<Book> books;
vector<User> users;
int lastBookId = 0;
int lastUserId = 0;



int main()
{
    LibrarySystem library;
    library.run();
    return 0;

}