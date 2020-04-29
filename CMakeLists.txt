cmake_minimum_required(VERSION 3.15...3.17 FATAL_ERROR)

include(cmake/BuildType.cmake)
include(cmake/ExportCompileCommands.cmake)

project(berrypicker_arm
  VERSION 0.0.1
  DESCRIPTION "Berry picker robot, arm module"
  LANGUAGES CXX)

option(FORCE_COLORED_OUTPUT
  "Always produce ANSI-colored output (GNU/Clang only)" 
  OFF)

option(STATIC_ANALYSIS
  "Enable static analysis tools"
  OFF)

list(PREPEND CMAKE_MODULE_PATH ${CMAKE_SOURCE_DIR}/cmake)

find_package(Polhemus 1.0 REQUIRED)
find_package(Ilanta REQUIRED)
find_package(spdlog REQUIRED)
find_package(gpiodcxx REQUIRED)
find_package(Torch REQUIRED)

file(GLOB_RECURSE SRCS
  LIST_DIRECTORIES false
  CONFIGURE_DEPENDS
  "berrypicker/*.cpp")

add_executable(arm ${SRCS})

target_compile_options(arm PRIVATE 
  -Wshadow
  -Warray-bounds
  -Wzero-length-bounds
  -Wstring-compare
  -Wstringop-overflow
  #-Wmismatched-tags
  #-Wredundant-tags
  -Wduplicated-cond
  -Wlogical-op
  -Wduplicated-branches
  -Wnull-dereference
  -Wold-style-cast
  -Wuseless-cast
  -Wformat=2 
  -Wall
  -Wextra
  -Wconversion
  -Wpedantic
  -pipe
  -flto
  "${TORCH_CXX_FLAGS}")

target_include_directories(arm PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})
target_compile_features(arm PRIVATE cxx_std_20)

if(CMAKE_BUILD_TYPE MATCHES DEBUG)
  target_compile_options(arm PRIVATE -fsanitize=address -fsanitize=undefined)
  target_link_libraries(arm PRIVATE asan ubsan)
endif()

target_link_libraries(arm PRIVATE
  "${TORCH_LIBRARIES}"
  gpiodcxx::gpiodcxx
  Ilanta::Ilanta
  Polhemus::polhemus_cxx
  spdlog::spdlog)

if(FORCE_COLORED_OUTPUT OR CMAKE_GENERATOR STREQUAL "Ninja")
  if(CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
    target_compile_options(arm PRIVATE -fdiagnostics-color=always)
  elseif(CMAKE_CXX_COMPILER_ID STREQUAL "Clang")
    target_compile_options(arm PRIVATE -fcolor-diagnostics)
  endif()
endif()

if(STATIC_ANALYSIS)
  set_target_properties(arm PROPERTIES
    CXX_CLANG_TIDY "clang-tidy;-checks=*"
    CXX_CPPCHECK "cppcheck;--std=c++17")
endif()
