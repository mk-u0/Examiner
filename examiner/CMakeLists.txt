add_executable(student WIN32)
target_sources(student
    PRIVATE
    student.cpp
)

target_link_libraries(student
    PRIVATE
    ecore
    dbio
    ${wxWidgets_LIBRARIES}
)


add_executable(admin WIN32)
target_sources(admin
    PRIVATE
    admin.cpp
)

target_link_libraries(admin
    PRIVATE
    ecore
    dbio
    ${wxWidgets_LIBRARIES}
)


add_library(ecore)
target_sources(ecore
    PRIVATE
    # insert implementation files (.cpp) under this comment
    util.cpp
    user.cpp
    exam.cpp
    PUBLIC
    FILE_SET ecore_headers
    TYPE HEADERS
    BASE_DIRS
        .
    FILES
    # insert header files under this comment
    user.h
    util.h
    exam.h
)
