#include <iostream>
#include <vector>
#include <string>
#include <fstream>

using namespace std;

// Book Class
class Book {
private:
    int id;
    string title;
    string author;
    int availableCopies;

public:
    Book(int id, string title, string author, int copies)
        : id(id), title(title), author(author), availableCopies(copies) {}

    int getId() const { return id; }
    string getTitle() const { return title; }
    string getAuthor() const { return author; }
    int getAvailableCopies() const { return availableCopies; }

    void borrowBook() {
        if (availableCopies > 0) availableCopies--;
    }

    void returnBook() {
        availableCopies++;
    }

    void display() const {
        cout << "Book ID: " << id << ", Title: " << title
             << ", Author: " << author << ", Available Copies: " << availableCopies << endl;
    }
};

// Member Class
class Member {
private:
    int id;
    string name;

public:
    Member(int id, string name) : id(id), name(name) {}

    int getId() const { return id; }
    string getName() const { return name; }

    void display() const {
        cout << "Member ID: " << id << ", Name: " << name << endl;
    }
};

// Library Class
class Library {
private:
    vector<Book> books;
    vector<Member> members;

public:
    // File Handling
    void loadBooksFromFile() {
        ifstream file("books.txt");
        if (file.is_open()) {
            books.clear();
            int id, copies;
            string title, author;
            while (file >> id >> ws && getline(file, title) && getline(file, author) && file >> copies) {
                books.emplace_back(id, title, author, copies);
            }
            file.close();
        }
    }

    void saveBooksToFile() {
        ofstream file("books.txt");
        if (file.is_open()) {
            for (auto &book : books) {
                file << book.getId() << "\n"
                     << book.getTitle() << "\n"
                     << book.getAuthor() << "\n"
                     << book.getAvailableCopies() << "\n";
            }
            file.close();
        }
    }

    void loadMembersFromFile() {
        ifstream file("members.txt");
        if (file.is_open()) {
            members.clear();
            int id;
            string name;
            while (file >> id >> ws && getline(file, name)) {
                members.emplace_back(id, name);
            }
            file.close();
        }
    }

    void saveMembersToFile() {
        ofstream file("members.txt");
        if (file.is_open()) {
            for (auto &member : members) {
                file << member.getId() << "\n" << member.getName() << "\n";
            }
            file.close();
        }
    }

    // Library Functions
    void addBook(int id, string title, string author, int copies) {
        books.emplace_back(id, title, author, copies);
        cout << "Book added successfully!" << endl;
    }

    void addMember(int id, string name) {
        members.emplace_back(id, name);
        cout << "Member added successfully!" << endl;
    }

    void displayBooks() {
        for (auto &book : books) {
            book.display();
        }
    }

    void displayMembers() {
        for (auto &member : members) {
            member.display();
        }
    }

    void searchBook(string keyword) {
        bool found = false;
        for (auto &book : books) {
            if (book.getTitle().find(keyword) != string::npos || book.getAuthor().find(keyword) != string::npos) {
                book.display();
                found = true;
            }
        }
        if (!found) cout << "No books found for the keyword: " << keyword << endl;
    }

    void searchMember(string keyword) {
        bool found = false;
        for (auto &member : members) {
            if (member.getName().find(keyword) != string::npos) {
                member.display();
                found = true;
            }
        }
        if (!found) cout << "No members found for the keyword: " << keyword << endl;
    }

    void borrowBook(int memberId, int bookId) {
        bool bookFound = false, memberFound = false;

        for (auto &book : books) {
            if (book.getId() == bookId) {
                bookFound = true;
                for (auto &member : members) {
                    if (member.getId() == memberId) {
                        memberFound = true;
                        if (book.getAvailableCopies() > 0) {
                            book.borrowBook();
                            cout << "Book borrowed successfully!" << endl;
                        } else {
                            cout << "Book is not available!" << endl;
                        }
                        break;
                    }
                }
                break;
            }
        }
        if (!bookFound) cout << "Book ID not found!" << endl;
        if (!memberFound) cout << "Member ID not found!" << endl;
    }

    void returnBook(int bookId) {
        for (auto &book : books) {
            if (book.getId() == bookId) {
                book.returnBook();
                cout << "Book returned successfully!" << endl;
                return;
            }
        }
        cout << "Book ID not found!" << endl;
    }
};

// Menu Display
void displayMenu() {
    cout << "\n=====================================" << endl;
    cout << "           Library System            " << endl;
    cout << "=====================================" << endl;
    cout << "1. Display Books" << endl;
    cout << "2. Display Members" << endl;
    cout << "3. Borrow Book" << endl;
    cout << "4. Return Book" << endl;
    cout << "5. Add Book" << endl;
    cout << "6. Add Member" << endl;
    cout << "7. Search Book" << endl;
    cout << "8. Search Member" << endl;
    cout << "9. Exit" << endl;
    cout << "=====================================" << endl;
    cout << "Enter your choice: ";
}

int main() {
    Library library;
    library.loadBooksFromFile();
    library.loadMembersFromFile();

    int choice;
    do {
        displayMenu();
        cin >> choice;
        switch (choice) {
            case 1:
                library.displayBooks();
                break;
            case 2:
                library.displayMembers();
                break;
            case 3: {
                int memberId, bookId;
                cout << "Enter Member ID: ";
                cin >> memberId;
                cout << "Enter Book ID: ";
                cin >> bookId;
                library.borrowBook(memberId, bookId);
                break;
            }
            case 4: {
                int bookId;
                cout << "Enter Book ID: ";
                cin >> bookId;
                library.returnBook(bookId);
                break;
            }
            case 5: {
                int id, copies;
                string title, author;
                cout << "Enter Book ID, Title, Author, and Copies: ";
                cin >> id >> ws;
                getline(cin, title);
                getline(cin, author);
                cin >> copies;
                library.addBook(id, title, author, copies);
                break;
            }
            case 6: {
                int id;
                string name;
                cout << "Enter Member ID and Name: ";
                cin >> id >> ws;
                getline(cin, name);
                library.addMember(id, name);
                break;
            }
            case 7: {
                string keyword;
                cout << "Enter Book Title/Author Keyword: ";
                cin.ignore();
                getline(cin, keyword);
                library.searchBook(keyword);
                break;
            }
            case 8: {
                string keyword;
                cout << "Enter Member Name Keyword: ";
                cin.ignore();
                getline(cin, keyword);
                library.searchMember(keyword);
                break;
            }
            case 9:
                library.saveBooksToFile();
                library.saveMembersToFile();
                cout << "Exiting... Goodbye!" << endl;
                break;
            default:
                cout << "Invalid choice! Please try again." << endl;
        }
    } while (choice != 9);

    return 0;
}
