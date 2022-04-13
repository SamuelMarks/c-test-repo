include("release/CPackConfig.cmake")

set(CPACK_INSTALL_CMAKE_PROJECTS
        "debug;c_test_repo;ALL;/"
        "release;c_test_repo;ALL;/"
)
