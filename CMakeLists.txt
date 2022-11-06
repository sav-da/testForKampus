cmake_minimum_required(VERSION 2.8)

project(ntrip)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -pthread")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wfatal-errors")

set(CMAKE_CXX_FLAGS_DEBUG "$ENV{CXXFLAGS} -O2 -Wall -g -ggdb")
set(CMAKE_CXX_FLAGS_RELEASE "$ENV{CXXFLAGS} -O3 -Wall")

set(ntrip_include_dirs ${CMAKE_CURRENT_SOURCE_DIR}/include)
include_directories(SYSTEM ${ntrip_include_dirs})


aux_source_directory(./src src_MAIN)

add_library(${PROJECT_NAME}
  ${src_MAIN}
)
set_target_properties(${PROJECT_NAME} PROPERTIES INTERFACE_INCLUDE_DIRECTORIES ${ntrip_include_dirs})

add_executable(ntrip_client
  ./src/ntrip_client_exmpl.cc
)
add_dependencies(ntrip_client ntrip)
target_link_libraries(ntrip_client
  ntrip
  pthread
)
