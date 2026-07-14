#include "Gui.h"

#include <array>
#include <cstring>
#include <sstream>
#include <string.h>
#include <iostream>

#include <lua.h>
#include <lualib.h>
#include <luacode.h>

#include <imgui/imgui.h>

#include "Vec2.h"
#include "Color.h"

namespace Luau
{

/**
 *    Luau function C++ implementations
 */

int Gui::SetNextWindowSize(lua_State* LuauState)
{
   Vec2 Size = Vec2::LuauCheck(LuauState, 1);

   ImGui::SetNextWindowSize(ImVec2(Size.X, Size.Y), ImGuiCond_Always);

   return 0;
}

int Gui::SetNextWindowPos(lua_State* LuauState)
{
   Vec2 Pos = Vec2::LuauCheck(LuauState, 1);

   ImGui::SetNextWindowPos(ImVec2(Pos.X, Pos.Y), ImGuiCond_Always);

   return 0;
}

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

int Gui::BeginChild(lua_State* LuauState)
{
   const char* ID = luaL_checkstring(LuauState, 1);
   Vec2 Size = Vec2::LuauCheck(LuauState, 2);
   ImGuiChildFlags ChildFlags = luaL_optinteger(LuauState, 3, 0);
   ImGuiWindowFlags WindowFlags = luaL_optinteger(LuauState, 4, 0);

   lua_pushboolean(LuauState, ImGui::BeginChild(ID, ImVec2(Size.X, Size.Y), ChildFlags, WindowFlags));

   return 1;
}

int Gui::EndChild(lua_State* LuauState)
{
   ImGui::EndChild();

   return 0;
}

int Gui::BeginMainMenuBar(lua_State* LuauState)
{
   lua_pushboolean(LuauState, ImGui::BeginMainMenuBar());

   return 1;
}

int Gui::EndMainMenuBar(lua_State* LuauState)
{
   ImGui::EndMainMenuBar();

   return 0;
}

int Gui::BeginMenuBar(lua_State* LuauState)
{
   lua_pushboolean(LuauState, ImGui::BeginMenuBar());

   return 1;
}

int Gui::EndMenuBar(lua_State* LuauState)
{
   ImGui::EndMenuBar();

   return 0;
}

int Gui::BeginMenu(lua_State* LuauState)
{
   const char* Label = luaL_checkstring(LuauState, 1);
   bool Enabled = luaL_optboolean(LuauState, 2, true);

   lua_pushboolean(LuauState, ImGui::BeginMenu(Label, Enabled));

   return 1;
}

int Gui::EndMenu(lua_State* LuauState)
{
   ImGui::EndMenu();

   return 0;
}

int Gui::MenuItem(lua_State* LuauState)
{
   const char* Label = luaL_checkstring(LuauState, 1);
   const char* Shortcut = luaL_optstring(LuauState, 2, nullptr);
   bool Selected = luaL_optboolean(LuauState, 3, false);
   bool Enabled = luaL_optboolean(LuauState, 4, true);

   lua_pushboolean(LuauState, ImGui::MenuItem(Label, Shortcut, Enabled));

   return 1;
}

int Gui::BeginDisabled(lua_State* LuauState)
{
   ImGui::BeginDisabled();

   return 0;
}

int Gui::EndDisabled(lua_State* LuauState)
{
   ImGui::EndDisabled();

   return 0;
}

int Gui::PushID(lua_State* LuauState)
{
   const char* ID = luaL_checkstring(LuauState, 1);

   ImGui::PushID(ID);

   return 0;
}

int Gui::PopID(lua_State* LuauState)
{
   ImGui::PopID();

   return 0;
}

int Gui::SameLine(lua_State* LuauState)
{
   int Offset = luaL_optnumber(LuauState, 1, 0.0f);
   int Spacing = luaL_optnumber(LuauState, 2, -1.0f);

   ImGui::SameLine(Offset, Spacing);

   return 0;
}

int Gui::Spacing(lua_State* LuauState)
{
   int Spaces = luaL_optinteger(LuauState, 1, 1);

   for (int i = 0; i < Spaces; i++)
      ImGui::Spacing();

   return 0;
}

int Gui::Separator(lua_State* LuauState)
{
   ImGui::Separator();

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

int Gui::SliderFloat(lua_State* LuauState)
{
   const char* Label = luaL_checkstring(LuauState, 1);
   float Value = luaL_checknumber(LuauState, 2);
   float Min = luaL_checknumber(LuauState, 3);
   float Max = luaL_checknumber(LuauState, 4);
   int Precision = luaL_optinteger(LuauState, 5, 2);
   ImGuiSliderFlags Flags = luaL_optinteger(LuauState, 6, 0);

   std::stringstream Format;
   Format << "%." << Precision << "f";

   ImGui::SliderFloat(Label, &Value, Min, Max, Format.str().c_str(), Flags);

   lua_pushnumber(LuauState, Value);

   return 1;
}

int Gui::ColorEdit(lua_State* LuauState)
{
   const char* Label = luaL_checkstring(LuauState, 1);
   Color InputColor = Color::LuauCheck(LuauState, 2);

   float ColorArray[] = {
      InputColor.R, InputColor.G, InputColor.B, InputColor.A
   };

   ImGui::ColorEdit4(Label, ColorArray);

   Color OutColor(ColorArray[0], ColorArray[1], ColorArray[2], ColorArray[3]);
   OutColor.LuauPush(LuauState);

   return 1;
}

/*
 *    Gui class
 */

luaL_Reg Gui::Functions[] = {
   { "SetNextWindowSize", SetNextWindowSize },
   { "SetNextWindowPos", SetNextWindowPos },

   { "Begin", Begin },
   { "End", End },

   { "BeginChild", BeginChild },
   { "EndChild", EndChild },

   { "BeginMainMenuBar", BeginMainMenuBar },
   { "EndMainMenuBar", EndMainMenuBar },

   { "BeginMenuBar", BeginMenuBar },
   { "EndMenuBar", EndMenuBar },

   { "BeginMenu", BeginMenu },
   { "EndMenu", EndMenu },

   { "MenuItem", MenuItem },

   { "BeginDisabled", BeginDisabled },
   { "EndDisabled", EndDisabled },

   { "PushID", PushID },
   { "PopID", PopID },

   { "SameLine", SameLine },
   { "Spacing", Spacing },
   { "Separator", Separator },

   { "Text", Text },
   { "SeparatorText", Text },
   { "InputText", InputText },

   { "Button", Button },
   { "Checkbox", Checkbox },

   { "SliderFloat", SliderFloat },
   { "ColorEdit", ColorEdit },
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

std::pair<std::string, int> Gui::ChildFlags[] = {
   { "None", ImGuiChildFlags_None },
   { "Borders", ImGuiChildFlags_Borders },
   { "AlwaysUseWindowPadding", ImGuiChildFlags_AlwaysUseWindowPadding },
   { "ResizeX", ImGuiChildFlags_ResizeX },
   { "ResizeY", ImGuiChildFlags_ResizeY },
   { "AutoResizeX", ImGuiChildFlags_AutoResizeX },
   { "AutoResizeY", ImGuiChildFlags_AutoResizeY },
   { "AlwaysAutoResize", ImGuiChildFlags_AlwaysAutoResize },
   { "FrameStyle", ImGuiChildFlags_FrameStyle },
   { "NavFlattened", ImGuiChildFlags_NavFlattened },
};

std::pair<std::string, int> Gui::SliderFlags[] = {
   { "None", ImGuiSliderFlags_None },
   { "Logarithmic", ImGuiSliderFlags_Logarithmic },
   { "NoRoundToFormat", ImGuiSliderFlags_NoRoundToFormat },
   { "NoInput", ImGuiSliderFlags_NoInput },
   { "WrapAround", ImGuiSliderFlags_WrapAround },
   { "ClampOnInput", ImGuiSliderFlags_ClampOnInput },
   { "ClampZeroRange", ImGuiSliderFlags_ClampZeroRange },
   { "NoSpeedTweaks", ImGuiSliderFlags_NoSpeedTweaks },
   { "ColorMarkers", ImGuiSliderFlags_ColorMarkers },
   { "AlwaysClamp", ImGuiSliderFlags_AlwaysClamp },
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
      lua_pushinteger(LuauState, Flag.second);
      lua_setfield(LuauState, -2, Flag.first.data());
   }

   lua_setglobal(LuauState, "GuiWindowFlags");

   // Gui window flags table
   lua_createtable(LuauState, 0, std::size(ChildFlags));

   for (auto Flag : ChildFlags)
   {
      lua_pushinteger(LuauState, Flag.second);
      lua_setfield(LuauState, -2, Flag.first.data());
   }

   lua_setglobal(LuauState, "GuiChildFlags");

   // Gui slider flags table
   lua_createtable(LuauState, 0, std::size(SliderFlags));

   for (auto Flag : SliderFlags)
   {
      lua_pushinteger(LuauState, Flag.second);
      lua_setfield(LuauState, -2, Flag.first.data());
   }

   lua_setglobal(LuauState, "GuiSliderFlags");
}

}
