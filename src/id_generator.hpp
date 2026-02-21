#ifndef ID_GENERATOR_HPP
#define ID_GENERATOR_HPP
#include <string>
#include <sstream>
#include <iomanip>
class IDGenerator {
public:
    // Generate book ID: B-001, B-002, etc.
    static string generateBookID(int id) {
        ostringstream oss;
        oss << "B-" << setfill('0') << setw(3) << id;
        return oss.str();
    }
    
    // Generate user ID: U-001, U-002, etc.
    static string generateUserID(int id) {
        ostringstream oss;
        oss << "U-" << setfill('0') << setw(3) << id;
        return oss.str();
    }
    
    // Extract integer from book ID: "B-005" -> 5
    static int extractBookID(const string& bookID) {
        // Remove "B-" prefix and convert to int
        return stoi(bookID.substr(2));
    }
    
    // Extract integer from user ID: "U-010" -> 10
    static int extractUserID(const string& userID) {
        // Remove "U-" prefix and convert to int
        return stoi(userID.substr(2));
    }
};
#endif