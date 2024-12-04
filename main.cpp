#include <iostream>
#include <ostream>
#include <vector>
#include <fstream>
using namespace std;

struct Book
{
    int id;
    string title;
    string author;
    int year;

    void display() const
    {
        cout << "ID: " << id << ", Title: " << title << ", Author: " << author << ", Year: " << year << endl;
    }
};

class Library
{
private:
    vector<Book> books;
    const string FILENAME = "library_data.txt";

    void saveToFile()
    {
        ofstream file(FILENAME);
        for (const auto &book : books)
        {
            file << book.id << "|" << book.title << "|" << book.author << "|" << book.year << "\n";
        }
        file.close();
    }

    void loadFromFile()
    {
        ifstream file(FILENAME);
        if (file.is_open())
        {
            Book book;
            string line;
            while (getline(file, line))
            {
                size_t pos1 = line.find("|");
                size_t pos2 = line.find("|", pos1 + 1);
                size_t pos3 = line.find("|", pos2 + 1);

                book.id = stoi(line.substr(0, pos1));
                book.title = line.substr(pos1 + 1, pos2 - pos1 - 1);
                book.author = line.substr(pos2 + 1, pos3 - pos2 - 1);
                book.year = stoi(line.substr(pos3 + 1));

                books.push_back(book);
            }
            file.close();
        }
    }

public:
    Library() { loadFromFile(); }

    void addBook()
    {
        Book book;
        cout << "Enter Book ID: ";
        cin >> book.id;
        cin.ignore();
        cout << "Enter Title: ";
        getline(cin, book.title);
        cout << "Enter Author: ";
        getline(cin, book.author);
        cout << "Enter Year: ";
        cin >> book.year;
        books.push_back(book);
        saveToFile();
        cout << "Book added successfully!" << endl;
    }

    void searchBook()
    {
        string keyword;
        cout << "Enter Title or Author to search: ";
        cin.ignore();
        getline(cin, keyword);

        for (const auto &book : books)
        {
            if (book.title.find(keyword) != string::npos || book.author.find(keyword) != string::npos)
                book.display();
        }
    }

    void displayBooks()
    {
        if (books.empty())
        {
            cout << "No books in the library!" << endl;
            return;
        }
        for (const auto &book : books)
        {
            book.display();
        }
    }

    void deleteBook()
    {
        int id;
        cout << "Enter Book ID to delete: ";
        cin >> id;
        for (auto it = books.begin(); it != books.end(); ++it)
        {
            if (it->id == id)
            {
                books.erase(it);
                saveToFile();
                cout << "Book deleted successfully." << endl;
                return;
            }
        }
        cout << "Book not found!" << endl;
    }
};

int main()
{
    Library library;
    int choice;

    do
    {
        cout << "\n Library Management System \n";
        cout << "1. Add Book\n2. Search Book\n3. Display Books\n4. Delete Book\n5. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice)
        {
        case 1:
            library.addBook();
            break;
        case 2:
            library.searchBook();
            break;
        case 3:
            library.displayBooks();
            break;
        case 4:
            library.deleteBook();
            break;
        case 5:
            cout << "Existing...\n";
            break;
        default:
            cout << "Invalid choice. Try again.\n";
        }
    } while (choice != 5);

    return 0;
}