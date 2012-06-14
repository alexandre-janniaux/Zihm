cmake_minimum_required(VERSION 2.8)

set(ROOTDIR ${CMAKE_SOURCE_DIR})

include(cmake/config.cmake)

add_definitions(-DZIHM_EXPORTS -static)

include_directories(
   ${ROOTDIR}/include
   ${SFML_INCLUDE_DIR}
)

add_definitions(-Wfatal-errors -std=c++0x)

set(BUILD_SHARED_LIBS TRUE CACHE BOOL "TRUE to build Zihm as shared library, FALSE to build it as static library")

set(BUILD_EXAMPLES FALSE CACHE BOOL "TRUE to build the Zihm examples, FALSE to ignore them")

add_subdirectory(src)

if(BUILD_EXAMPLES)
  add_subdirectory(examples)
endif()

install( 
    DIRECTORY ./include/Zihm
    DESTINATION include
    COMPONENT devel
)