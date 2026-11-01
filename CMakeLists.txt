cmake_minimum_required(VERSION 3.23)

option(BUILD_FOR_APP "Build as an application bundle" OFF)

set(APP_NAME "Luapp" CACHE STRING "Name of the executable")
set(LUAU_PATH "" CACHE STRING "Path to Luau entry point")
set(ICON_PATH "" CACHE STRING "Path to app icon")

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
add_subdirectory(External/nativefiledialog-extended)

set(SOURCES
   Source/Main.cpp
   Source/FileHelp.cpp
   Source/Setup.cpp
   Source/App.cpp

   Source/Luau/Gui.cpp
   Source/Luau/Web.cpp
   Source/Luau/Vec2.cpp
   Source/Luau/Font.cpp
   Source/Luau/File.cpp
   Source/Luau/Color.cpp
   Source/Luau/Flags.cpp
   Source/Luau/Input.cpp
   Source/Luau/Image.cpp
   Source/Luau/Icons.cpp
   Source/Luau/Window.cpp
   Source/Luau/Config.cpp
   Source/Luau/LuauHelp.cpp
   Source/Luau/GlobalFuncs.cpp
)

if(BUILD_FOR_APP)
   if(APPLE)
      get_filename_component(ICON_FILENAME ${ICON_PATH} NAME)
      set_source_files_properties(${ICON_PATH} PROPERTIES
         MACOSX_PACKAGE_LOCATION "Resources"
      )
      add_executable(${APP_NAME} MACOSX_BUNDLE ${SOURCES} ${ICON_PATH})
      set_target_properties(${APP_NAME} PROPERTIES 
         MACOSX_BUNDLE_GUI_IDENTIFIER "Luapp.${APP_NAME}"
         MACOSX_BUNDLE_EXECUTABLE_NAME "${APP_NAME}"
         MACOSX_BUNDLE_BUNDLE_NAME "${APP_NAME}"
         MACOSX_BUNDLE_ICON_FILE "${ICON_FILENAME}"
         RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin"
         LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin"
         LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin"
      )
   else()
      add_executable(${APP_NAME} ${SOURCES})
      set_target_properties(${APP_NAME} PROPERTIES
         RUNTIME_OUTPUT_DIRECTORY "bin"
      )
   endif()
else()
   add_executable(${APP_NAME} ${SOURCES})
   set_target_properties(${APP_NAME} PROPERTIES
      RUNTIME_OUTPUT_DIRECTORY "bin"
   )
endif()


target_link_libraries(${APP_NAME}
   PRIVATE 
      nfd
      glfw
      glad
      imgui
      Luau.Compiler
      Luau.VM
      Luau.Ast
      Luau.Common
      nlohmann_json 
)

target_include_directories(${APP_NAME}
   PRIVATE
      External/stb
      External/avir
)

target_compile_definitions(${APP_NAME}
   PRIVATE
      LOCAL_APP_PATH
      SOURCE_DIR="${CMAKE_SOURCE_DIR}"
)

string(LENGTH "${LUAU_PATH}" LUAU_PATH_LENGTH)
if (LUAU_PATH_LENGTH GREATER 0)
   target_compile_definitions(${APP_NAME}
      PRIVATE
         LUAU_ENTRY_POINT="${LUAU_PATH}"
   )
endif()

unset(APP_NAME CACHE)
unset(LUAU_PATH CACHE)
