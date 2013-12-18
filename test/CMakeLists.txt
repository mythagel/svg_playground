
INCLUDE_DIRECTORIES(${PROJECT_SOURCE_DIR}/src ${PROJECT_SOURCE_DIR}/src/dom/include/ ${PROJECT_SOURCE_DIR}/deps/uri/src)

ADD_EXECUTABLE(test_colour EXCLUDE_FROM_ALL test_colour.cpp)
TARGET_LINK_LIBRARIES(test_colour svg)
ADD_TEST(test_colour "${MAKE_CURRENT_BINARY_DIR}/test_colour")
ADD_DEPENDENCIES(check test_colour)

ADD_EXECUTABLE(test_path EXCLUDE_FROM_ALL test_path.cpp)
TARGET_LINK_LIBRARIES(test_path svg)
ADD_TEST(test_path "${MAKE_CURRENT_BINARY_DIR}/test_path")
ADD_DEPENDENCIES(check test_path)

ADD_EXECUTABLE(test_transform EXCLUDE_FROM_ALL test_transform.cpp)
TARGET_LINK_LIBRARIES(test_transform svg)
ADD_TEST(test_transform "${MAKE_CURRENT_BINARY_DIR}/test_transform")
ADD_DEPENDENCIES(check test_transform)

ADD_EXECUTABLE(test_document EXCLUDE_FROM_ALL test_document.cpp)
TARGET_LINK_LIBRARIES(test_document svg)
ADD_TEST(test_document "${MAKE_CURRENT_BINARY_DIR}/test_document")
ADD_DEPENDENCIES(check test_document)

ADD_EXECUTABLE(test_expat  test_expat.cpp)
TARGET_LINK_LIBRARIES(test_expat svg expat)
ADD_TEST(test_expat "${MAKE_CURRENT_BINARY_DIR}/test_expat")
ADD_DEPENDENCIES(check test_expat)

ADD_EXECUTABLE(test_parser_basic EXCLUDE_FROM_ALL test_parser_basic.cpp)
TARGET_LINK_LIBRARIES(test_parser_basic svg)
ADD_TEST(test_parser_basic "${MAKE_CURRENT_BINARY_DIR}/test_parser_basic")
ADD_DEPENDENCIES(check test_parser_basic)

ADD_EXECUTABLE(test_parser_numberlist EXCLUDE_FROM_ALL test_parser_numberlist.cpp)
TARGET_LINK_LIBRARIES(test_parser_numberlist svg)
ADD_TEST(test_parser_numberlist "${MAKE_CURRENT_BINARY_DIR}/test_parser_numberlist")
ADD_DEPENDENCIES(check test_parser_numberlist)
