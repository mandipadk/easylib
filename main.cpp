#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>
#include "easylib.h"

using namespace std;

int main() {
    Library library;
    library.loadBooksFromFile(); // Load book data on startup
    library.loadMembersFromFile(); // Load member data on startup

    int choice;
    do {
// cout <<"  _____                         _       _   _      " << endl; 
// cout <<" | ____|   __ _   ___   _   _  | |     (_) | |__   " << endl;
// cout <<" |  _|    / _` | / __| | | | | | |     | | | '_ \  " << endl; 
// cout <<" | |___  | (_| | \__ \ | |_| | | |___  | | | |_) | " << endl; 
// cout <<" |_____|  \__,_| |___/  \__, | |_____| |_| |_.__/  " << endl;  
// cout <<"                       |___/                       " << endl; 
        cout << "\nEasyLib - A Library Management System" << endl;
        cout << "1. Add Book" << endl;
        cout << "2. Issue Book" << endl;
        cout << "3. Return Book" << endl;
        cout << "4. Search Books" << endl;
        cout << "5. Display All Books" << endl;
        cout << "6. Add Member" << endl;
        cout << "7. Display All Members" << endl;
        cout << "8. Save Data" << endl;
        cout << "0. Exit" << endl;
        cout << "\nEnter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1: library.addBook(); break;
            case 2: library.issueBook(); break;
            case 3: library.returnBook(); break;
            case 4: library.searchBooks(); break;
            case 5: library.displayAllBooks(); break;
            case 6: library.addMember(); break;
            case 7: library.displayAllMembers(); break;
            case 8: library.saveBooksToFile(); library.saveMembersToFile(); break;
            case 0: cout << "Exiting...\n"; break;
            default: cout << "Invalid choice!\n";
        }
    } while (choice != 0);

    return 0;
}

// Library member function definitions
void Library::addBook() {
    Book book;
    cout << "Enter Book Title: ";
    cin.ignore(); // Clear input buffer
    getline(cin, book.title);
    cout << "Enter Author: ";
    getline(cin, book.author);
    cout << "Enter ISBN: ";
    cin >> book.ISBN;
    book.available = true;
    books.push_back(book);
    cout << "Book added successfully!\n";
}

void Library::issueBook() {
    string ISBN;
    int memberID;
    bool foundBook = false;

    cout << "\nEnter ISBN of the book to issue: ";
    cin >> ISBN;

    // Find the book by ISBN
    for (size_t i = 0; i < books.size(); ++i) {
        if (books[i].ISBN == ISBN && books[i].available) {
            foundBook = true;

            cout << "Enter Member ID: ";
            cin >> memberID;

            // Find the member by ID and add borrowed book ISBN
            for (size_t j = 0; j < members.size(); ++j) {
                if (members[j].memberID == memberID) {
                    members[j].borrowedBooks.push_back(ISBN);
                    books[i].available = false;  // Mark book as issued
                    cout << "Book issued successfully to " << members[j].name << "." << endl;
                    return;
                }
            }
            cout << "Invalid Member ID!\n";
            books[i].available = true; // Revert availability change
            return;
        }
    }

    if (!foundBook) {
        cout << "Book not found or unavailable!\n";
    }
}

void Library::returnBook() {
    string ISBN;
    int memberID;
    bool foundBook = false;

    cout << "Enter ISBN of the book to return: ";
    cin >> ISBN;

    // Find the book by ISBN
    for (size_t i = 0; i < books.size(); ++i) {
        if (books[i].ISBN == ISBN) {
            foundBook = true;
            books[i].available = true;   // Mark book as available

            cout << "Enter Member ID: ";
            cin >> memberID;

            // Find the member by ID and remove borrowed book ISBN
            for (size_t j = 0; j < members.size(); ++j) {
                if (members[j].memberID == memberID) {
                    vector<string>::iterator it = find(members[j].borrowedBooks.begin(), members[j].borrowedBooks.end(), ISBN);
                    if (it != members[j].borrowedBooks.end()) {
                        members[j].borrowedBooks.erase(it);
                        cout << "Book returned successfully!\n";
                        return;
                    } else {
                        cout << "Member has not borrowed this book!\n";
                        return;
                    }
                }
            }
        }
    }

    if (!foundBook) {
        cout << "Book not found!\n";
    }
}

