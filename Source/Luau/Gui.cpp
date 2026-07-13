#include "Gui.h"

#include <array>
#include <cstring>

#include <lua.h>
#include <lualib.h>
#include <luacode.h>

#include <imgui/imgui.h>

#include "Color.h"


namespace Luau
{

/**
 *    Luau function C++ implementations
 */

int Gui::Begin(lua_State* LuauState)
{
   const char* Name = luaL_checkstring(LuauState, 1);
   int IsOpen = luaL_optboolean(LuauState, 2, -1);
   ImGuiWindowFlags Flags = luaL_optinteger(LuauState, 3, 0);

   bool Begin = ImGui::Begin(Name, (IsOpen == -1) ? nullptr : (bool*)&IsOpen, Flags);
   lua_pushboolean(LuauState, Begin);
   lua_pushboolean(LuauState, (IsOpen == -1) ? true : IsOpen);

   return 2;
}

int Gui::End(lua_State* LuauState)
{
   ImGui::End();

   return 0;
}

int Gui::Text(lua_State* LuauState)
{
   const char* Text = luaL_checkstring(LuauState, 1);

   Color Color;
   if (Color::LuauOpt(LuauState, 2, &Color))
   {
      ImGui::TextColored(*(ImVec4*)&Color, "%s", Text);
   }
   else 
   {
      ImGui::Text("%s", Text);
   }

   return 0;
}

int Gui::SeparatorText(lua_State* LuauState)
{
   const char* Label = luaL_checkstring(LuauState, 1);

   ImGui::SeparatorText(Label);

   return 0;
}

int Gui::InputText(lua_State* LuauState)
{
   const char* Label = luaL_checkstring(LuauState, 1);
   const char* Input = luaL_checkstring(LuauState, 2);

   char Buffer[1024];
   strcpy(Buffer, Input);

   if (ImGui::InputText(Label, Buffer, strlen(Buffer)))
   {
      lua_pushstring(LuauState, Buffer);
   }
   else 
   {
      lua_pushstring(LuauState, Input);
   }

   return 1;
}

int Gui::Button(lua_State* LuauState)
{
   const char* Label = luaL_checkstring(LuauState, 1);

   lua_pushboolean(LuauState, ImGui::Button(Label));

   return 1;
}

int Gui::Checkbox(lua_State* LuauState)
{
   const char* Label = luaL_checkstring(LuauState, 1);
   bool Checked = luaL_checkboolean(LuauState, 2);

   ImGui::Checkbox(Label, &Checked);

   lua_pushboolean(LuauState, Checked);

   return 1;
}

/*
 *    Gui class
 */

luaL_Reg Gui::Functions[] = {
   { "Begin", Begin },
   { "End", End },

   { "Text", Text },
   { "SeparatorText", Text },
   { "InputText", InputText },

   { "Button", Button },
   { "Checkbox", Checkbox },
};

std::pair<std::string, int> Gui::WindowFlags[] = {
   { "None", ImGuiWindowFlags_None },
   { "NoTitleBar", ImGuiWindowFlags_NoTitleBar },
   { "NoResize", ImGuiWindowFlags_NoResize },
   { "NoMove", ImGuiWindowFlags_NoMove },
   { "NoScrollbar", ImGuiWindowFlags_NoScrollbar},
   { "NoScrollWithMouse", ImGuiWindowFlags_NoScrollWithMouse },
   { "NoCollapse", ImGuiWindowFlags_NoCollapse },
   { "AlwaysAutoResize", ImGuiWindowFlags_AlwaysAutoResize },
   { "NoBackground", ImGuiWindowFlags_NoBackground },
   { "NoSavedSettings", ImGuiWindowFlags_NoSavedSettings },
   { "NoMouseInputs", ImGuiWindowFlags_NoMouseInputs },
   { "MenuBar", ImGuiWindowFlags_MenuBar },
   { "HorizontalScrollbar", ImGuiWindowFlags_HorizontalScrollbar },
   { "NoFocusOnAppearing", ImGuiWindowFlags_NoFocusOnAppearing },
   { "NoBringToFrontOnFocus", ImGuiWindowFlags_NoBringToFrontOnFocus },
   { "AlwaysVerticalScrollbar", ImGuiWindowFlags_AlwaysVerticalScrollbar },
   { "AlwaysHorizontalScrollbar", ImGuiWindowFlags_AlwaysHorizontalScrollbar },
   { "NoNavInputs", ImGuiWindowFlags_NoNavInputs },
   { "NoNavFocus", ImGuiWindowFlags_NoNavFocus },
   { "UnsavedDocument", ImGuiWindowFlags_UnsavedDocument },
   { "NoNav", ImGuiWindowFlags_NoNav },
   { "NoDecoration", ImGuiWindowFlags_NoDecoration },
   { "NoInputs", ImGuiWindowFlags_NoInputs },
};

void Gui::LoadGlobal(lua_State* LuauState)
{
   // Gui table
   lua_createtable(LuauState, 0, std::size(Functions));

   for (luaL_Reg Function : Functions)
   {
      lua_pushcfunction(LuauState, Function.func, Function.name);
      lua_setfield(LuauState, -2, Function.name);
   }
   
   lua_setglobal(LuauState, "Gui");


   // Gui window flags table
   lua_createtable(LuauState, 0, std::size(WindowFlags));

   for (auto Flag : WindowFlags)
   {
      lua_pushnumber(LuauState, Flag.second);
      lua_setfield(LuauState, -2, Flag.first.data());
   }

   lua_setglobal(LuauState, "GuiWindowFlags");
}

}
