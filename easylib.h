#include <string>
#include <vector>

using namespace std;

// Book class
class Book {
public:
    string title;
    string author;
    string ISBN; // Store ISBN as string
    bool available;
};

// Member class
class Member {
public:
    string name;
    int memberID;
    vector<string> borrowedBooks; // Stores ISBNs of borrowed books as strings
};

// Library class
class Library {
private:
    vector<Book> books;
    vector<Member> members;

public:
    void addBook();
    void issueBook();
    void returnBook();
    void searchBooks();
    void displayAllBooks();
    void addMember();
    void displayAllMembers();
    void saveBooksToFile();
    void saveMembersToFile();
    void loadBooksFromFile();
    void loadMembersFromFile();
};