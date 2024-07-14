#ifndef BOOKMANAGER_H
#define BOOKMANAGER_H

#include <string>
#include <sqlite3.h>

class BookManager {
public:
    BookManager(const std::string& db_name);
    ~BookManager();

    void addBook(const std::string& title, const std::string& author, const std::string& isbn);
    void removeBook(const std::string& isbn);
    void listBooks() const;
    bool isISBNExists(const std::string& isbn) const;
    void removeAllBooks();

private:
    sqlite3* db;

    void createTable();
};

#endif // BOOKMANAGER_H