void Library::searchBooks() {
    string searchTerm;
    int choice;

    cout << "Search by:\n";
    cout << "1. Title\n";
    cout << "2. Author\n";
    cout << "3. ISBN\n";
    cout << "Enter your choice: ";
    cin >> choice;
    if (choice > 3 || choice < 1){
        cout << "Invalid Choice. Please try again." << endl;
    }
    else{
    cin.ignore(); // Clear input buffer
    cout << "Enter search term: ";
    getline(cin, searchTerm);

    bool found = false;
    switch (choice) {
        case 1: // Search by Title
            for (size_t i = 0; i < books.size(); ++i) {
                const Book& book = books[i];
                if (book.title.find(searchTerm) != string::npos) {
                    cout << "\n----------------------------" << endl;
                    cout << "Title: " << book.title << endl;
                    cout << "Author: " << book.author << endl;
                    cout << "ISBN: " << book.ISBN << endl;
                    cout << "Available: " << (book.available ? "Yes" : "No") << endl;
                    cout << "----------------------------" << endl;
                    found = true;
                }
            }
            break;
        case 2: // Search by Author
            for (size_t i = 0; i < books.size(); ++i) {
                const Book& book = books[i];
                if (book.author.find(searchTerm) != string::npos) {
                    cout << "\n----------------------------" << endl;
                    cout << "Title: " << book.title << endl;
                    cout << "Author: " << book.author << endl;
                    cout << "ISBN: " << book.ISBN << endl;
                    cout << "Available: " << (book.available ? "Yes" : "No") << endl;
                    cout << "----------------------------" << endl;
                    found = true;
                }
            }
            break;
        case 3: // Search by ISBN
            for (size_t i = 0; i < books.size(); ++i) {
                const Book& book = books[i];
                if (book.ISBN == searchTerm) {
                    cout << "\n----------------------------" << endl;
                    cout << "Title: " << book.title << endl;
                    cout << "Author: " << book.author << endl;
                    cout << "ISBN: " << book.ISBN << endl;
                    cout << "Available: " << (book.available ? "Yes" : "No") << endl;
                    cout << "----------------------------" << endl;
                    found = true;
                }
            }
            break;
        default:
            cout << "Invalid choice!\n";
    }
    if (!found) {
        cout << "No matching books found.\n";
    }
    }
}

void Library::displayAllBooks() {
    if (books.empty()){
        cout << "No books in the library.\n";
    return;
    }
    cout << "\n------------------------" << endl;
    cout << "All Books in the library:" << endl;
    cout << "------------------------" << endl;
    for (size_t i = 0; i < books.size(); ++i) {
        const Book& book = books[i];
        cout << "Title: " << book.title << endl;
        cout << "Author: " << book.author << endl;
        cout << "ISBN: " << book.ISBN << endl;
        cout << "Available: " << (book.available ? "Yes" : "No") << endl;
        cout << "----------------------------" << endl;
    }
}

void Library::addMember() {
    Member member;
    cout << "Enter Member Name: ";
    cin.ignore();
    getline(cin, member.name);
    cout << "Enter Member ID: ";
    cin >> member.memberID;
    members.push_back(member);
    cout << "Member added successfully!\n";
}

void Library::displayAllMembers() {
    if (members.empty()) {
        cout << "No members in the library.\n";
    } else {
        cout << "\nAll Members:\n";
        for (size_t i = 0; i < members.size(); ++i) {
            cout << "Name: " << members[i].name << endl;
            cout << "Member ID: " << members[i].memberID << endl;
            cout << "----------------------------" << endl;
        }
    }
}

// Member functions to save data to files
void Library::saveBooksToFile() {
    ofstream file("books_data.txt");
    if (file.is_open()) {
        for (size_t i = 0; i < books.size(); ++i) {
            file << books[i].title << "," << books[i].author << "," << books[i].ISBN << "," << books[i].available << endl;
        }
        file.close();
        cout << "Book data saved successfully!\n";
    } else {
        cout << "Failed to open book data file!\n";
    }
}

void Library::saveMembersToFile() {
    ofstream file("members_data.txt");
    if (file.is_open()) {
        for (size_t i = 0; i < members.size(); ++i) {
            file << members[i].name << "," << members[i].memberID;
            for (size_t j = 0; j < members[i].borrowedBooks.size(); ++j) {
                file << "," << members[i].borrowedBooks[j];
            }
            file << endl;
        }
        file.close();
        cout << "Member data saved successfully!\n";
    } else {
        cout << "Failed to open member data file!\n";
    }
}

// Member functions to load data from files
void Library::loadBooksFromFile() {
    ifstream file("books_data.txt");
    if (file.is_open()) {
        string line;
        while (getline(file, line)) {
            vector<string> data;
            string token;
            size_t pos = 0;
            // Split the line (comma-separated data) into tokens
            while ((pos = line.find(",")) != string::npos) {
                token = line.substr(0, pos);
                data.push_back(token);
                line.erase(0, pos + 1);
        }
        data.push_back(line); // Add the last token

        Book book;
        book.title = data[0];
        book.author = data[1];
        book.ISBN = data[2]; // Store ISBN as string
        book.available = (data[3] == "1") ? true : false;
        books.push_back(book);
    }
    file.close();
    cout << "-------------------------------------" << endl;
    cout << "Book data loaded successfully!\n";
    } else {
    cout << "No book data found.\n";
    }
}

void Library::loadMembersFromFile() {
    ifstream file("members_data.txt");
    if (file.is_open()) {
        string line;
        while (getline(file, line)) {
            vector<string> data;
            string token;
            size_t pos = 0;
            // Split the line (comma-separated data) into tokens
            while ((pos = line.find(",")) != string::npos) {
                token = line.substr(0, pos);
                data.push_back(token);
                line.erase(0, pos + 1);
            }
            data.push_back(line); // Add the last token

            Member member;
            member.name = data[0];
            member.memberID = stoi(data[1]);

            for (size_t i = 2; i < data.size(); ++i) {
                member.borrowedBooks.push_back(data[i]);
            }
            members.push_back(member);
        }
        file.close();
        cout << "Member data loaded successfully!\n";
        cout << "-------------------------------------" << endl;
    } else {
        cout << "No member data found.\n";
    }
}