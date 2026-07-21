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

int Vec2::Lerp(lua_State* LuauState)
{
   Vec2 V1 = Vec2::LuauCheck(LuauState, 1);
   Vec2 V2 = Vec2::LuauCheck(LuauState, 2);
   float T = luaL_checknumber(LuauState, 3);

   Vec2 Result;
   Result.X = V1.X + (V2.X - V1.X) * T;
   Result.Y = V1.Y + (V2.Y - V1.Y) * T;
   Result.LuauPush(LuauState);

   return 1;
}

int Vec2::__add(lua_State* LuauState)
{
   Vec2 Self = Vec2::LuauCheck(LuauState, 1);
   Vec2 Value = Vec2::LuauCheck(LuauState, 2);

   (Self + Value).LuauPush(LuauState);

   return 1;
}

int Vec2::__sub(lua_State* LuauState)
{
   Vec2 Self = Vec2::LuauCheck(LuauState, 1);
   Vec2 Value = Vec2::LuauCheck(LuauState, 2);

   (Self - Value).LuauPush(LuauState);

   return 1;
}

int Vec2::__mul(lua_State* LuauState)
{
   Vec2 Self = Vec2::LuauCheck(LuauState, 1);
   float Value = luaL_checknumber(LuauState, 2);

   (Self * Value).LuauPush(LuauState);

   return 1;
}

int Vec2::__div(lua_State* LuauState)
{
   Vec2 Self = Vec2::LuauCheck(LuauState, 1);
   float Value = luaL_checknumber(LuauState, 2);

   (Self / Value).LuauPush(LuauState);

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

   luaL_getmetatable(LuauState, "Vec2");
   lua_setmetatable(LuauState, -2);
}

Vec2 Vec2::operator+(const Vec2& Value)
{
   return Vec2(X + Value.X, Y + Value.Y);
}

Vec2 Vec2::operator-(const Vec2& Value)
{
   return Vec2(X - Value.X, Y - Value.Y);
}

Vec2 Vec2::operator*(float Value)
{
   return Vec2(X * Value, Y * Value);
}

Vec2 Vec2::operator/(float Value)
{
   return Vec2(X / Value, Y / Value);
}

luaL_Reg Vec2::Functions[] = {
   { "New", New },
   { "Lerp", Lerp },
};

luaL_Reg Vec2::MetaFunctions[] = {
   { "__add", __add },
   { "__sub", __sub },
   { "__mul", __mul },
   { "__div", __div },
};

void Vec2::LoadGlobal(lua_State *LuauState)
{
   LuauHelp::SetupFunctionsGlobal(LuauState, Functions, std::size(Functions), "Vec2");

   luaL_newmetatable(LuauState, "Vec2");

   lua_pushvalue(LuauState, -1);
   lua_setfield(LuauState, -2, "__index");

   for (const luaL_Reg& Function : MetaFunctions)
   {
      lua_pushcfunction(LuauState, Function.func, Function.name);
      lua_setfield(LuauState, -2, Function.name);
   }

   lua_pop(LuauState, 1);
}

}
