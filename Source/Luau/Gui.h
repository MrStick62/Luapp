#pragma once

#include <string>
#include <utility>

class lua_State;
class luaL_Reg;

namespace Luau
{

class Gui
{
private:
   static luaL_Reg Functions[];
   static std::pair<std::string, int> WindowFlags[];

   static int Begin(lua_State* LuauState);
   static int End(lua_State* LuauState);

   static int Text(lua_State* LuauState);
   static int SeparatorText(lua_State* LuauState);
   static int InputText(lua_State* LuauState);

   static int Button(lua_State* LuauState);
   static int Checkbox(lua_State* LuauState);

public:
   static void LoadGlobal(lua_State* LuauState);
};

}
