add_executable(
   "${PROJECT_NAME}" 
   main.cpp
   application.cpp
   window.cpp
   container.cpp
   panel.cpp
   label.cpp
   button.cpp
   textarea.cpp
   ../includes/event.hpp
   ../includes/colors.hpp
   ../includes/component2d.hpp
) 
 
target_link_libraries("${PROJECT_NAME}" PRIVATE raylib) 
