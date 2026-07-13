#pragma once

class lua_State;
class luaL_Reg;

namespace Luau
{

class GlobalFuncs
{
private:
   static luaL_Reg Functions[];

public:
   static void LoadGlobal(lua_State* LuauState, const char* AppName);
};

}
