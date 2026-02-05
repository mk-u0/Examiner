add_library(core)
target_sources(core
    PRIVATE
    # insert implementation files (.cpp) under this comment
    util.cpp
    user.cpp
    exam.cpp
    PUBLIC
    FILE_SET core_headers
    TYPE HEADERS
    BASE_DIRS
        .
    FILES
    # insert header files under this comment
    user.h
    util.h
    exam.h
)

target_link_libraries(core
    PRIVATE
    nlohmann_json::nlohmann_json
    ${OpenSSL_LIBRARIES}
)
