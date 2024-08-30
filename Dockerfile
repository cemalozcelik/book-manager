# Base image
FROM ubuntu:latest

# Update package list and install necessary tools
RUN apt-get update && \
    apt-get install -y \
    sqlite3 \
    libsqlite3-dev \
    g++

# Set working directory inside the container
WORKDIR /app

# Copy source code into the container
COPY main.cpp BookManager.cpp BookManager.h CMakeLists.txt ./

# Compile the C++ code and create the executable
RUN g++ main.cpp BookManager.cpp -o BookManagerApp -lsqlite3

# Command to run the application
CMD ["./BookManagerApp"]
