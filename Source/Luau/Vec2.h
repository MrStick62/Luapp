#pragma once

class luaL_Reg;
class lua_State;

namespace Luau
{

struct Vec2
{
   float X, Y;

   Vec2(float X = 0.0f, float Y = 0.0f) : X(X), Y(Y) {};

   void LuauPush(lua_State* LuauState);

   static Vec2 LuauCheck(lua_State* LuauState, int Index);
   static bool LuauOpt(lua_State* LuauState, int Index, Vec2* OutVec);

   Vec2 operator+(const Vec2& Value);
   Vec2 operator-(const Vec2& Value);
   Vec2 operator*(float Value);
   Vec2 operator/(float Value);

private:
   static luaL_Reg Functions[];
   static luaL_Reg MetaFunctions[];

   // Functions
   static int New(lua_State* LuauState);

   // Meta functions
   static int __add(lua_State* LuauState);
   static int __sub(lua_State* LuauState);
   static int __mul(lua_State* LuauState);
   static int __div(lua_State* LuauState);

public:
   static void LoadGlobal(lua_State* LuauState);
};

}
