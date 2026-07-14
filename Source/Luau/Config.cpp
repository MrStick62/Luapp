#include "Config.h"

#include <array>

#include <lua.h>
#include <lualib.h>
#include <luacode.h>


namespace Luau
{

int Config::Save(lua_State* LuauState)
{
   

   return 0;
}

void Config::PushData(lua_State* LuauState)
{
   lua_createtable(LuauState, 0, 0); // change size obv
}

luaL_Reg Config::Functions[] = {
   { "Save", Save },
};

void Config::LoadGlobal(lua_State* LuauState)
{
   lua_createtable(LuauState, 0, std::size(Functions) + 1);
   
   for (luaL_Reg Function : Functions)
   {
      lua_pushcfunction(LuauState, Function.func, Function.name);
      lua_setfield(LuauState, -2, Function.name);
   }

   PushData(LuauState);
   lua_setfield(LuauState, -2, "Data");

   lua_setglobal(LuauState, "Config");
}

}
