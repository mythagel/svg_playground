
add_subdirectory(dom)

include_directories(dom/include ${PROJECT_SOURCE_DIR}/deps/uri/src)

add_library(svg STATIC document.cpp svg.cpp

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
types/focus.cpp
types/animate.cpp
types/clock_value.cpp
types/aspect_ratio.cpp
types/func_iri.cpp
types/svg.cpp
types/boolean.cpp

types/parsers/basic.cpp
types/parsers/path.cpp
types/parsers/transform.cpp
types/parsers/func_iri.cpp
types/parsers/numberlist.cpp

attr/typed_attribute.cpp
attr/bidi.cpp
attr/media.cpp
attr/core.cpp
attr/core_common.cpp
attr/properties.cpp
attr/svg.cpp

)
target_link_libraries(svg dom network-uri)
