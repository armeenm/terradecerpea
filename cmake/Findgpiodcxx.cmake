find_path(gpiodcxx_INCLUDE_DIR NAMES gpiod.hpp)

message("Include dir: " "${gpiodcxx_INCLUDE_DIR}")

find_library(gpiodcxx_LIBRARIES NAMES gpiodcxx)

#set(gpiodcxx_VERSION ${PC_gpiodcxx_VERSION})

include(FindPackageHandleStandardArgs)
find_package_handle_standard_args(gpiodcxx
  REQUIRED_VARS gpiodcxx_INCLUDE_DIR
  VERSION_VAR "1.0")

if(gpiodcxx_FOUND AND NOT gpiodcxx::gpiodcxx)
  add_library(gpiodcxx::gpiodcxx SHARED IMPORTED)
  set_target_properties(gpiodcxx::gpiodcxx PROPERTIES
    IMPORTED_LOCATION "${gpiodcxx_LIBRARIES}"
    INTERFACE_INCLUDE_DIRECTORIES "${gpiodcxx_INCLUDE_DIR}")
endif()
