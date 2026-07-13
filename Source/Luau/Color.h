#pragma once

#include "lualib.h"
class lua_State;

namespace Luau
{

struct Color
{
   float R, G, B, A;

   Color(float R = 0.0f, float G = 0.0f, float B = 0.0f, float A = 0.0f) : R(R), G(G), B(B), A(A) {};

   void LuauPush(lua_State* LuauState);

   static Color LuauCheck(lua_State* LuauState, int Index);
   static bool LuauOpt(lua_State* LuauState, int Index, Color* OutColor);


private:
   static luaL_Reg Functions[];

public:
   static void LoadGlobal(lua_State* LuauState);
};

}
