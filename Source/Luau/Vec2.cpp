#include "Vec2.h"

#include <array>

#include <lua.h>
#include <lualib.h>
#include <luacode.h>

#include "LuauHelp.h"

namespace Luau
{

int Vec2::New(lua_State* LuauState)
{
   float X = luaL_checknumber(LuauState, 1);
   float Y = luaL_checknumber(LuauState, 2);

   Vec2 Vec2(X, Y);
   Vec2.LuauPush(LuauState);

   return 1;
}

Vec2 Vec2::LuauCheck(lua_State *LuauState, int Index)
{
   luaL_checktype(LuauState, Index, LUA_TTABLE);

   lua_getfield(LuauState, Index, "X");
   float X = luaL_checknumber(LuauState, -1);
   lua_pop(LuauState, 1);

   lua_getfield(LuauState, Index, "Y");
   float Y = luaL_checknumber(LuauState, -1);
   lua_pop(LuauState, 1);

   return Vec2(X, Y);
}

bool Vec2::LuauOpt(lua_State *LuauState, int Index, Vec2 *OutVec)
{
   if (OutVec && lua_gettop(LuauState) >= Index && lua_istable(LuauState, Index))
   {
      *OutVec = LuauCheck(LuauState, Index);
      return true;
   }

   return false;
}

void Vec2::LuauPush(lua_State* LuauState)
{
   lua_createtable(LuauState, 0, 2);

   lua_pushnumber(LuauState, X);
   lua_setfield(LuauState, -2, "X");

   lua_pushnumber(LuauState, Y);
   lua_setfield(LuauState, -2, "Y");
}

luaL_Reg Vec2::Functions[] = {
   { "New", New },
};

void Vec2::LoadGlobal(lua_State *LuauState)
{
   LuauHelp::SetupFunctionsGlobal(LuauState, Functions, std::size(Functions), "Vec2");
}

}
