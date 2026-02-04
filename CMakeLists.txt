cmake_minimum_required(VERSION 4.0)

project(examiner)


# External package definitions

find_package(SQLite3 REQUIRED)

find_package(wxWidgets REQUIRED COMPONENTS core base gl)
include(${wxWidgets_USE_FILE})

find_package(fmt REQUIRED)


# Project subdirectories

add_subdirectory(examiner)

add_subdirectory(db)

add_subdirectory(ui)

add_subdirectory(core)

