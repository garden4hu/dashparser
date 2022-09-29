cmake_minimum_required(VERSION 3.21)
project(DASHParser CXX)

option(DASH_ENABLE_STATIC "generate static library" OFF)
option(DASH_ENABLE_STATIC "generate static library" OFF)

set(CMAKE_CXX_STANDARD 17)

find_package(absl CONFIG REQUIRED)
find_package(LibXml2 CONFIG REQUIRED)
find_package(fmt CONFIG REQUIRED)


list(APPEND DASH_CXX_HEADERS
	include/common_type.h 
	parser/mime.h
)


list(APPEND DASH_CXX_FILES
	parser/common_attributes_elements.cpp
	parser/xml/dash_xml.cpp
	parser/dash_parser.cpp
	parser/segment.cpp
	parser/representation.cpp
	parser/adaptation_set.cpp
	parser/period.cpp
	parser/util.cpp
	parser/mpd.cpp
	parser/dash.cpp
)


add_library(${PROJECT_NAME} SHARED ${DASH_CXX_FILES} ${DASH_CXX_HEADERS})

target_include_directories(${PROJECT_NAME} PUBLIC include)
target_include_directories(${PROJECT_NAME} PRIVATE parser)
target_link_libraries(${PROJECT_NAME}  PRIVATE LibXml2::LibXml2 fmt::fmt-header-only absl::base)


enable_testing()
add_subdirectory(tests)

