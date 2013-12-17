
add_subdirectory(dom)

include_directories(dom/include)

add_library(svg STATIC document.cpp svg.cpp attr.cpp

types/length.cpp
types/colour.cpp
types/stringlist.cpp
types/core.cpp
types/media.cpp
types/bidi.cpp
types/flowable_text.cpp
types/gradient.cpp
types/opacity.cpp
types/paint.cpp
types/solidcolour.cpp
types/text.cpp
types/vectoreffects.cpp

types/parsers/basic.cpp
types/parsers/path.cpp
types/parsers/transform.cpp

)
target_link_libraries(svg dom)
