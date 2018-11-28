# Corerain-C-CXX-Template

## Introduction

This repository is a basic template for a Qt5 project for a customized camera system. The core structure of the project is as below:

```
.
├── config
|   └── <binary files or parameters for configuration>
├── script
|   └── <cusomized scripts>
├── log
|   └── <log file of profram>
├── inc
|   ├── engine
|   |   └── <header files of engine>
|   ├── parser
|   |   └── <header files of parser>
|   └── utility
|       └── <header files of utility>
├── src
|   ├── engine
|   |   └── <source codes of engine>
|   ├── parser
|   |   └── <source codes of parser>
|   └── utility
|       └── <source codes of utility>
├── test
|   ├── CMakeLists.txt
|   └── <surce codes of test case and use case>
├── CMakeLists.txt
├── .gitignore
└── README.md
```
Directories [inc](./inc) and [src](./src) both have 3 subtirectories:
1. engine
2. parser
3. utility

These subdirectories are used to store header files and source codes for different purposes.

Directories [test](./test) is used to store the test cases and use cases of the project.
