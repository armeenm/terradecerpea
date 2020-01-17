find_package(PkgConfig)

pkg_check_modules(PC_tensorflow QUIET tensorflow)

find_path(tensorflow_INCLUDE_DIR
  NAMES tensorflow/core
  PATHS ${PC_tensorflow_INCLUDE_DIRS})

# tensorflow #
find_library(tensorflow_LIBRARIES
  NAMES tensorflow
  PATHS ${PC_tensorflow_LIBRARY_DIRS})

mark_as_advanced(tensorflow_INCLUDE_DIR tensorflow_LIBRARIES)

set(tensorflow_VERSION ${PC_tensorflow_VERSION})

include(FindPackageHandleStandardArgs)
find_package_handle_standard_args(tensorflow
  REQUIRED_VARS tensorflow_INCLUDE_DIR tensorflow_LIBRARIES
  VERSION_VAR tensorflow_VERSION)

if(tensorflow_FOUND AND NOT TensorFlow::tensorflow)
  add_library(TensorFlow::tensorflow SHARED IMPORTED)
  set_target_properties(TensorFlow::tensorflow PROPERTIES
    IMPORTED_LOCATION "${tensorflow_LIBRARIES}"
    INTERFACE_INCLUDE_DIRECTORIES tensorflow_framework
    INTERFACE_INCLUDE_DIRECTORIES "${tensorflow_INCLUDE_DIR}")
endif()


# tensorflow_cc #
pkg_check_modules(PC_tensorflow_cc QUIET tensorflow_cc)

find_library(tensorflow_cc_LIBRARIES
  NAMES tensorflow_cc
  PATHS ${PC_tensorflow_cc_LIBRARY_DIRS})

mark_as_advanced(tensorflow_cc_INCLUDE_DIR tensorflow_cc_LIBRARIES)

set(tensorflow_VERSION ${PC_tensorflow_cc_VERSION})

include(FindPackageHandleStandardArgs)
find_package_handle_standard_args(tensorflow_cc
  REQUIRED_VARS tensorflow_INCLUDE_DIR tensorflow_cc_LIBRARIES
  VERSION_VAR tensorflow_cc_VERSION)

if(tensorflow_FOUND AND NOT TensorFlow::tensorflow_cc)
  add_library(TensorFlow::tensorflow_cc SHARED IMPORTED)
  set_target_properties(TensorFlow::tensorflow_cc PROPERTIES
    IMPORTED_LOCATION "${tensorflow_cc_LIBRARIES}"
    INTERFACE_LINK_LIBRARIES tensorflow_framework
    INTERFACE_INCLUDE_DIRECTORIES "${tensorflow_INCLUDE_DIR}")
endif()
