option(SFML_INSTALLED "SFML was successfully installed" ON)
add_executable(project src/main.cpp src/graph/grap.h)

if (SFML_INSTALLED)
    target_link_libraries(project sfml-graphics sfml-window sfml-system)
    message(STATUS "SFML_INSTALLED")
endif()