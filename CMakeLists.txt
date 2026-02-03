cmake_minimum_required(VERSION 4.0)

project(examiner)

find_package(SQLite3 REQUIRED)

find_package(wxWidgets REQUIRED COMPONENTS core base gl)
include(${wxWidgets_USE_FILE})

add_subdirectory(examiner)

add_subdirectory(db)
