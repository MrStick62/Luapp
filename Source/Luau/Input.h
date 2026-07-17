#pragma once

#include <string>
#include <utility>

class luaL_Reg;
class lua_State;

namespace Luau
{

class Input
{
private:
   static luaL_Reg Functions[];

   static int IsKeyDown(lua_State* LuauState);
   static int IsKeyPressed(lua_State* LuauState);
   static int IsKeyReleased(lua_State* LuauState);

   static int Shortcut(lua_State* LuauState);
   static int SetNextItemShortcut(lua_State* LuauState);

   static int GetClipboardText(lua_State* LuauState);
   static int SetClipboardText(lua_State* LuauState);

   static std::pair<std::string, int> Keys[];
   static std::pair<std::string, int> Mods[];
   static std::pair<std::string, int> Flags[];

public:
   static void LoadGlobal(lua_State* LuauState);

};

}
