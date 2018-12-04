# CR registry module

## Introduction
This repository is a registry module project from Corerain. The structure of the procture is shown below.
```
.
├── config
|   └── <binary files or parameters for configuration>
├── script
|   └── <cusomized scripts>
├── log
|   └── <log file of profram>
├── inc
|   └── <header files>
├── src
|   └── <source codes>
├── test
|   ├── CMakeLists.txt
|   └── <surce codes of test case and use case>
├── CMakeLists.txt
├── .gitignore
└── README.md
```
Directories [inc](./inc) is used to store header files of the project.

Directories [src](./src) is used to source codes of the project.

Directory [test](./test) is used to store the test cases and use cases of the project.

## Functions
Two utility apps are included in this project.

1. [img_cap_tc.cpp](./test/img_cap_tc.cpp) - Use front camera of a pc to shoot 5 photos for a person and register his/her information.
Photos and info are stored locally in a directory assigned by user.
Structure of the data is described as below.
```
.(root path assigned by user, when starting the app)
├── <sub path of a person>
|   ├── info.txt
|   ├── img_0.jpg
|   ├── img_1.jpg
|   ├── img_2.jpg
|   ├── img_3.jpg
|   └── img_4.jpg
├── <sub path of another person>
|...
```

2. [reg_tc.cpp](./test/reg_tc.cpp) - Upload persons info in a directory (whose structure is defined as in 1) to a MySQL table (pre-built) whose structure is:
```
+---------------+--------------+------+-----+---------+----------------+
| Field         | Type         | Null | Key | Default | Extra          |
+---------------+--------------+------+-----+---------+----------------+
| id_ppl        | int(11)      | NO   | PRI | NULL    | auto_increment |
| reg_time      | datetime     | YES  |     | NULL    |                |
| name          | varchar(20)  | YES  |     | NULL    |                |
| gender        | varchar(5)   | YES  |     | NULL    |                |
| date_of_birth | date         | YES  |     | NULL    |                |
| id_num        | varchar(18)  | YES  |     | NULL    |                |
| img_path_1    | varchar(260) | YES  |     | NULL    |                |
| img_path_2    | varchar(260) | YES  |     | NULL    |                |
| img_path_3    | varchar(260) | YES  |     | NULL    |                |
| img_path_4    | varchar(260) | YES  |     | NULL    |                |
| img_path_5    | varchar(260) | YES  |     | NULL    |                |
+---------------+--------------+------+-----+---------+----------------+
```

## Compile
```
cd <root of the project>
mkdir build
cmake ..
make
```

## Usage
1. Raw info collection:
```
./bin/img_cap_tc <registry folder root>
```
2. Upload to MySQL:
```
./bin/reg_tc <registry folder root> <my sql server IP> <my sql account> <my sql password> <my sql database> <my sql table>
```
