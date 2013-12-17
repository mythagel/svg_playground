CMAKE_MINIMUM_REQUIRED(VERSION 2.6)
PROJECT(svg_playground)

ENABLE_TESTING()
IF(NOT TARGET check)
	ADD_CUSTOM_TARGET(check COMMAND ${CMAKE_CTEST_COMMAND})
ENDIF()

IF(UNIX)
	SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -Wall -Wextra")
ENDIF()

#add_executable(xerces_basic xerces.cpp)
#target_link_libraries(xerces_basic xerces-c)

add_subdirectory(deps)
add_subdirectory(src)
ADD_SUBDIRECTORY(test)
