#include "Vec3.h"

#include <array>

#include <lua.h>
#include <lualib.h>
#include <luacode.h>

#include "LuauHelp.h"

namespace Luau
{

int Vec3::New(lua_State* LuauState)
{
   float X = luaL_checknumber(LuauState, 1);
   float Y = luaL_checknumber(LuauState, 2);
   float Z = luaL_checknumber(LuauState, 3);

   Vec3 Vec3(X, Y, Z);
   Vec3.LuauPush(LuauState);

   return 1;
}

int Vec3::Lerp(lua_State* LuauState)
{
   Vec3 V1 = Vec3::LuauCheck(LuauState, 1);
   Vec3 V2 = Vec3::LuauCheck(LuauState, 2);
   float T = luaL_checknumber(LuauState, 3);

   Vec3 Result;
   Result.X = V1.X + (V2.X - V1.X) * T;
   Result.Y = V1.Y + (V2.Y - V1.Y) * T;
   Result.Z = V1.Z + (V2.Z - V2.Z) * T;
   Result.LuauPush(LuauState);

   return 1;
}

int Vec3::__add(lua_State* LuauState)
{
   Vec3 Self = Vec3::LuauCheck(LuauState, 1);
   Vec3 Value = Vec3::LuauCheck(LuauState, 2);

   (Self + Value).LuauPush(LuauState);

   return 1;
}

int Vec3::__sub(lua_State* LuauState)
{
   Vec3 Self = Vec3::LuauCheck(LuauState, 1);
   Vec3 Value = Vec3::LuauCheck(LuauState, 2);

   (Self - Value).LuauPush(LuauState);

   return 1;
}

int Vec3::__mul(lua_State* LuauState)
{
   Vec3 Self = Vec3::LuauCheck(LuauState, 1);
   float Value = luaL_checknumber(LuauState, 2);

   (Self * Value).LuauPush(LuauState);

   return 1;
}

int Vec3::__div(lua_State* LuauState)
{
   Vec3 Self = Vec3::LuauCheck(LuauState, 1);
   float Value = luaL_checknumber(LuauState, 2);

   (Self / Value).LuauPush(LuauState);

   return 1;
}


Vec3 Vec3::LuauCheck(lua_State *LuauState, int Index)
{
   luaL_checktype(LuauState, Index, LUA_TTABLE);

   lua_getfield(LuauState, Index, "X");
   float X = luaL_checknumber(LuauState, -1);
   lua_pop(LuauState, 1);

   lua_getfield(LuauState, Index, "Y");
   float Y = luaL_checknumber(LuauState, -1);
   lua_pop(LuauState, 1);

   lua_getfield(LuauState, Index, "Z");
   float Z = luaL_checknumber(LuauState, -1);
   lua_pop(LuauState, 1);

   return Vec3(X, Y);
}

bool Vec3::LuauOpt(lua_State *LuauState, int Index, Vec3 *OutVec)
{
   if (OutVec && lua_gettop(LuauState) >= Index && lua_istable(LuauState, Index))
   {
      *OutVec = LuauCheck(LuauState, Index);
      return true;
   }

   return false;
}

void Vec3::LuauPush(lua_State* LuauState)
{
   lua_createtable(LuauState, 0, 2);

   lua_pushnumber(LuauState, X);
   lua_setfield(LuauState, -2, "X");

   lua_pushnumber(LuauState, Y);
   lua_setfield(LuauState, -2, "Y");

   lua_pushnumber(LuauState, Z);
   lua_setfield(LuauState, -2, "Z");

   luaL_getmetatable(LuauState, "Vec3");
   lua_setmetatable(LuauState, -2);
}

Vec3 Vec3::operator+(const Vec3& Value)
{
   return Vec3(X + Value.X, Y + Value.Y, Z + Value.Z);
}

Vec3 Vec3::operator-(const Vec3& Value)
{
   return Vec3(X - Value.X, Y - Value.Y, Z - Value.Z);
}

Vec3 Vec3::operator*(float Value)
{
   return Vec3(X * Value, Y * Value, Z * Value);
}

Vec3 Vec3::operator/(float Value)
{
   return Vec3(X / Value, Y / Value, Z / Value);
}

luaL_Reg Vec3::Functions[] = {
   { "New", New },
   { "Lerp", Lerp },
};

luaL_Reg Vec3::MetaFunctions[] = {
   { "__add", __add },
   { "__sub", __sub },
   { "__mul", __mul },
   { "__div", __div },
};

void Vec3::LoadGlobal(lua_State *LuauState)
{
   LuauHelp::SetupFunctionsGlobal(LuauState, Functions, std::size(Functions), "Vec3");

   luaL_newmetatable(LuauState, "Vec3");

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
