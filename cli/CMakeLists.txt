get_filename_component(EXEC_NAME "${CMAKE_CURRENT_SOURCE_DIR}" NAME)
set(EXEC_NAME "${PROJECT_NAME}_${EXEC_NAME}")

set(Header_Files "cli.h")
source_group("Header Files" FILES "${Header_Files}")

set(Source_Files "cli.c")
source_group("Source Files" FILES "${Source_Files}")

add_executable("${EXEC_NAME}" "${Header_Files}" "${Source_Files}")

target_link_libraries("${EXEC_NAME}" PRIVATE "${PROJECT_NAME}_compiler_flags" "${PROJECT_NAME}_list")

include(GNUInstallDirs)
target_include_directories(
        "${EXEC_NAME}"
        PUBLIC
        "$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>"
        "$<BUILD_INTERFACE:${CMAKE_CURRENT_BINARY_DIR}>"
        "$<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}>"
)

if (MSVC)
    target_compile_definitions("${EXEC_NAME}" PRIVATE _CRT_SECURE_NO_WARNINGS)
endif (MSVC)
