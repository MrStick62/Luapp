#pragma once

class luaL_Reg;
class lua_State;

namespace Luau
{

class Config
{
private:
   static luaL_Reg Functions[];

   static int Save(lua_State* LuauState);

   static void PushData(lua_State* LuauState);

public:
   static void LoadGlobal(lua_State* LuauState);

};

}
