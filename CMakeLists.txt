cmake_minimum_required(VERSION 3.5)
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)
set(CMAKE_CXX_FLAGS "-Wall -Wextra -g -O0 -w")
option(EBUG "debug mode" off)
if(EBUG)
    add_definitions(-DDEBUG)
endif()

project(EasyContact-DataBase)

set(LIBHVR DataBase/libhv)
set(SOURCE DataBase/DB_Main.cpp)

set(BUILD_STATIC OFF CACHE BOOL "build static library")
set(BUILD_EXAMPLES OFF CACHE BOOL "build examples")
set(WITH_HTTP_CLIENT OFF CACHE BOOL "compile http/client")

add_subdirectory(${LIBHVR})
include_directories(${PROJECT_SOURCE_DIR}/${LIBHVR}/include)
link_libraries(${PROJECT_SOURCE_DIR}/${LIBHVR}/lib/libhv.so)

add_executable(ecdb ${SOURCE})
set(THREADS_PREFER_PTHREAD_FLAG on)
find_package(Threads REQUIRED)
target_link_libraries(ecdb PUBLIC m Threads::Threads)

add_dependencies(ecdb hv)
set_target_properties(ecdb PROPERTIES CMAKE_CXX_FLAGS "-Wall -Wextra -g -Werror -w")
set_target_properties(ecdb PROPERTIES RUNTIME_OUTPUT_DIRECTORY "DataBase")
