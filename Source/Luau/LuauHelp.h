#pragma once

#include <string>
#include <utility>

class luaL_Reg;
class lua_State;

namespace Luau::LuauHelp
{

void SetupFunctionsGlobal(lua_State* LuauState, luaL_Reg Functions[], size_t Size, const char* GlobalName);
void SetupEnumGlobal(lua_State* LuauState, std::pair<std::string, int> Table[], size_t Size, const char* GlobalName, int Offset = 0);

}
