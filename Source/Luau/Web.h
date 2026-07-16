#pragma once

#include <string>

class luaL_Reg;
class lua_State;

namespace Luau
{

class Web
{
private:
   static luaL_Reg Functions[];

   static bool IsURL(const std::string& URL);
   static int OpenPage(lua_State* LuauState);
   static int ConnectToSystem(lua_State* LuauState);

public:
   static void LoadGlobal(lua_State* LuauState);

};

}
