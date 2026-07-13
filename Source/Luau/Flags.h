#pragma once

class lua_State;
class luaL_Reg;

namespace Luau
{

class Flags {
private:
   static luaL_Reg Functions[];

   static int Unite(lua_State* LuauState);
      
public:
   static void LoadGlobal(lua_State* LuauState);
};

}
