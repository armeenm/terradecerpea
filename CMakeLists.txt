cmake_minimum_required(VERSION 3.0)
project(berrypicker)
set(CMAKE_BUILD_TYPE Debug)

set(CMAKE_CXX_FLAGS "-Wshadow -Wall -Wextra -pedantic -pipe")
set(CMAKE_CXX_STANDARD 17)

file(GLOB CXX_SRCS "src/*.cpp")
add_executable(berrypicker ${CXX_SRCS})

target_include_directories(berrypicker PRIVATE src)
target_link_libraries(berrypicker fmt gpiodcxx)
