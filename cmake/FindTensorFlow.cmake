find_package(PkgConfig)
pkg_check_modules(PC_tensorflow QUIET tensorflow)

find_package(tensorflow ${tensorflow_VERSION})

find_path(tensorflow_INCLUDE_DIR
  NAMES tensorflow/core
  PATHS ${PC_tensorflow_INCLUDE_DIRS})

find_library(tensorflow_LIBRARIES
  NAMES tensorflow
  PATHS ${PC_tensorflow_LIBRARY_DIRS})

set(tensorflow_VERSION ${PC_tensorflow_VERSION})

mark_as_advanced(tensorflow_INCLUDE_DIR tensorflow_LIBRARIES tensorflow_VERSION)

include(FindPackageHandleStandardArgs)
find_package_handle_standard_args(tensorflow
  REQUIRED_VARS tensorflow_INCLUDE_DIR tensorflow_LIBRARIES
  VERSION_VAR tensorflow_VERSION)

if(tensorflow_FOUND AND NOT TARGET tensorflow::tensorflow)
  add_library(tensorflow::tensorflow SHARED IMPORTED)
  set_target_properties(tensorflow::tensorflow PROPERTIES
    IMPORTED_LOCATION "${tensorflow_LIBRARIES}"
    INTERFACE_LINK_LIBRARIES tensorflow_framework
    INTERFACE_INCLUDE_DIRECTORIES "${tensorflow_INCLUDE_DIR}")
endif()
