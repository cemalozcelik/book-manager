#include "BookManager.h"
#include <iostream>

BookManager::BookManager(const std::string &db_name)
{
    int rc = sqlite3_open(db_name.c_str(), &db);
    if (rc)
    {
        std::cerr << "Can't open database: " << sqlite3_errmsg(db) << std::endl;
        return;
    }
    createTable();
}

BookManager::~BookManager()
{
    sqlite3_close(db);
}



void BookManager::createTable()
{
    std::string sql = "CREATE TABLE IF NOT EXISTS BOOKS ("
                      "TITLE TEXT NOT NULL, "
                      "AUTHOR TEXT NOT NULL, "
                      "ISBN TEXT PRIMARY KEY NOT NULL);";
    char *errMsg = 0;
    int rc = sqlite3_exec(db, sql.c_str(), 0, 0, &errMsg);
    if (rc != SQLITE_OK)
    {
        std::cerr << "SQL error: " << errMsg << std::endl;
        sqlite3_free(errMsg);
    }
}

void BookManager::addBook(const std::string &title, const std::string &author, const std::string &isbn)
{

    if (isbn.empty() || title.empty() || author.empty())
    {
        std::cerr << "Error: ISBN, Title or Author cannot be empty." << std::endl;
        return;
    }

    if (isISBNExists(isbn))
    {
        std::cerr << "Error: ISBN " << isbn << " already exists in the database." << std::endl;
        return;
    }

    std::string sql = "INSERT INTO BOOKS (TITLE, AUTHOR, ISBN) VALUES (?, ?, ?);";
    sqlite3_stmt *stmt;
    int rc = sqlite3_prepare_v2(db, sql.c_str(), -1, &stmt, 0);
    if (rc == SQLITE_OK)
    {
        sqlite3_bind_text(stmt, 1, title.c_str(), -1, SQLITE_STATIC);
        sqlite3_bind_text(stmt, 2, author.c_str(), -1, SQLITE_STATIC);
        sqlite3_bind_text(stmt, 3, isbn.c_str(), -1, SQLITE_STATIC);
        sqlite3_step(stmt);
        sqlite3_finalize(stmt);
        std::cout << "Book added successfully" << std::endl;
    }
    else
    {
        std::cerr << "Failed to add book: " << sqlite3_errmsg(db) << std::endl;
    }
}

void BookManager::removeBook(const std::string &isbn)
{
    std::string sql = "DELETE FROM BOOKS WHERE ISBN = ?;";
    sqlite3_stmt *stmt;
    int rc = sqlite3_prepare_v2(db, sql.c_str(), -1, &stmt, 0);
    if (rc == SQLITE_OK)
    {
        sqlite3_bind_text(stmt, 1, isbn.c_str(), -1, SQLITE_STATIC);
        sqlite3_step(stmt);
        sqlite3_finalize(stmt);
        std::cout << "Book removed successfully" << std::endl;
    }
    else
    {
        std::cerr << "Failed to remove book: " << sqlite3_errmsg(db) << std::endl;
    }
}

void BookManager::listBooks() const
{
    std::string sql = "SELECT * FROM BOOKS;";
    sqlite3_stmt *stmt;
    int rc = sqlite3_prepare_v2(db, sql.c_str(), -1, &stmt, 0);

    if (rc == SQLITE_OK)
    {
        bool isEmpty = true;
        while (sqlite3_step(stmt) == SQLITE_ROW)
        {
            isEmpty = false;
            std::string title = reinterpret_cast<const char *>(sqlite3_column_text(stmt, 0));
            std::string author = reinterpret_cast<const char *>(sqlite3_column_text(stmt, 1));
            std::string isbn = reinterpret_cast<const char *>(sqlite3_column_text(stmt, 2));
            std::cout << "Title: " << title << "\nAuthor: " << author << "\nISBN: " << isbn << std::endl;
            std::cout << "-------------------" << std::endl;
        }
        sqlite3_finalize(stmt);

        if (isEmpty)
        {
            std::cout << "No books found in the database." << std::endl;
        }
    }
    else
    {
        std::cerr << "Failed to list books: " << sqlite3_errmsg(db) << std::endl;
    }
}

bool BookManager::isISBNExists(const std::string &isbn) const
{
    std::string sql = "SELECT COUNT(*) FROM BOOKS WHERE ISBN = ?;";
    sqlite3_stmt *stmt;
    int rc = sqlite3_prepare_v2(db, sql.c_str(), -1, &stmt, 0);
    if (rc == SQLITE_OK)
    {
        sqlite3_bind_text(stmt, 1, isbn.c_str(), -1, SQLITE_STATIC);
        if (sqlite3_step(stmt) == SQLITE_ROW)
        {
            int count = sqlite3_column_int(stmt, 0);
            sqlite3_finalize(stmt);
            return (count > 0);
        }
        sqlite3_finalize(stmt);
    }
    else
    {
        std::cerr << "Failed to check ISBN: " << sqlite3_errmsg(db) << std::endl;
    }
    return false;
}

void BookManager::removeAllBooks() {
    char confirmation;
    std::cout << "Are you sure you want to remove all books? This action cannot be undone. (y/n): ";
    std::cin >> confirmation;

    if (confirmation == 'y' || confirmation == 'Y') {
        std::string sql = "DELETE FROM BOOKS;";
        char* errMsg = 0;
        int rc = sqlite3_exec(db, sql.c_str(), 0, 0, &errMsg);
        if (rc != SQLITE_OK) {
            std::cerr << "SQL error: " << errMsg << std::endl;
            sqlite3_free(errMsg);
        } else {
            std::cout << "All books removed successfully" << std::endl;
        }
    } else {
        std::cout << "Operation canceled. No books were removed." << std::endl;
    }
}
