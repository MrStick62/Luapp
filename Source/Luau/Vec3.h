#pragma once

class luaL_Reg;
class lua_State;

namespace Luau
{

struct Vec3
{
   float X, Y, Z;

   Vec3(float X = 0.0f, float Y = 0.0f, float Z = 0.0f) : X(X), Y(Y), Z(Z) {};

   void LuauPush(lua_State* LuauState);

   static Vec3 LuauCheck(lua_State* LuauState, int Index);
   static bool LuauOpt(lua_State* LuauState, int Index, Vec3* OutVec);

   Vec3 operator+(const Vec3& Value);
   Vec3 operator-(const Vec3& Value);
   Vec3 operator*(float Value);
   Vec3 operator/(float Value);

private:
   static luaL_Reg Functions[];
   static luaL_Reg MetaFunctions[];

   // Functions
   static int New(lua_State* LuauState);
   static int Lerp(lua_State* LuauState);

   // Meta functions
   static int __add(lua_State* LuauState);
   static int __sub(lua_State* LuauState);
   static int __mul(lua_State* LuauState);
   static int __div(lua_State* LuauState);

public:
   static void LoadGlobal(lua_State* LuauState);
};

}
