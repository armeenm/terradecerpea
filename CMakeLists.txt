cmake_minimum_required(VERSION 3.15...3.18 FATAL_ERROR)

list(PREPEND CMAKE_PREFIX_PATH
    ${CMAKE_BINARY_DIR})
  list(PREPEND CMAKE_MODULE_PATH
      ${CMAKE_BINARY_DIR} ${CMAKE_CURRENT_SOURCE_DIR}/cmake)

set(CMAKE_DEFAULT_BUILD_TYPE Release)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

project(terradecerpea
  VERSION 2.0.0
  DESCRIPTION "Berry picker robot v2"
  LANGUAGES CXX)

option(FORCE_COLORED_OUTPUT
  "Always produce ANSI-colored output (GNU/Clang only)" 
  OFF)

option(STATIC_ANALYSIS
  "Enable static analysis tools"
  OFF)

find_package(gpiodcxx REQUIRED)
find_package(polhemus REQUIRED CONFIG)
find_package(ilanta REQUIRED CONFIG)
find_package(spdlog REQUIRED CONFIG)
find_package(fmt REQUIRED CONFIG)
find_package(range-v3 REQUIRED CONFIG)
#find_package(Torch REQUIRED)

file(GLOB_RECURSE SRCS
  LIST_DIRECTORIES false
  CONFIGURE_DEPENDS
  "src/*.cpp")

add_executable(trdcrp ${SRCS})

target_compile_options(trdcrp PRIVATE 
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

target_include_directories(trdcrp PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/src)
target_compile_features(trdcrp PRIVATE cxx_std_20)

if(CMAKE_BUILD_TYPE MATCHES DEBUG)
  target_compile_options(trdcrp PRIVATE -fsanitize=address -fsanitize=undefined)
  target_link_libraries(trdcrp PRIVATE asan ubsan)
endif()

target_link_libraries(trdcrp PRIVATE
  "${TORCH_LIBRARIES}"
  gpiodcxx::gpiodcxx
  ilanta::ilanta
  polhemus::polhemus_cxx
  fmt::fmt
  range-v3::range-v3
  spdlog::spdlog)

if(FORCE_COLORED_OUTPUT OR CMAKE_GENERATOR MATCHES "^Ninja")
  if(CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
    target_compile_options(trdcrp PRIVATE -fdiagnostics-color=always)
  elseif(CMAKE_CXX_COMPILER_ID STREQUAL "Clang")
    target_compile_options(trdcrp PRIVATE -fcolor-diagnostics)
  endif()
endif()

if(STATIC_ANALYSIS)
  set_target_properties(trdcrp PROPERTIES
    CXX_CLANG_TIDY "clang-tidy;-checks=*"
    CXX_CPPCHECK "cppcheck;--std=c++17")
endif()
