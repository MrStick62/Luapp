#include "Color.h"

#include <array>

#include <lua.h>
#include <lualib.h>
#include <luacode.h>


namespace Luau
{

/**
 *    Luau function C++ implementations
 */

int Color::New(lua_State* LuauState)
{
   float R = luaL_checknumber(LuauState, 1);
   float G = luaL_checknumber(LuauState, 2);
   float B = luaL_checknumber(LuauState, 3);
   float A = luaL_checknumber(LuauState, 4);

   Color Color(R, G, B, A);
   Color.LuauPush(LuauState);

   return 1;
}
   
void Color::LuauPush(lua_State* LuauState)
{
   lua_createtable(LuauState, 0, 4);

   lua_pushnumber(LuauState, R);
   lua_setfield(LuauState, -2, "R");

   lua_pushnumber(LuauState, G);
   lua_setfield(LuauState, -2, "G");

   lua_pushnumber(LuauState, B);
   lua_setfield(LuauState, -2, "B");

   lua_pushnumber(LuauState, A);
   lua_setfield(LuauState, -2, "A");
}

Color Color::LuauCheck(lua_State* LuauState, int Index)
{
   luaL_checktype(LuauState, Index, LUA_TTABLE);

   lua_getfield(LuauState, Index, "R");
   float R = luaL_checknumber(LuauState, -1);
   lua_pop(LuauState, 1);

   lua_getfield(LuauState, Index, "G");
   float G = luaL_checknumber(LuauState, -1);
   lua_pop(LuauState, 1);

   lua_getfield(LuauState, Index, "B");
   float B = luaL_checknumber(LuauState, -1);
   lua_pop(LuauState, 1);

   lua_getfield(LuauState, Index, "A");
   float A = luaL_checknumber(LuauState, -1);
   lua_pop(LuauState, 1);

   return Color(R, G, B, A);
}

bool Color::LuauOpt(lua_State* LuauState, int Index, Color* OutColor)
{
   if (OutColor && lua_gettop(LuauState) >= Index && lua_istable(LuauState, Index))
   {
      *OutColor = LuauCheck(LuauState, Index);
      return true;
   }

   return false;
}

/**
 *    Setup Color global
 */

luaL_Reg Color::Functions[] = {
   { "New", New }
};

void Color::LoadGlobal(lua_State *LuauState)
{
   lua_createtable(LuauState, 0, std::size(Functions));

   for (const luaL_Reg& Function : Functions)
   {
      lua_pushcfunction(LuauState, Function.func, Function.name);
      lua_setfield(LuauState, -2, Function.name);
   }

   lua_setglobal(LuauState, "Color");
}

}
