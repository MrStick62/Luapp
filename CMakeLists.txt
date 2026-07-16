cmake_minimum_required(VERSION 3.23)

# Projet setup
project(Luapp)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

execute_process(
   COMMAND "${CMAKE_COMMAND}" -E create_symlink
      "${CMAKE_BINARY_DIR}/compile_commands.json"
      "${CMAKE_SOURCE_DIR}/compile_commands.json"
   RESULT_VARIABLE result
)

if(NOT result EQUAL 0)
   message(STATUS "Failed to create compile commands symlink")
endif()

# Library setup
add_subdirectory(External/glfw)
add_subdirectory(External/glad)
add_subdirectory(External/imgui)
add_subdirectory(External/luau)
add_subdirectory(External/json)

# Executable setup
add_executable(Luapp)

set_target_properties(Luapp PROPERTIES
   RUNTIME_OUTPUT_DIRECTORY "bin"
)

target_sources(Luapp
   PRIVATE
      Source/Main.cpp
      Source/FileHelp.cpp
      Source/App.cpp

      Source/Luau/Gui.cpp
      Source/Luau/Web.cpp
      Source/Luau/Vec2.cpp
      Source/Luau/Color.cpp
      Source/Luau/Flags.cpp
      Source/Luau/Window.cpp
      Source/Luau/Config.cpp
      Source/Luau/GlobalFuncs.cpp
)

target_link_libraries(Luapp 
   PRIVATE 
      glfw
      glad
      imgui
      Luau.Compiler
      Luau.VM
      Luau.Ast
      Luau.Common
      nlohmann_json 
)

target_compile_definitions(Luapp
   PRIVATE
      LOCAL_APP_PATH
)
