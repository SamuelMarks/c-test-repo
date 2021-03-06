cmake_minimum_required(VERSION 3.15)

project(c_test_repo VERSION 0.0.1 LANGUAGES C)

#===============#
# Compiler args #
#===============#

set(CMAKE_C_VISIBILITY_PRESET hidden)
set(CMAKE_VISIBILITY_INLINES_HIDDEN YES)
set(CMAKE_C_STANDARD 90 CACHE STRING "")

add_library("${PROJECT_NAME}_compiler_flags" INTERFACE)
target_compile_features("${PROJECT_NAME}_compiler_flags" INTERFACE "c_std_${CMAKE_C_STANDARD}")

# add compiler warning flags just when building this project via
# the BUILD_INTERFACE genex
set(gcc_like "$<COMPILE_LANG_AND_ID:C,CXX,ARMClang,AppleClang,Clang,GNU,LCC>")
set(msvc "$<COMPILE_LANG_AND_ID:C,CXX,MSVC>")
target_compile_options(
        "${PROJECT_NAME}_compiler_flags"
        INTERFACE
        "$<${gcc_like}:$<BUILD_INTERFACE:-Wshadow;-Wformat=2;-Wno-format-nonliteral;-Wall;-pedantic>>"
        "$<${msvc}:$<BUILD_INTERFACE:-W3;-WX;-Zi;-permissive->>"
)

# Set the build directories
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${PROJECT_BINARY_DIR}/bin")
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY "${PROJECT_BINARY_DIR}/lib")

#===========#
# Configure #
#===========#

# configure a header file to pass the version number only
configure_file(
        "${CMAKE_CURRENT_SOURCE_DIR}/cmake/config.h.in"
        "${PROJECT_NAME}Config.h"
)

#=============#
# Sub-targets #
#=============#

set(installable_libs "")
foreach (_lib "list" "lib")
    add_subdirectory("${_lib}")
    list(APPEND installable_libs "${PROJECT_NAME}_${_lib}")
endforeach (_lib "list" "lib")
add_subdirectory("cli")

include(CTest)
if (BUILD_TESTING)
    add_subdirectory("tests")
endif (BUILD_TESTING)

#=========#
# Install #
#=========#

include(GNUInstallDirs)

install(
        FILES "${PROJECT_BINARY_DIR}/${PROJECT_NAME}Config.h"
        TYPE "INCLUDE"
)
include(InstallRequiredSystemLibraries)
set(CPACK_BUNDLE_NAME "${PROJECT_NAME}")
set(CPACK_PACKAGE_VENDOR "SamuelMarks")
set(CPACK_PACKAGE_DESCRIPTION "Repo for [most] all my experiments in C, on GitHub to run in cross-platform workflows.")
set(CPACK_PACKAGE_DESCRIPTION_SUMMARY "${CPACK_PACKAGE_DESCRIPTION_SUMMARY}")
if (APPLE)
    set(CPACK_BUNDLE_PLIST "${CMAKE_CURRENT_SOURCE_DIR}/cmake/Info.plist")
    set(CPACK_BUNDLE_ICON "${CMAKE_CURRENT_SOURCE_DIR}/cmake/Info.plist")
    set(CPACK_PACKAGE_ICON "${CMAKE_CURRENT_SOURCE_DIR}/cmake/CustomVolumeIcon.icns")
endif (APPLE)
set(CPACK_RESOURCE_FILE_LICENSE "${CMAKE_CURRENT_SOURCE_DIR}/LICENSE.md")
set(CPACK_PACKAGE_VERSION_MAJOR "${${PROJECT_NAME}_VERSION_MAJOR}")
set(CPACK_PACKAGE_VERSION_MINOR "${${PROJECT_NAME}_VERSION_MINOR}")
set(CPACK_RESOURCE_FILE_README "${CMAKE_CURRENT_SOURCE_DIR}/cmake/README.txt")
set(CPACK_RESOURCE_FILE_WELCOME "${CMAKE_CURRENT_SOURCE_DIR}/cmake/Welcome.txt")
set(CPACK_PACKAGE_CONTACT "https://github.com/SamuelMarks/c-test-repo")

include(CPack)
include(CMakePackageConfigHelpers)

# generate the config file that is includes the exports
configure_package_config_file(
        "${CMAKE_CURRENT_SOURCE_DIR}/cmake/Config.cmake.in"
        "${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME}Config.cmake"
        INSTALL_DESTINATION "${CMAKE_INSTALL_DATADIR}/${PROJECT_NAME}"
        NO_SET_AND_CHECK_MACRO
        NO_CHECK_REQUIRED_COMPONENTS_MACRO
)

# generate the version file for the config file
write_basic_package_version_file(
        "${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME}ConfigVersion.cmake"
        VERSION "${${PROJECT_NAME}_VERSION_MAJOR}.${${PROJECT_NAME}_VERSION_MINOR}"
        COMPATIBILITY AnyNewerVersion
)
install(FILES "${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME}Config.cmake"
        DESTINATION "${CMAKE_INSTALL_DATADIR}/${PROJECT_NAME}")

#====================#
# Package to install #
#====================#

list(APPEND installable_libs "${PROJECT_NAME}_compiler_flags")
if (TARGET "${DEPENDANT_LIBRARY}")
    list(APPEND installable_libs "${DEPENDANT_LIBRARY}")
endif ()
install(TARGETS ${installable_libs}
        EXPORT "${LIBRARY_NAME}Targets"
        ARCHIVE DESTINATION "${CMAKE_INSTALL_LIBDIR}"
        LIBRARY DESTINATION "${CMAKE_INSTALL_LIBDIR}"
        RUNTIME DESTINATION "${CMAKE_INSTALL_BINDIR}")
install(EXPORT "${LIBRARY_NAME}Targets" DESTINATION "${CMAKE_INSTALL_DATADIR}/${LIBRARY_NAME}")
