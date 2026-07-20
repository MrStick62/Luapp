#include "LuauHelp.h"

#include <lua.h>
#include <lualib.h>
#include <luacode.h>

namespace Luau::LuauHelp
{

void SetupFunctionsGlobal(lua_State* LuauState, luaL_Reg Functions[], size_t Size, const char* GlobalName)
{
   lua_createtable(LuauState, 0, Size);

   for (int i = 0; i < Size; i++)
   {
      lua_pushcfunction(LuauState, Functions[i].func, Functions[i].name);
      lua_setfield(LuauState, -2, Functions[i].name);
   }

   lua_setglobal(LuauState, GlobalName);
}

void SetupEnumGlobal(lua_State* LuauState, std::pair<std::string, int> Table[], size_t Size, const char* GlobalName)
{
   lua_createtable(LuauState, 0, Size);

   for (int i = 0; i < Size; i++)
   {
      lua_pushinteger(LuauState, Table[i].second);
      lua_setfield(LuauState, -2, Table[i].first.data());
   }

   lua_setglobal(LuauState, GlobalName);
}

}
