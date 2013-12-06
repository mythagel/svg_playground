
INCLUDE_DIRECTORIES(${PROJECT_SOURCE_DIR}/src)

ADD_EXECUTABLE(test_colour EXCLUDE_FROM_ALL test_colour.cpp)
TARGET_LINK_LIBRARIES(test_colour svg)
ADD_TEST(test_colour "${MAKE_CURRENT_BINARY_DIR}/test_colour")
ADD_DEPENDENCIES(check test_colour)

ADD_EXECUTABLE(test_path EXCLUDE_FROM_ALL test_path.cpp)
TARGET_LINK_LIBRARIES(test_path svg)
ADD_TEST(test_path "${MAKE_CURRENT_BINARY_DIR}/test_path")
ADD_DEPENDENCIES(check test_path)

ADD_EXECUTABLE(test_document EXCLUDE_FROM_ALL test_document.cpp)
TARGET_LINK_LIBRARIES(test_document svg)
ADD_TEST(test_document "${MAKE_CURRENT_BINARY_DIR}/test_document")
ADD_DEPENDENCIES(check test_document)
