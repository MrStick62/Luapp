#include "Input.h"

#include <array>

#include <lua.h>
#include <lualib.h>
#include <luacode.h>

#include <imgui/imgui.h>

namespace Luau
{

int Input::IsKeyDown(lua_State* LuauState)
{
   ImGuiKey Key = static_cast<ImGuiKey>(luaL_checkinteger(LuauState, 1));

   lua_pushboolean(LuauState, ImGui::IsKeyDown(Key));

   return 1;
}

int Input::IsKeyPressed(lua_State* LuauState)
{
   ImGuiKey Key = static_cast<ImGuiKey>(luaL_checkinteger(LuauState, 1));

   lua_pushboolean(LuauState, ImGui::IsKeyPressed(Key));

   return 1;
}

int Input::IsKeyReleased(lua_State* LuauState)
{
   ImGuiKey Key = static_cast<ImGuiKey>(luaL_checkinteger(LuauState, 1));

   lua_pushboolean(LuauState, ImGui::IsKeyReleased(Key));

   return 1;
}


luaL_Reg Input::Functions[] = {
   { "IsKeyDown", IsKeyDown },
   { "IsKeyPressed", IsKeyPressed },
   { "IsKeyReleased", IsKeyReleased },
};

std::pair<std::string, int> Input::Keys[] = {
   { "None", ImGuiKey_None },
};

void Input::LoadGlobal(lua_State *LuauState)
{
   // Init functions
   lua_createtable(LuauState, 0, std::size(Functions));

   for (const luaL_Reg& Function : Functions)
   {
      lua_pushcfunction(LuauState, Function.func, Function.name);
      lua_setfield(LuauState, -2, Function.name);
   }

   lua_setglobal(LuauState, "Input");

   // Init key enum list
   lua_createtable(LuauState, 0, std::size(Keys));

   for (const auto& Key : Keys)
   {
      lua_pushinteger(LuauState, Key.second);
      lua_setfield(LuauState, -2, Key.first.data());
   }

   lua_setglobal(LuauState, "InputKey");
}

}
