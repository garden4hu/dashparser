cmake_minimum_required(VERSION 3.21)
project(DASHParser CXX)

option(DASH_ENABLE_STATIC "generate static library" OFF)
option(DASH_ENABLE_STATIC "generate static library" OFF)

set(CMAKE_CXX_STANDARD 17)

find_package(absl CONFIG REQUIRED)
find_package(LibXml2 CONFIG REQUIRED)
find_package(fmt CONFIG REQUIRED)



list(APPEND DASH_CXX_FILES
	parser/xml/dash_xml.cpp
	parser/dash_parser.cpp
)


add_library(${PROJECT_NAME} SHARED ${DASH_CXX_FILES})

target_include_directories(${PROJECT_NAME} PUBLIC include)
target_include_directories(${PROJECT_NAME} PRIVATE parser)
target_link_libraries(${PROJECT_NAME}  PRIVATE LibXml2::LibXml2 fmt::fmt-header-only absl::any absl::base absl::bits absl::city)


enable_testing()
add_subdirectory(test)

