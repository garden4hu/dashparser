LIST(APPEND LIB_DASH_PARSER_HEADER
        ../include/common_type.h
        ../parser/mime.h
        ../parser/identifier.h
        ../parser/utils/dash_time.h
        ../parser/common_parser.h
        )


LIST(APPEND LIB_DASH_PARSER_CXX_FILES
        ../parser/common_attributes_elements.cpp
        ../parser/xml/dash_xml.cpp
        ../parser/dash_parser.cpp
        ../parser/segment.cpp
        ../parser/representation.cpp
        ../parser/adaptation_set.cpp
        ../parser/period.cpp
        ../parser/util.cpp
        ../parser/mpd.cpp
        ../parser/dash.cpp
        ../parser/utils/dash_time.cpp
        ../parser/utils/prtime.cpp
        ../parser/common_parser.cpp
        )

add_executable(
        mpd_parser
        ${LIB_DASH_PARSER_HEADER}
        ${LIB_DASH_PARSER_CXX_FILES}
        test_mpd.cpp ../parser/common_parser.cpp)

target_link_libraries(mpd_parser PRIVATE GTest::gtest GTest::gtest_main LibXml2::LibXml2 fmt::fmt-header-only absl::base absl::strings)
if (CMAKE_CXX_COMPILER_ID STREQUAL "MSVC")
    set_property(TARGET mpd_parser PROPERTY MSVC_RUNTIME_LIBRARY "MultiThreaded$<$<CONFIG:Debug>:Debug>")
endif()
#add_test(
#        NAME
#        mpd_parser.unittest
#        COMMAND
#        ${CMAKE_BINARY_DIR}/${CMAKE_INSTALL_BINDIR}/mpd_parser.unittest
#)