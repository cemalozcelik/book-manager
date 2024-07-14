# Book Manager Application

This application allows users to manage a collection of books using a C++ program. Users can add, remove, and list books in the collection.

## Features

- **Add Book**: Users can add a new book to the collection by providing the title, author, and ISBN.
- **Remove Book**: Users can remove a book from the collection by its ISBN.
- **List Books**: Users can view a list of all books currently in the collection.

## Requirements

- C++ compiler
- SQLite library (`sqlite3`)
- C++ Standard Library (`iostream`, `string`, `limits`)

## Installation

1. **SQLite Installation**

    Install SQLite on your system. On Ubuntu, you can use the following commands:

    ```
    sudo apt-get update
    sudo apt-get install sqlite3 libsqlite3-dev
    ```

2. **Compilation and Execution**

    If you have CMake installed, you can use it to build and run the application. Here are the steps:

    1. Create a build directory inside the project directory:
    
        ```
        mkdir build
        cd build
        ```

    2. Generate the build files using CMake:
    
        ```
        cmake ..
        ```

    3. Build the application:
    
        ```
        cmake --build .
        ```

    4. Run the compiled executable:
    
        ```
        ./BookManagerApp
        ```

    If you prefer to compile manually, you can use the following commands:

    ```
    g++ main.cpp BookManager.cpp -o BookManagerApp -lsqlite3
    ```

    Run the compiled executable:

    ```
    ./BookManagerApp
    ```

3. **Usage**

    - When the application starts, choose an option from the menu.
    - Follow the prompts for each option and enter the required information.


## Example Usage of std::numeric_limits

The `std::numeric_limits` library is used in this application to clear the input buffer after reading numeric input. This prevents issues where newline characters (`\n`) in the input buffer interfere with subsequent input operations.

Example:

```cpp
#include <iostream>
#include <limits>

int main() {
  int choice;
  std::cout << "Enter your choice: ";
  std::cin >> choice;
  std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
  std::cin.clear();
  // Use 'choice' variable
  return 0;
}
```

