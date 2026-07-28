#pragma once

#include <string>
#include <vector>
#include <unordered_map>

class luaL_Reg;
class lua_State;

namespace Luau
{

class File
{
private:
   static luaL_Reg Functions[];

   static int OpenDialog(lua_State* LuauState);

   static void DialogThread(std::string ID, std::vector<std::pair<const char*, const char*>> Filters);

   static std::unordered_map<std::string, const char*> OpenDialogs;

public:
   static void LoadGlobal(lua_State* LuauState);

};

}
