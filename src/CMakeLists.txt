add_executable(
   "${PROJECT_NAME}" 
   main.cpp
   application.cpp
   window.cpp
   label.cpp
   container.cpp
   button.cpp
   ../includes/component2d.hpp
) 
 
target_link_libraries("${PROJECT_NAME}" PRIVATE raylib) 
