cmake_minimum_required(VERSION 3.23)

# Projet setup
project(Luapp)

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

# OpenGL setup
add_subdirectory(External/glfw)
add_subdirectory(External/glad)
add_subdirectory(External/imgui)
add_subdirectory(External/luau)

# Executable setup
add_executable(Luapp)

target_sources(Luapp
   PRIVATE
      Source/Main.cpp
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
)
