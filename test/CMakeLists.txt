
add_executable(
        mpd_parser
        test_mpd.cpp
)

target_link_libraries(mpd_parser PRIVATE GTest::gmock GTest::gtest GTest::gmock_main GTest::gtest_main)

#add_test(
#        NAME
#        mpd_parser.unittest
#        COMMAND
#        ${CMAKE_BINARY_DIR}/${CMAKE_INSTALL_BINDIR}/mpd_parser.unittest
#)