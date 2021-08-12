cmake_minimum_required(VERSION 3.5)
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)
set(CMAKE_CXX_FLAGS "-Wall -Wextra -g")

project(EasyContact-DataBase)

set(LIBHVR DataBase/libhv)
set(SOURCE DataBase/DB_Main.cpp)

set(BUILD_SHARED on)
set(BUILD_EXAMPLES off)
add_subdirectory(${LIBHVR})
include_directories(${PROJECT_SOURCE_DIR}/${LIBHVR}/include)
link_libraries(${PROJECT_SOURCE_DIR}/${LIBHVR}/lib/libhv.so)

add_executable(ecdb ${SOURCE})
set(THREADS_PREFER_PTHREAD_FLAG on)
find_package(Threads REQUIRED)
target_link_libraries(ecdb PUBLIC Threads::Threads)

add_dependencies(ecdb libhv)
