#include "GlobalFuncs.h"

#include <array>
#include <sstream>
#include <iostream>
#include <exception>

#include <lua.h>
#include <lualib.h>
#include <luacode.h>

#include "../App.h"
#include "../FileHelp.h"

namespace Luau
{

int GlobalFuncs::Require(lua_State* LuauState)
{
   /**
    *    Check if module exists
    */

   const char* ModuleName = luaL_checkstring(LuauState, 1);

   lua_getfield(LuauState, LUA_REGISTRYINDEX, "_LOADED");
   lua_getfield(LuauState, -1, ModuleName);

   if (!lua_isnil(LuauState, -1))
      return 1;

   lua_pop(LuauState, -1);

   /**
    *    Load module
    */

   std::stringstream FileName;
   FileName << ModuleName << ".luau";

   std::string Content = FileHelp::ReadWholeFile((App::GetPath() / FileName.str()).string());

   size_t BytecodeSize = 0;
   char* Bytecode = luau_compile(Content.data(), Content.length(), NULL, &BytecodeSize);
   
   if (luau_load(LuauState, ModuleName, Bytecode, BytecodeSize, 0))
   {
      luaL_error(LuauState, "Failed to load module %s!", ModuleName);
      return 0;
   }

   lua_pushstring(LuauState, ModuleName);
   if (lua_pcall(LuauState, 1, 1, 0))
   {
      luaL_error(LuauState, "Failed to load module %s!", ModuleName);
      return 0;
   }

   lua_getfield(LuauState, LUA_REGISTRYINDEX, "_LOADED");
   lua_pushvalue(LuauState, -2);
   lua_setfield(LuauState, -2, ModuleName);
   lua_pop(LuauState, 1);

   free(Bytecode);

   return 1;
}

luaL_Reg GlobalFuncs::Functions[] = {
   { "require", Require },
};

void GlobalFuncs::LoadGlobal(lua_State* LuauState)
{
   lua_getfield(LuauState, LUA_REGISTRYINDEX, "_LOADED");
   bool IsLoadedNil = lua_isnil(LuauState, -1);
   lua_pop(LuauState, 1);

   if (IsLoadedNil)
   {
      lua_newtable(LuauState);
      lua_setfield(LuauState, LUA_REGISTRYINDEX, "_LOADED");
   }

   for (luaL_Reg Function : Functions)
   {
      lua_pushcfunction(LuauState, Function.func, Function.name);
      lua_setglobal(LuauState, Function.name);
   }
}

}
