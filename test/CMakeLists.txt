
INCLUDE_DIRECTORIES(${PROJECT_SOURCE_DIR}/src)

ADD_EXECUTABLE(test_colour EXCLUDE_FROM_ALL test_colour.cpp)
TARGET_LINK_LIBRARIES(test_colour svg)
ADD_TEST(test_colour "${MAKE_CURRENT_BINARY_DIR}/test_colour")
ADD_DEPENDENCIES(check test_colour)

ADD_EXECUTABLE(test_path EXCLUDE_FROM_ALL test_path.cpp)
TARGET_LINK_LIBRARIES(test_path svg)
ADD_TEST(test_path "${MAKE_CURRENT_BINARY_DIR}/test_path")
ADD_DEPENDENCIES(check test_path)
