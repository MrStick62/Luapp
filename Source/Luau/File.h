#pragma once

class luaL_Reg;
class lua_State;

namespace Luau
{

class File
{
private:
   static luaL_Reg Functions[];

   static int OpenDialog(lua_State* LuauState);

public:
   static void LoadGlobal(lua_State* LuauState);

};

}
