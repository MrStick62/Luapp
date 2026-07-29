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

   static int SetSaveFile(lua_State* LuauState);

   static int SetNextWindowSize(lua_State* LuauState);
   static int SetNextWindowPos(lua_State* LuauState);

   static int SetNextWindowSizeConstraints(lua_State* LuauState);

   static int GetWindowSize(lua_State* LuauState);
   static int GetWindowPos(lua_State* LuauState);

   static int GetCursorScreenPos(lua_State* LuauState);
   static int SetCursorScreenPos(lua_State* LuauState);
   static int GetContentRegionAvail(lua_State* LuauState);

   static int GetCursorPos(lua_State* LuauState);
   static int SetCursorPos(lua_State* LuauState);

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

   static int BeginTabBar(lua_State* LuauState);
   static int EndTabBar(lua_State* LuauState);

   static int BeginTabItem(lua_State* LuauState);
   static int EndTabItem(lua_State* LuauState);

   static int BeginTooltip(lua_State* LuauState);
   static int EndTooltip(lua_State* LuauState);
   static int SetTooltip(lua_State* LuauState);

   static int OpenPopup(lua_State* LuauState);
   static int OpenPopupOnItemClick(lua_State* LuauState);
   static int CloseCurrentPopup(lua_State* LuauState);

   static int BeginPopup(lua_State* LuauState);
   static int BeginPopupModal(lua_State* LuauState);
   static int EndPopup(lua_State* LuauState);

   static int BeginTable(lua_State* LuauState);
   static int EndTable(lua_State* LuauState);

   static int TableNextRow(lua_State* LuauState);
   static int TableNextColumn(lua_State* LuauState);
   static int TableSetColumnIndex(lua_State* LuauState);

   static int TableSetupColumn(lua_State* LuauState);
   static int TableSetupScrollFreeze(lua_State* LuauState);
   static int TableHeader(lua_State* LuauState);
   static int TableHeadersRow(lua_State* LuauState);
   static int TableAngledHeadersRow(lua_State* LuauState);

   static int TableSetBgColor(lua_State* LuauState);

   static int BeginDisabled(lua_State* LuauState);
   static int EndDisabled(lua_State* LuauState);

   static int PushID(lua_State* LuauState);
   static int PopID(lua_State* LuauState);

   static int SameLine(lua_State* LuauState);
   static int Spacing(lua_State* LuauState);
   static int Indent(lua_State* LuauState);
   static int Unindent(lua_State* LuauState);
   static int Separator(lua_State* LuauState);
   static int Bullet(lua_State* LuauState);
   static int Dummy(lua_State* LuauState);

   static int CollapsingHeader(lua_State* LuauState);

   static int Image(lua_State* LuauState);
   static int ImageWithBg(lua_State* LuauState);
   static int ImageButton(lua_State* LuauState);

   static int Text(lua_State* LuauState);
   static int SeparatorText(lua_State* LuauState);

   static int TextLink(lua_State* LuauState);
   static int TextLinkOpenURL(lua_State* LuauState);

   static int CalcTextSize(lua_State* LuauState);

   static int InputText(lua_State* LuauState);
   static int InputTextWithHint(lua_State* LuauState);
   static int InputTextMultiline(lua_State* LuauState);
   static int InputFloat(lua_State* LuauState);
   static int InputInt(lua_State* LuauState);

   static int Button(lua_State* LuauState);
   static int SmallButton(lua_State* LuauState);
   static int InvisibleButton(lua_State* LuauState);
   static int ArrowButton(lua_State* LuauState);
   static int Checkbox(lua_State* LuauState);

   static int IsItemHovered(lua_State* LuauState);

   static int Selectable(lua_State* LuauState);

   static int Combo(lua_State* LuauState);

   static int SliderFloat(lua_State* LuauState);
   static int ColorEdit(lua_State* LuauState);

   static int PlotLines(lua_State* LuauState);

   static int BeginDragDropSource(lua_State* LuauState);
   static int SetDragDropPayload(lua_State* LuauState);
   static int EndDragDropSource(lua_State* LuauState);

   static int BeginDragDropTarget(lua_State* LuauState);
   static int AcceptDragDropPayload(lua_State* LuauState);
   static int EndDragDropTarget(lua_State* LuauState);

   static int GetDragDropPayload(lua_State* LuauState);

   static void PushStyle(lua_State* LuauState, const ImGuiStyle& Style);
   static ImGuiStyle CheckStyle(lua_State* LuauState, int Index);

   static int GetCurrentFont(lua_State* LuauState);
   static int SetFont(lua_State* LuauState);

   static int PushFont(lua_State* LuauState);
   static int PopFont(lua_State* LuauState);

   static int GetCurrentStyle(lua_State* LuauState);
   static int GetDarkStyle(lua_State* LuauState);
   static int GetLightStyle(lua_State* LuauState);
   static int GetClassicStyle(lua_State* LuauState);
   static int SetStyle(lua_State* LuauState);

   static int PushStyleColor(lua_State* LuauState);
   static int PopStyleColor(lua_State* LuauState);
   static int GetStyleColorName(lua_State* LuauState);
   static int GetStyleColorValue(lua_State* LuauState);

   static int PushStyleVar(lua_State* LuauState);
   static int PopStyleVar(lua_State* LuauState);

   static int ShowDemoWindow(lua_State* LuauState);
   static int ShowIDStackToolWindow(lua_State* LuauState);
   static int ShowFontSelector(lua_State* LuauState);

   static std::pair<std::string, int> GuiColors[];
   static std::pair<std::string, int> StyleVars[];
   static std::pair<std::string, int> Directions[];
   static std::pair<std::string, int> TableBgTargets[];

   static std::pair<std::string, int> WindowFlags[];
   static std::pair<std::string, int> ChildFlags[];

   static std::pair<std::string, int> ButtonFlags[];

   static std::pair<std::string, int> SliderFlags[];
   static std::pair<std::string, int> InputTextFlags[];

   static std::pair<std::string, int> TreeNodeFlags[];

   static std::pair<std::string, int> SelectableFlags[];

   static std::pair<std::string, int> TabBarFlags[];
   static std::pair<std::string, int> TabItemFlags[];

   static std::pair<std::string, int> TableFlags[];
   static std::pair<std::string, int> TableColumnFlags[];
   static std::pair<std::string, int> TableRowFlags[];

public:
   static void LoadGlobal(lua_State* LuauState);
   static void HandleDragDrop(lua_State* LuauState);
};

}
