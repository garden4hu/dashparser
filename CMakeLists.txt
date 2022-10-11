cmake_minimum_required(VERSION 3.21)
project(DASHParser CXX)

option(DASH_ENABLE_STATIC "generate static library" OFF)
option(DASH_ENABLE_STATIC "generate static library" OFF)
option(DASH_ENABLE_TESTS "Build DASH parser tests" ON)

set(CMAKE_CXX_STANDARD 17)

find_package(absl CONFIG REQUIRED)
find_package(LibXml2 CONFIG REQUIRED)
find_package(fmt CONFIG REQUIRED)

include_directories(include)
include_directories(parser)

list(APPEND DASH_CXX_HEADERS
		include/common_type.h
		parser/mime.h
		parser/identifier.h
		parser/utils/dash_time.h
		parser/base/helper.h
		parser/common_parser.h
)


list(APPEND DASH_CXX_FILES
		parser/common_attributes_elements.cpp
		parser/xml/dash_xml.cpp
		parser/dash_parser.cpp
		parser/common_parser.cpp
		parser/segment.cpp
		parser/representation.cpp
		parser/adaptation_set.cpp
		parser/period.cpp
		parser/util.cpp
		parser/mpd.cpp
		parser/dash.cpp
		parser/utils/prtime.cpp
		parser/utils/dash_time.cpp

)


add_library(${PROJECT_NAME} SHARED ${DASH_CXX_HEADERS} ${DASH_CXX_FILES} parser/utils/url_parser.cpp parser/utils/url_parser.h parser/utils/url.cpp parser/utils/url.h)

# for MSVC
if (CMAKE_CXX_COMPILER_ID STREQUAL "MSVC")
	## set_property(TARGET mpd_parser PROPERTY MSVC_RUNTIME_LIBRARY "MultiThreaded$<$<CONFIG:Debug>:Debug>")
endif()

target_include_directories(${PROJECT_NAME} PUBLIC include)
target_include_directories(${PROJECT_NAME} PRIVATE parser)
target_link_libraries(${PROJECT_NAME}  PRIVATE LibXml2::LibXml2 fmt::fmt-header-only absl::base absl::strings)
# for MSVC
if (CMAKE_CXX_COMPILER_ID STREQUAL "MSVC")
	set_property(TARGET ${PROJECT_NAME} PROPERTY MSVC_RUNTIME_LIBRARY "MultiThreaded$<$<CONFIG:Debug>:Debug>")
endif()

#if(ON)
	find_package(GTest CONFIG REQUIRED)
	enable_testing()
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/test)

#	add_executable(
#			mpd_parser
#            ${DASH_CXX_HEADERS}
#			${DASH_CXX_FILES}
#			test/test_mpd.cpp
#			parser/utils/prtime.h)

## for linking static library,  we should set the runtime flag to avoid the conflicting of symbols.
	if (CMAKE_CXX_COMPILER_ID STREQUAL "MSVC")
		## set_property(TARGET mpd_parser PROPERTY MSVC_RUNTIME_LIBRARY "MultiThreaded$<$<CONFIG:Debug>:Debug>")
	endif()
#endif()

