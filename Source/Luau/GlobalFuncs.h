#pragma once

class lua_State;
class luaL_Reg;

namespace Luau
{

class GlobalFuncs
{
private:
   static luaL_Reg Functions[];

   static int Require(lua_State* LuauState);

public:
   static void LoadGlobal(lua_State* LuauState);
};

}
