cmake_minimum_required(VERSION 3.0)

project(my_project)

include_directories(${CMAKE_SOURCE_DIR}/inc/)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin/)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib/)

set(CMAKE_C_COMPILER g++)
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -std=c++11")
set(CMAKE_CXX_COMPILER g++)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
set(CMAKE_BUILD_TYPE Release)

#Find pre-installed package
find_package(OpenCV REQUIRED)

#Add external include directories
include_directories(
  /usr/include/
  /usr/local/include/
  ${OpenCV_INSTALL_PATH}/include/
  /usr/include/mysql/
  )

#Link external libraries diectories
link_directories(
  /usr/lib/
  /usr/local/lib/
  ${OpenCV_INSTALL_PATH}/lib/
  /usr/lib/x86_64-linux-gnu/
  )

#Link external libraries
set(EXTERNAL_LIBS
  pthread
  ${OpenCV_LIBS}
  mysqlclient
  )

#Add project source codes to project
set(SRC "" CACHE INTERNAL "")
file(GLOB SRC
  src/*.c src/*.cpp src/*.cc
  )

#Create project library
if(NOT "${SRC}" STREQUAL "")
  #Create the library
  message("[CORERAIN] Creating project library")
  add_library(${PROJECT_NAME} SHARED ${SRC})
  target_link_libraries(${PROJECT_NAME} ${EXTERNAL_LIBS})
elseif("${SRC}" STREQUAL "")
  message("[CORERAIN] No internal dependencies")
endif()

#Add sub-directories of the project
add_subdirectory(test/)
