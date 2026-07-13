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

public:
   static void LoadGlobal(lua_State* LuauState);
};

}
