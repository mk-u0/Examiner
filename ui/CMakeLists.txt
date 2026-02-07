add_library(ui)

target_sources(ui
    PRIVATE
    login.cpp
    adminui.cpp
    studentui.cpp
    PUBLIC
    FILE_SET ui_headers
    TYPE HEADERS
    BASE_DIRS
        .
    FILES
    login.h
    adminui.h
    studentui.h
)

target_link_libraries(ui
    PRIVATE
    core
    ${wxWidgets_LIBRARIES}
)
