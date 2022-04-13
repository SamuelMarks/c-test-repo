set(LIBRARY_NAME "${PROJECT_NAME}_list")

set(Header_Files "list.h")
source_group("Header Files" FILES "${Header_Files}")

set(Source_Files "list.c")
source_group("Source Files" FILES "${Source_Files}")
add_library("${LIBRARY_NAME}" "${Header_Files}" "${Source_Files}")

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

#=========#
# Install #
#=========#

# setup the version numbering
set_property(TARGET "${LIBRARY_NAME}" PROPERTY VERSION "1.0.0")
set_property(TARGET "${LIBRARY_NAME}" PROPERTY SOVERSION "1")

install(FILES ${Header_Files} "${_export_file}"
        TYPE "INCLUDE")
