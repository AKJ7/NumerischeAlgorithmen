#add_subdirectory(deps/SFML)
add_executable(project src/main.cpp src/graph/grap.h)
target_link_libraries(project sfml-graphics sfml-window sfml-system)
#target_link_libraries(project sfml-graphics sfml-window sfml-system SFML)