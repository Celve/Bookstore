cmake_minimum_required(VERSION 3.16)
project(Bookstore)

set(CMAKE_CXX_STANDARD 14)

add_executable(code src/File.h src/main.cpp src/BPlusTree.cpp src/Book.cpp src/User.cpp src/Bookstore.cpp src/Bookstore.h src/Utils.h src/Exception.h src/Log.cpp)
