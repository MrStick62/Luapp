#pragma once

#include <string>
#include <utility>

class luaL_Reg;
class lua_State;

namespace Luau
{

class Icons
{
private:
    static std::pair<const char*, const char*> IconsList[];

public:
    static void LoadGlobal(lua_State* LuauState);
};


}