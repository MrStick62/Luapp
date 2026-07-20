#include "Flags.h"

#include <array>

#include <lua.h>
#include <lualib.h>
#include <luacode.h>

#include "LuauHelp.h"

namespace Luau
{

int Flags::Unite(lua_State* LuauState)
{
   luaL_checktype(LuauState, 1, LUA_TTABLE);

   lua_Integer Length = lua_objlen(LuauState, 1);
   lua_Integer OutFlags = 0;

   for (int i = 1; i <= Length; i++)
   {
      lua_rawgeti(LuauState, 1, i);

      OutFlags |= luaL_checkinteger(LuauState, -1);

      lua_pop(LuauState, 1);
   }

   lua_pushinteger(LuauState, OutFlags);

   return 1;
}

luaL_Reg Flags::Functions[] = {
   { "Unite", Unite },
};

void Flags::LoadGlobal(lua_State* LuauState)
{  
   LuauHelp::SetupFunctionsGlobal(LuauState, Functions, std::size(Functions), "Flags");
}

}
