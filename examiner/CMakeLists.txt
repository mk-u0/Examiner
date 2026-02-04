set(LIBS
    core
    dbio
    ui
    ${wxWidgets_LIBRARIES}
)


add_executable(student WIN32)
target_sources(student
    PRIVATE
    student.cpp
)

target_link_libraries(student
    PRIVATE
    ${LIBS}
)


add_executable(admin WIN32)
target_sources(admin
    PRIVATE
    admin.cpp
)

target_link_libraries(admin
    PRIVATE
    ${LIBS}
)


# add_library(examiner)
# target_sources(examiner
#     PRIVATE
#     # insert implementation files (.cpp) under this comment
#     PUBLIC
#     FILE_SET examiner_headers
#     TYPE HEADERS
#     BASE_DIRS
#         .
#     FILES
#     # insert header files under this comment
# )
