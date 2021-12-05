cmake_minimum_required(VERSION 3.10)

project(stomperd VERSION 1.0.0)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

FIND_PACKAGE(Boost COMPONENTS program_options REQUIRED)
include_directories(${Boost_INCLUDE_DIR})

if (WIN32)
    add_definitions(-DNOMINMAX -DWIN32_LEAN_AND_MEAN)
endif()

include_directories(./)

add_executable(stomperd
    src/main.cpp
    src/startup.cpp
    src/server.cpp
    src/output.cpp)

target_link_libraries(stomperd PRIVATE event ${Boost_LIBRARIES})

if (WIN32)
    target_link_libraries(stomperd PRIVATE ws2_32)
endif()
