cmake_minimum_required(VERSION 3.16)
project(artscii)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# find needed packages
find_package(PNG REQUIRED)

# Include Directories
include_directories(${CMAKE_SOURCE_DIR}/include)
file(GLOB_RECURSE SOURCES "src/*.cpp")

add_executable(artscii ${SOURCES})
target_link_libraries(artscii PNG::PNG)

