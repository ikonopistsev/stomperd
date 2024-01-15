cmake_minimum_required(VERSION 3.10)

project(stomperd VERSION 1.0.0)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Boost COMPONENTS program_options REQUIRED)

option(STOMPERD_FIND_LIBEVENT "use find libevent" OFF)

if (STOMPERD_FIND_LIBEVENT)
    find_package(Libevent CONFIG REQUIRED)
endif()

if (WIN32)
    add_definitions(-DNOMINMAX -DWIN32_LEAN_AND_MEAN)
endif()

# add_subdirectory(btdef)
# add_subdirectory(btpro)
add_subdirectory(e4pp)
add_subdirectory(libmdbx)

add_executable(stomperd
    src/main.cpp
    src/output.cpp
    src/startup.cpp
    src/server.cpp
)

#target_include_directories(stomperd PRIVATE ${Boost_INCLUDE_DIR} btpro btdef e4pp)
target_include_directories(stomperd PRIVATE ${Boost_INCLUDE_DIR} e4pp)


if (STOMPERD_FIND_LIBEVENT)
    #target_link_libraries(stomperd PRIVATE e4pp libevent::core libevent::extra libevent::threads ${Boost_LIBRARIES})
else()
    target_link_libraries(stomperd PRIVATE e4pp event_core event_extra event_pthreads mdbx-static ${Boost_LIBRARIES})
endif()

if (WIN32)
    target_link_libraries(stomperd PRIVATE e4pp ws2_32)
endif()
