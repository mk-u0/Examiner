add_library(ui)
target_sources(ui
    PRIVATE
    # insert implementation files (.cpp) under this comment
    login.cpp
    PUBLIC
    FILE_SET ui_headers
    TYPE HEADERS
    BASE_DIRS
        .
    FILES
    # insert header files under this comment
    login.h
)

target_link_libraries(ui
    PRIVATE
    ${wxWidgets_LIBRARIES}
)
