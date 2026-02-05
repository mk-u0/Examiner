add_library(dbio)
target_sources(dbio
    PRIVATE
    # insert implementation files (.cpp) under this comment
    dataio.cpp
    dataio_insert.cpp
    dataio_select.cpp
    PUBLIC
    FILE_SET dbio_headers
    TYPE HEADERS
    BASE_DIRS
        .
    FILES
    # insert header files under this comment
    dataio.h
)

target_link_libraries(dbio
    PRIVATE
    core
    SQLite::SQLite3
)
