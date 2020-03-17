cmake_minimum_required(VERSION 3.12...3.16)
project(berrypicker_arm
  VERSION 0.0.1
  DESCRIPTION "Berry picker robot, arm module"
  LANGUAGES CXX)

option(FORCE_COLORED_OUTPUT
  "Always produce ANSI-colored output (GNU/Clang only)" 
  OFF)

option(STATIC_ANALYSIS
  "Enable static analysis tools"
  ON)

list(INSERT CMAKE_MODULE_PATH 0 ${CMAKE_SOURCE_DIR}/cmake)
find_package(Polhemus 1.0 REQUIRED)
find_package(Ilanta REQUIRED CONFIG)
find_package(spdlog REQUIRED)
find_package(TensorFlow REQUIRED MODULE)
#find_package(gpiod REQUIRED MODULE)

file(GLOB_RECURSE SRCS
  LIST_DIRECTORIES false
  CONFIGURE_DEPENDS
  "berrypicker/*.cpp")

add_executable(arm ${SRCS})

target_include_directories(arm PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})

set(BUILD_OPTS -Wshadow -Wduplicated-cond -Wlogical-op -Wduplicated-branches -Wnull-dereference -Wold-style-cast -Wuseless-cast -Wformat=2 -Wall -Wextra -Wconversion -Wpedantic -pipe -flto -fsanitize=undefined)
target_compile_options(arm PRIVATE ${BUILD_OPTS})
target_compile_features(arm PRIVATE cxx_std_20)
set_target_properties(arm PROPERTIES CXX_EXTENSIONS OFF)

target_link_libraries(arm PRIVATE
  ubsan
  Ilanta::ilanta
  Polhemus::polhemus_cc
  spdlog::spdlog
  TensorFlow::tensorflow_cc
  gpiod::gpiodcxx)

if(${FORCE_COLORED_OUTPUT})
  if("${CMAKE_CXX_COMPILER_ID}" STREQUAL "GNU")
    target_compile_options(arm PRIVATE -fdiagnostics-color=always)
  elseif("${CMAKE_CXX_COMPILER_ID}" STREQUAL "Clang")
    target_compile_options(arm PRIVATE -fcolor-diagnostics)
  endif()
endif()

if(${STATIC_ANALYSIS})
  set_target_properties(arm PROPERTIES
    CXX_CLANG_TIDY "clang-tidy;-checks=*"
    CXX_CPPCHECK "cppcheck;--std=c++17")
endif()
