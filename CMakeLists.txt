cmake_minimum_required(VERSION 4.0)

project(examiner)

set(CMAKE_CXX_STANDARD 11)

# External package definitions

find_package(SQLite3 REQUIRED)

find_package(wxWidgets REQUIRED COMPONENTS core base gl)
include(${wxWidgets_USE_FILE})

find_package(nlohmann_json REQUIRED)

find_package(OpenSSL REQUIRED)
find_package(nlohmann_json CONFIG REQUIRED)


# Project subdirectories

add_subdirectory(examiner)

add_subdirectory(db)

add_subdirectory(ui)

add_subdirectory(core)

