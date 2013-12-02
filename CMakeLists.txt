CMAKE_MINIMUM_REQUIRED(VERSION 2.6)
PROJECT(svg_playground)

IF(UNIX)
	SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
ENDIF()

add_executable(xerces_basic xerces.cpp)
target_link_libraries(xerces_basic xerces-c)

