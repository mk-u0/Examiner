add_library(dbio)
target_sources(dbio
    PRIVATE
    # insert implementation files (.cpp) under this comment
    dataio.cpp
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
    SQLite::SQLite3
)
