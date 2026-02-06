# Insertion tests
add_executable(test_insert)
target_sources(test_insert
    PRIVATE
    test_insert.cpp
)

target_link_libraries(test_insert
    PRIVATE
    dbio
    core
)

add_test(
    NAME insert_admin
    COMMAND test_insert admin
)

add_test(
    NAME insert_student
    COMMAND test_insert student
)
