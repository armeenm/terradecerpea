find_package(PkgConfig)
pkg_check_modules(PC_gpiodcxx QUIET libgpiod)

find_path(gpiodcxx_INCLUDE_DIR
  NAMES gpiod.hpp
  PATHS ${PC_gpiodcxx_INCLUDE_DIRS})

find_library(gpiodcxx_LIBRARIES
  NAMES gpiodcxx
  PATHS ${PC_gpiodcxx_LIBRARY_DIRS})

mark_as_advanced(gpiodcxx_INCLUDE_DIR gpiodcxx_LIBRARIES)

set(gpiodcxx_VERSION ${PC_gpiodcxx_VERSION})

include(FindPackageHandleStandardArgs)
find_package_handle_standard_args(gpiodcxx
  REQUIRED_VARS gpiodcxx_INCLUDE_DIR
  VERSION_VAR gpiodcxx_VERSION)

if(gpiodcxx_FOUND AND NOT gpiodcxx::gpiodcxx)
  add_library(gpiodcxx::gpiodcxx SHARED IMPORTED)
  set_target_properties(gpiodcxx::gpiodcxx PROPERTIES
    IMPORTED_LOCATION "${gpiodcxx_LIBRARIES}"
    INTERFACE_INCLUDE_DIRECTORIES "${gpiodcxx_INCLUDE_DIR}")
endif()
