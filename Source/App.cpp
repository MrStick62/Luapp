#include "App.h"

#include <cstdlib>
#include <iostream>

#include <lua.h>
#include <luacode.h>
#include <lualib.h>

#include "FileHelp.h"

const std::string App::EntryPointName = "Main.luau";
const std::string App::DirectoryName = "Luapp";

App::App(const std::string& Name)
{
   // Set path
   Path = FileHelp::GetHomeDirectory() / "Documents" / DirectoryName / Name;

   // Initialize Luau
   LuauState = luaL_newstate();
   luaL_openlibs(LuauState);

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
