cmake_minimum_required(VERSION 3.10)

# set the project name
project(BookManager)

# Cpp standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# add the executable
set (SOURCES
    main.cpp
    BookManager.cpp
    )

#binary executable
add_executable(BookManager ${SOURCES})

# add sqlite3 library
find_package(SQLite3 REQUIRED)
target_link_libraries(BookManager SQLite::SQLite3)