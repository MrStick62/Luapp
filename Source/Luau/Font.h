#pragma once

class luaL_Reg;
class lua_State;

class ImFont;

namespace Luau
{

class Font
{
private:
   static luaL_Reg Functions[];
   static luaL_Reg MetaFunctions[];

   static int LoadNew(lua_State* LuauState);
   static int GetAll(lua_State* LuauState);

   static void AddDefaultIcons();

public:
   static void LoadGlobal(lua_State* LuauState);

   static void LuauPush(lua_State* LuauState, ImFont* Font);
   static ImFont* LuauCheck(lua_State* LuauState, int Index);

};

}
