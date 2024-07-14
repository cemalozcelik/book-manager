#include <iostream>
#include <limits> // For std::numeric_limits
#include <cctype> // For std::toupper
#include "BookManager.h"

void clearInputBuffer()
{
    std::cin.clear();
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}

std::string toTitleCase(const std::string &str)
{
    bool makeUpper = true; // Flag to track if the next character should be upper case
    std::string result;

    for (char c : str)
    {
        if (std::isspace(c))
        {
            makeUpper = true; // Next character should be upper case if it's a space
            result += c;
        }
        else if (makeUpper)
        {
            result += std::toupper(c);
            makeUpper = false;
        }
        else
        {
            result += std::tolower(c);
        }
    }

    return result;
}

int main()
{
    BookManager bookManager("bookstore.db");

    std::cout << "Table created successfully" << std::endl;
    std::cout << "Welcome to the Book Manager" << std::endl;

    int choice = 0;
    while (choice != 5)
    {
        std::cout << "1. Add book" << std::endl;
        std::cout << "2. Remove book" << std::endl;
        std::cout << "3. Remove all books" << std::endl;
        std::cout << "4. Show all books" << std::endl;
        std::cout << "5. Exit" << std::endl;
        std::cout << "Enter your choice: ";

        std::cin >> choice;
        clearInputBuffer();

        switch (choice)
        {
        case 1:
        {
            std::string title, author, isbn;
            std::cout << "Enter the title: ";
            std::getline(std::cin, title);
            title = toTitleCase(title); // Convert to title case
            std::cout << "Enter the author: ";
            std::getline(std::cin, author);
            author = toTitleCase(author); // Convert to title case

            std::cout << "Enter the ISBN: ";
            std::getline(std::cin, isbn);
            bookManager.addBook(title, author, isbn);
            break;
        }
        case 2:
        {
            std::string isbn;
            std::cout << "Enter the ISBN of the book to remove: ";
            std::getline(std::cin, isbn);
            bookManager.removeBook(isbn);
            break;
        }
        case 3:
            bookManager.removeAllBooks();
            break;
        case 4:
            bookManager.listBooks();
            break;
        case 5:
            std::cout << "Goodbye!" << std::endl;
            break;
        default:
            std::cout << "Invalid choice. Please enter again." << std::endl;
            break;
        }
    }

    return 0;
}
