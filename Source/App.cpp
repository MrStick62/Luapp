#include "App.h"

#include <cstdlib>
#include <iostream>

#include <lua.h>
#include <luacode.h>
#include <lualib.h>

#include <GLFW/glfw3.h>

#include "FileHelp.h"

#include "Luau/Gui.h"
#include "Luau/Vec2.h"
#include "Luau/Color.h"
#include "Luau/Flags.h"
#include "Luau/Window.h"
#include "Luau/GlobalFuncs.h"

const std::string App::EntryPointName = "Main.luau";
const std::string App::DirectoryName = "Luapp";

App::App(const std::string& Name, GLFWwindow* Window)
{
   // Set path
   Path = FileHelp::GetHomeDirectory() / "Documents" / DirectoryName / Name;

   // Initialize Luau
   LuauState = luaL_newstate();
   luaL_openlibs(LuauState);

   Luau::GlobalFuncs::LoadGlobal(LuauState, Name.data());

   Luau::Gui::LoadGlobal(LuauState);
   Luau::Vec2::LoadGlobal(LuauState);
   Luau::Color::LoadGlobal(LuauState);
   Luau::Flags::LoadGlobal(LuauState);
   Luau::Window::SetCurrentWindow(Window);
   Luau::Window::LoadGlobal(LuauState);

   std::string MainContent = FileHelp::ReadWholeFile((Path / EntryPointName).string());

   size_t BytecodeSize;
   char* Bytecode = luau_compile(MainContent.data(), MainContent.length(), NULL, &BytecodeSize);
   int result = luau_load(LuauState, Name.data(), Bytecode, BytecodeSize, 0);

   lua_pcall(LuauState, 0, 0, 0);

   free(Bytecode);
}

void App::Main()
{
   if (lua_getglobal(LuauState, "Main") == LUA_TNIL)
      return;

   lua_pcall(LuauState, 0, 0, 0);
}

void App::Tick(float DeltaTime)
{
   if (lua_getglobal(LuauState, "Tick") == LUA_TNIL)
      return;

   lua_pushnumber(LuauState, DeltaTime);
   lua_pcall(LuauState, 1, 0, 0);
}

void App::OnGui(float DeltaTime)
{
   if (lua_getglobal(LuauState, "OnGui") == LUA_TNIL)
      return;

   lua_pushnumber(LuauState, DeltaTime);
   lua_pcall(LuauState, 1, 0, 0);
}
