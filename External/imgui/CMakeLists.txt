add_library(imgui
   STATIC
      src/imgui.cpp
      src/imgui_draw.cpp
      src/imgui_tables.cpp
      src/imgui_widgets.cpp
      src/imgui_demo.cpp

      backends/imgui_impl_glfw.cpp
      backends/imgui_impl_opengl3.cpp
)

target_include_directories(imgui
   PUBLIC
      include
   PRIVATE
      include/imgui
)

target_link_libraries(imgui
   PRIVATE 
      glfw
      glad
)
