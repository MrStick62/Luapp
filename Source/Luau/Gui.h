#pragma once

#include <string>
#include <utility>

class luaL_Reg;
class lua_State;
class ImGuiStyle;

namespace Luau
{

class Gui
{
private:
   static luaL_Reg Functions[];

   static int SetNextWindowSize(lua_State* LuauState);
   static int SetNextWindowPos(lua_State* LuauState);

   static int Begin(lua_State* LuauState);
   static int End(lua_State* LuauState);

   static int BeginChild(lua_State* LuauState);
   static int EndChild(lua_State* LuauState);

   static int BeginMainMenuBar(lua_State* LuauState);
   static int EndMainMenuBar(lua_State* LuauState);

   static int BeginMenuBar(lua_State* LuauState);
   static int EndMenuBar(lua_State* LuauState);

   static int BeginMenu(lua_State* LuauState);
   static int EndMenu(lua_State* LuauState);

   static int MenuItem(lua_State* LuauState);
   static int BeginPopup(lua_State* LuauState);
   static int EndPopup(lua_State* LuauState);

   static int BeginDisabled(lua_State* LuauState);
   static int EndDisabled(lua_State* LuauState);

   static int PushID(lua_State* LuauState);
   static int PopID(lua_State* LuauState);

   static int SameLine(lua_State* LuauState);
   static int Spacing(lua_State* LuauState);
   static int Indent(lua_State* LuauState);
   static int Unindent(lua_State* LuauState);
   static int Separator(lua_State* LuauState);

   static int CollapsingHeader(lua_State* LuauState);

   static int Text(lua_State* LuauState);
   static int SeparatorText(lua_State* LuauState);

   static int InputText(lua_State* LuauState);
   static int InputTextMultiline(lua_State* LuauState);

   static int Button(lua_State* LuauState);
   static int Checkbox(lua_State* LuauState);

   static int SliderFloat(lua_State* LuauState);
   static int ColorEdit(lua_State* LuauState);

   static int PlotLines(lua_State* LuauState);

   static void PushStyle(lua_State* LuauState, const ImGuiStyle& Style);
   static ImGuiStyle CheckStyle(lua_State* LuauState, int Index);

   static int GetCurrentStyle(lua_State* LuauState);
   static int GetDarkStyle(lua_State* LuauState);
   static int GetLightStyle(lua_State* LuauState);
   static int GetClassicStyle(lua_State* LuauState);
   static int SetStyle(lua_State* LuauState);

   static int PushStyleColor(lua_State* LuauState);
   static int PopStyleColor(lua_State* LuauState);
   static int GetStyleColorName(lua_State* LuauState);

   static int ShowDemoWindow(lua_State* LuauState);

   static std::pair<std::string, int> GuiColors[];

   static std::pair<std::string, int> WindowFlags[];
   static std::pair<std::string, int> ChildFlags[];
   static std::pair<std::string, int> SliderFlags[];
   static std::pair<std::string, int> InputTextFlags[];
   static std::pair<std::string, int> TreeNodeFlags[];

public:
   static void LoadGlobal(lua_State* LuauState);
};

}
