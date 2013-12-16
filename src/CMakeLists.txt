
add_library(svg STATIC document.cpp svg.cpp attr.cpp

types/length.cpp
types/colour.cpp
types/stringlist.cpp
types/core.cpp
types/media.cpp
types/bidi.cpp

types/parsers/basic.cpp
types/parsers/path.cpp
types/parsers/transform.cpp

dom/node.cpp
dom/element.cpp
dom/qualified_name.cpp
dom/character.cpp
dom/basic_element.cpp
)
