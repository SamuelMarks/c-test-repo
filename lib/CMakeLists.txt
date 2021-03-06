get_filename_component(LIBRARY_NAME "${CMAKE_CURRENT_SOURCE_DIR}" NAME)
set(LIBRARY_NAME "${PROJECT_NAME}_${LIBRARY_NAME}")

add_library("${LIBRARY_NAME}" library.c)

target_link_libraries("${LIBRARY_NAME}" PRIVATE "${PROJECT_NAME}_compiler_flags")

include(GenerateExportHeader)
set(_export_file "${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME}_export.h")
generate_export_header("${LIBRARY_NAME}" EXPORT_FILE_NAME "${_export_file}")

include(GNUInstallDirs)
target_include_directories(
        "${LIBRARY_NAME}"
        PUBLIC
        "$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>"
        "$<BUILD_INTERFACE:${CMAKE_CURRENT_BINARY_DIR}>"
        "$<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}>"
)

if (MSVC)
    target_compile_definitions("${LIBRARY_NAME}" PRIVATE _CRT_SECURE_NO_WARNINGS)
endif (MSVC)

#=========#
# Install #
#=========#

# setup the version numbering
set_property(TARGET "${LIBRARY_NAME}" PROPERTY VERSION "1.0.0")
set_property(TARGET "${LIBRARY_NAME}" PROPERTY SOVERSION "1")

install(FILES ${Header_Files} "${_export_file}"
        TYPE "INCLUDE")
