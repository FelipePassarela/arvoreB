cmake_minimum_required(VERSION 3.29)
project(arvoreB C)

set(CMAKE_C_STANDARD 11)

add_executable(arvoreB src/main.c
        src/BTree.c
        include/BTree.h
        src/BTreeNode.c
        include/BTreeNode.h)
