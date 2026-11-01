#include "Gui.h"

#include <array>
#include <cstdlib>
#include <cstring>
#include <sstream>
#include <string.h>
#include <iostream>

#include <lua.h>
#include <lualib.h>
#include <luacode.h>

#include <imgui/imgui.h>

#include <glad/gl.h>

#include "Vec2.h"
#include "Font.h"
#include "Color.h"
#include "LuauHelp.h"

#include "../App.h"
#include "../FileHelp.h"

namespace Luau
{

/**
 *    Luau function C++ implementations
 */

int Gui::SetSaveFile(lua_State* LuauState)
{
   static std::string Filename;
   Filename = (App::GetPath() / luaL_checkstring(LuauState, 1)).string();

   ImGuiIO& IO = ImGui::GetIO();
   IO.IniFilename = Filename.data();

   ImGui::LoadIniSettingsFromDisk(IO.IniFilename);

   return 0;
}

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

int Gui::SetNextWindowFocus(lua_State* LuauState)
{
   ImGui::SetNextWindowFocus();

   return 0;
}

int Gui::SetNextWindowSizeConstraints(lua_State* LuauState)
{
   Vec2 Min = Vec2::LuauCheck(LuauState, 1);
   Vec2 Max = Vec2::LuauCheck(LuauState, 2);

   ImGui::SetNextWindowSizeConstraints(ImVec2(Min.X, Min.Y), ImVec2(Max.X, Max.Y));

   return 0;
}

int Gui::GetWindowSize(lua_State* LuauState)
{
   ImVec2 ImSize = ImGui::GetWindowSize();

   Vec2(ImSize.x, ImSize.y).LuauPush(LuauState);

   return 1;
}

int Gui::GetWindowPos(lua_State* LuauState)
{
   ImVec2 ImPos = ImGui::GetWindowPos();

   Vec2(ImPos.x, ImPos.y).LuauPush(LuauState);

   return 1;
}

int Gui::GetCursorScreenPos(lua_State* LuauState)
{
   ImVec2 ImPos = ImGui::GetCursorScreenPos();

   Vec2(ImPos.x, ImPos.y).LuauPush(LuauState);

   return 1;
}

int Gui::SetCursorScreenPos(lua_State* LuauState)
{
   Vec2 Pos = Vec2::LuauCheck(LuauState, 1);

   ImGui::SetCursorScreenPos(ImVec2(Pos.X, Pos.Y));

   return 0;
}

int Gui::GetContentRegionAvail(lua_State* LuauState)
{
   ImVec2 ImSize = ImGui::GetContentRegionAvail();

   Vec2(ImSize.x, ImSize.y).LuauPush(LuauState);

   return 1;
}

int Gui::GetCursorPos(lua_State* LuauState)
{
   ImVec2 ImPos = ImGui::GetCursorPos();

   Vec2(ImPos.x, ImPos.y).LuauPush(LuauState);

   return 1;
}

int Gui::SetCursorPos(lua_State* LuauState)
{
   Vec2 Pos = Vec2::LuauCheck(LuauState, 1);

   ImGui::SetCursorPos(ImVec2(Pos.X, Pos.Y));

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

   lua_pushboolean(LuauState, ImGui::MenuItem(Label, Shortcut, Selected, Enabled));

   return 1;
}

int Gui::BeginTabBar(lua_State* LuauState)
{
   const char* ID = luaL_checkstring(LuauState, 1);
   ImGuiTabBarFlags Flags = luaL_optinteger(LuauState, 2, 0);

   lua_pushboolean(LuauState, ImGui::BeginTabBar(ID, Flags));

   return 1;
}

int Gui::EndTabBar(lua_State* LuauState)
{
   ImGui::EndTabBar();

   return 0;
}

int Gui::BeginTabItem(lua_State* LuauState)
{
   const char* Label = luaL_checkstring(LuauState, 1);
   int IsOpen = luaL_optboolean(LuauState, 2, -1);
   ImGuiTabItemFlags Flags = luaL_optinteger(LuauState, 3, 0);

   lua_pushboolean(LuauState, ImGui::BeginTabItem(Label, IsOpen == -1 ? nullptr : (bool*)&IsOpen, Flags));
   lua_pushboolean(LuauState, IsOpen == -1 ? true : IsOpen);

   return 2;
}

int Gui::EndTabItem(lua_State* LuauState)
{
   ImGui::EndTabItem();

   return 0;
}

int Gui::BeginTooltip(lua_State* LuauState)
{
   lua_pushboolean(LuauState, ImGui::BeginTooltip());

   return 1;
}

int Gui::EndTooltip(lua_State* LuauState)
{
   ImGui::EndTooltip();

   return 0;
}

int Gui::SetTooltip(lua_State* LuauState)
{
   const char* Text = luaL_checkstring(LuauState, 1);

   ImGui::SetTooltip("%s", Text);

   return 0;
}

int Gui::OpenPopup(lua_State* LuauState)
{
   const char* ID = luaL_checkstring(LuauState, 1);
   ImGuiPopupFlags Flags = luaL_optinteger(LuauState, 2, 0);

   ImGui::OpenPopup(ID, Flags);

   return 0;
}

int Gui::OpenPopupOnItemClick(lua_State* LuauState)
{
   const char* ID = luaL_checkstring(LuauState, 1);
   ImGuiPopupFlags Flags = luaL_optinteger(LuauState, 2, 0);

   ImGui::OpenPopupOnItemClick(ID, Flags);

   return 0;
}

int Gui::CloseCurrentPopup(lua_State* LuauState)
{
   ImGui::CloseCurrentPopup();

   return 0;
}

int Gui::BeginPopup(lua_State* LuauState)
{
   const char* ID = luaL_checkstring(LuauState, 1);
   ImGuiWindowFlags Flags = luaL_optinteger(LuauState, 2, 0);

   lua_pushboolean(LuauState, ImGui::BeginPopup(ID, Flags));

   return 1;
}

int Gui::BeginPopupModal(lua_State* LuauState)
{
   const char* Name = luaL_checkstring(LuauState, 1);
   int IsOpen = luaL_optboolean(LuauState, 2, -1);
   ImGuiWindowFlags Flags = luaL_optinteger(LuauState, 3, 0);

   lua_pushboolean(LuauState, ImGui::BeginPopupModal(Name, IsOpen == -1 ? nullptr : (bool*)&IsOpen, Flags));
   lua_pushboolean(LuauState, IsOpen == -1 ? true : IsOpen);

   return 2;
}

int Gui::EndPopup(lua_State* LuauState)
{
   ImGui::EndPopup();

   return 0;
}

int Gui::BeginTable(lua_State* LuauState)
{
   const char* ID = luaL_checkstring(LuauState, 1);
   int Columns = luaL_checkinteger(LuauState, 2);
   ImGuiTableFlags Flags = luaL_optinteger(LuauState, 3, 0);

   Vec2 OuterSize(0.0f, 0.0f);
   Vec2::LuauOpt(LuauState, 4, &OuterSize);

   float InnerWidth = luaL_optnumber(LuauState, 5, 0.0f);

   lua_pushboolean(LuauState, ImGui::BeginTable(ID, Columns, Flags, ImVec2(OuterSize.X, OuterSize.Y), InnerWidth));

   return 1;
}

int Gui::EndTable(lua_State* LuauState)
{
   ImGui::EndTable();

   return 0;
}

int Gui::TableNextRow(lua_State* LuauState)
{
   ImGuiTableRowFlags Flags = luaL_optinteger(LuauState, 1, 0);
   float MinRowHeight = luaL_optnumber(LuauState, 2, 0.0f);

   ImGui::TableNextRow(Flags, MinRowHeight);

   return 0;
}

int Gui::TableNextColumn(lua_State* LuauState)
{
   lua_pushboolean(LuauState, ImGui::TableNextColumn());

   return 1;
}

int Gui::TableSetColumnIndex(lua_State* LuauState)
{
   int Index = luaL_checkinteger(LuauState, 1);

   lua_pushboolean(LuauState, ImGui::TableSetColumnIndex(Index));

   return 1;
}

int Gui::TableSetupColumn(lua_State* LuauState)
{
   const char* Label = luaL_checkstring(LuauState, 1);
   ImGuiTableColumnFlags Flags = luaL_optinteger(LuauState, 2, 0);
   float InitWidth = luaL_optnumber(LuauState, 3, 0.0f);

   ImGui::TableSetupColumn(Label, Flags, InitWidth);

   return 0;
}

int Gui::TableSetupScrollFreeze(lua_State* LuauState)
{
   int Columns = luaL_checkinteger(LuauState, 1);
   int Rows = luaL_checkinteger(LuauState, 2);

   ImGui::TableSetupScrollFreeze(Columns, Rows);

   return 0;
}

int Gui::TableHeader(lua_State* LuauState)
{
   const char* Label = luaL_checkstring(LuauState, 1);

   ImGui::TableHeader(Label);

   return 0;
}

int Gui::TableHeadersRow(lua_State* LuauState)
{
   ImGui::TableHeadersRow();

   return 0;
}

int Gui::TableAngledHeadersRow(lua_State* LuauState)
{
   ImGui::TableAngledHeadersRow();

   return 0;
}

int Gui::TableSetBgColor(lua_State* LuauState)
{
   ImGuiTableBgTarget Target = luaL_checkinteger(LuauState, 1);
   Color Color = Color::LuauCheck(LuauState, 2);
   int Column = luaL_optinteger(LuauState, 3, -1);

   ImGui::TableSetBgColor(Target, ImGui::GetColorU32(ImVec4(Color.R, Color.G, Color.B, Color.A)), Column);

   return 0;
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
   if (lua_isnumber(LuauState, 1))
   {
      int ID = luaL_checkinteger(LuauState, 1);

      ImGui::PushID(ID);

      return 0;
   }
   else if (lua_isstring(LuauState, 1))
   {
      const char* ID = luaL_checkstring(LuauState, 1);
      
      ImGui::PushID(ID);

      return 0;
   }

   luaL_error(LuauState, "Unexpected ID type. Expected string or integer");

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

int Gui::Indent(lua_State* LuauState)
{
   float Width = luaL_optinteger(LuauState, 1, 0.0f);

   ImGui::Indent(Width);

   return 0;
}

int Gui::Unindent(lua_State* LuauState)
{
   float Width = luaL_optinteger(LuauState, 1, 0.0f);

   ImGui::Unindent(Width);

   return 0;
}

int Gui::Separator(lua_State* LuauState)
{
   ImGui::Separator();

   return 0;
}

int Gui::Bullet(lua_State* LuauState)
{
   ImGui::Bullet();

   return 0;
}

int Gui::Dummy(lua_State* LuauState)
{
   Vec2 Size = Vec2::LuauCheck(LuauState, 1);

   ImGui::Dummy(ImVec2(Size.X, Size.Y));

   return 0;
}

int Gui::CollapsingHeader(lua_State* LuauState)
{
   const char* Label = luaL_checkstring(LuauState, 1);
   ImGuiTreeNodeFlags Flags = luaL_optinteger(LuauState, 2, 0);

   lua_pushboolean(LuauState, ImGui::CollapsingHeader(Label, 0));

   return 1;
}

int Gui::Image(lua_State* LuauState)
{
   luaL_checktype(LuauState, 1, LUA_TTABLE);

   lua_getfield(LuauState, 1, "ID");
   GLuint ImageID = luaL_checkinteger(LuauState, -1);
   lua_pop(LuauState, 1);

   Vec2 Size;
   if (!Vec2::LuauOpt(LuauState, 2, &Size))
   {
      int Width, Height;
      glBindTexture(GL_TEXTURE_2D, ImageID);
      glGetTexLevelParameteriv(GL_TEXTURE_2D, 0, GL_TEXTURE_WIDTH, &Width);
      glGetTexLevelParameteriv(GL_TEXTURE_2D, 0, GL_TEXTURE_HEIGHT, &Height);

      Size = Vec2(Width, Height);
   }

   Vec2 UV1(0.0f, 0.0f);
   Vec2::LuauOpt(LuauState, 3, &UV1);

   Vec2 UV2(1.0f, 1.0f);
   Vec2::LuauOpt(LuauState, 4, &UV2);

   ImGui::Image(ImageID, ImVec2(Size.X, Size.Y), ImVec2(UV1.X, UV1.Y), ImVec2(UV2.X, UV2.Y));

   return 0;
}

int Gui::ImageWithBg(lua_State* LuauState)
{
   luaL_checktype(LuauState, 1, LUA_TTABLE);

   lua_getfield(LuauState, 1, "ID");
   GLuint ImageID = luaL_checkinteger(LuauState, -1);
   lua_pop(LuauState, 1);

   Vec2 Size;
   if (!Vec2::LuauOpt(LuauState, 2, &Size))
   {
      int Width, Height;
      glBindTexture(GL_TEXTURE_2D, ImageID);
      glGetTexLevelParameteriv(GL_TEXTURE_2D, 0, GL_TEXTURE_WIDTH, &Width);
      glGetTexLevelParameteriv(GL_TEXTURE_2D, 0, GL_TEXTURE_HEIGHT, &Height);

      Size = Vec2(Width, Height);
   }

   Vec2 UV1(0.0f, 0.0f);
   Vec2::LuauOpt(LuauState, 3, &UV1);

   Vec2 UV2(1.0f, 1.0f);
   Vec2::LuauOpt(LuauState, 4, &UV2);

   Color Background(0.0f, 0.0f, 0.0f, 0.0f);
   Color::LuauOpt(LuauState, 5, &Background);

   Color Tint(1.0f, 1.0f, 1.0f, 1.0f);
   Color::LuauOpt(LuauState, 6, &Tint);

   ImGui::ImageWithBg(ImageID, ImVec2(Size.X, Size.Y), ImVec2(UV1.X, UV1.Y), ImVec2(UV2.X, UV2.Y), ImVec4(Background.R, Background.G, Background.B, Background.A), ImVec4(Tint.R, Tint.G, Tint.B, Tint.A));

   return 0;
}

int Gui::ImageButton(lua_State* LuauState)
{
   const char* ID = luaL_checkstring(LuauState, 1);

   luaL_checktype(LuauState, 2, LUA_TTABLE);

   lua_getfield(LuauState, 2, "ID");
   GLuint ImageID = luaL_checkinteger(LuauState, -1);
   lua_pop(LuauState, 1);

   Vec2 Size;
   if (!Vec2::LuauOpt(LuauState, 3, &Size))
   {
      int Width, Height;
      glBindTexture(GL_TEXTURE_2D, ImageID);
      glGetTexLevelParameteriv(GL_TEXTURE_2D, 0, GL_TEXTURE_WIDTH, &Width);
      glGetTexLevelParameteriv(GL_TEXTURE_2D, 0, GL_TEXTURE_HEIGHT, &Height);

      Size = Vec2(Width, Height);
   }

   Vec2 UV1(0.0f, 0.0f);
   Vec2::LuauOpt(LuauState, 4, &UV1);

   Vec2 UV2(1.0f, 1.0f);
   Vec2::LuauOpt(LuauState, 5, &UV2);

   Color Background(0.0f, 0.0f, 0.0f, 0.0f);
   Color::LuauOpt(LuauState, 6, &Background);

   Color Tint(1.0f, 1.0f, 1.0f, 1.0f);
   Color::LuauOpt(LuauState, 7, &Tint);

   ImGui::ImageButton(ID, ImageID, ImVec2(Size.X, Size.Y), ImVec2(UV1.X, UV1.Y), ImVec2(UV2.X, UV2.Y), ImVec4(Background.R, Background.G, Background.B, Background.A), ImVec4(Tint.R, Tint.G, Tint.B, Tint.A));

   return 1;
}

int Gui::Text(lua_State* LuauState)
{
   const char* Text = luaL_checkstring(LuauState, 1);
   bool Wrapped = luaL_optboolean(LuauState, 3, false);

   if (Wrapped)
   {
      ImGui::PushTextWrapPos();
   }

   Color Color;
   if (Color::LuauOpt(LuauState, 2, &Color))
   {
      ImGui::TextColored(*(ImVec4*)&Color, "%s", Text);
   }
   else 
   {
      ImGui::Text("%s", Text);
   }

   if (Wrapped)
   {
      ImGui::PopTextWrapPos();
   }

   return 0;
}

int Gui::SeparatorText(lua_State* LuauState)
{
   const char* Label = luaL_checkstring(LuauState, 1);

   ImGui::SeparatorText(Label);

   return 0;
}

int Gui::TextLink(lua_State* LuauState)
{
   const char* Label = luaL_checkstring(LuauState, 1);

   lua_pushboolean(LuauState, ImGui::TextLink(Label));

   return 1;
}

int Gui::TextLinkOpenURL(lua_State* LuauState)
{
   const char* Label = luaL_checkstring(LuauState, 1);
   const char* URL = luaL_checkstring(LuauState, 2);

   lua_pushboolean(LuauState, ImGui::TextLinkOpenURL(Label, URL));

   return 1;
}

int Gui::CalcTextSize(lua_State* LuauState)
{
   const char* Text = luaL_checkstring(LuauState, 1);

   ImVec2 TextSize = ImGui::CalcTextSize(Text);
   Vec2(TextSize.x, TextSize.y).LuauPush(LuauState);

   return 1;
}

int Gui::InputText(lua_State* LuauState)
{
   const char* Label = luaL_checkstring(LuauState, 1);
   const char* Input = luaL_checkstring(LuauState, 2);
   ImGuiInputTextFlags Flags = luaL_optinteger(LuauState, 3, 0);

   char Buffer[1024];
   strcpy(Buffer, Input);

   bool Modified = ImGui::InputText(Label, Buffer, 1024, Flags);
   lua_pushstring(LuauState, Buffer);
   lua_pushboolean(LuauState, Modified);

   return 2;
}

int Gui::InputTextWithHint(lua_State* LuauState)
{
   const char* Label = luaL_checkstring(LuauState, 1);
   const char* Hint = luaL_checkstring(LuauState, 2);
   const char* Input = luaL_checkstring(LuauState, 3);
   ImGuiInputTextFlags Flags = luaL_optinteger(LuauState, 4, 0);

   char Buffer[1024];
   strcpy(Buffer, Input);

   bool Modified = ImGui::InputTextWithHint(Label, Hint, Buffer, 1024, Flags);
   lua_pushstring(LuauState, Buffer);
   lua_pushboolean(LuauState, Modified);

   return 2;
}

int Gui::InputTextMultiline(lua_State* LuauState)
{
   const char* Label = luaL_checkstring(LuauState, 1);
   const char* Input = luaL_checkstring(LuauState, 2);

   Vec2 Size(0.0f, 0.0f);
   Vec2::LuauOpt(LuauState, 3, &Size);

   ImGuiInputTextFlags Flags = luaL_optinteger(LuauState, 4, 0);

   char Buffer[4096];
   strcpy(Buffer, Input);

   bool Modified = ImGui::InputTextMultiline(Label, Buffer, 4096, ImVec2(Size.X, Size.Y), Flags);
   lua_pushstring(LuauState, Buffer);
   lua_pushboolean(LuauState, Modified);

   return 2;
}

int Gui::InputFloat(lua_State* LuauState)
{
   const char* Label = luaL_checkstring(LuauState, 1);
   float Value = luaL_checknumber(LuauState, 2);
   int Precision = luaL_optinteger(LuauState, 3, 2);
   ImGuiInputTextFlags Flags = luaL_optinteger(LuauState, 4, 0);

   std::stringstream Format;
   Format << "%." << Precision << "f";

   bool Modified = ImGui::InputFloat(Label, &Value, 0.0f, 0.0f, Format.str().data(), Flags);
   lua_pushnumber(LuauState, Value);
   lua_pushboolean(LuauState, Modified);

   return 2;
}

int Gui::InputInt(lua_State* LuauState)
{
   const char* Label = luaL_checkstring(LuauState, 1);
   int Value = luaL_checkinteger(LuauState, 2);
   ImGuiInputTextFlags Flags = luaL_optinteger(LuauState, 3, 0);

   bool Modified = ImGui::InputInt(Label, &Value, 0, 0, Flags);
   lua_pushinteger(LuauState, Value);
   lua_pushboolean(LuauState, Modified);

   return 2;  
}

int Gui::Button(lua_State* LuauState)
{
   const char* Label = luaL_checkstring(LuauState, 1);
   Vec2 Size(0.0f, 0.0f);
   Vec2::LuauOpt(LuauState, 2, &Size);

   lua_pushboolean(LuauState, ImGui::Button(Label, ImVec2(Size.X, Size.Y)));

   return 1;
}

int Gui::SmallButton(lua_State* LuauState)
{
   const char* Label = luaL_checkstring(LuauState, 1);

   lua_pushboolean(LuauState, ImGui::SmallButton(Label));

   return 1;
}

int Gui::InvisibleButton(lua_State* LuauState)
{
   const char* ID = luaL_checkstring(LuauState, 1);
   Vec2 Size = Vec2::LuauCheck(LuauState, 2);
   ImGuiButtonFlags Flags = luaL_optinteger(LuauState, 3, 0);

   lua_pushboolean(LuauState, ImGui::InvisibleButton(ID, ImVec2(Size.X, Size.Y), Flags));

   return 1;
}

int Gui::ArrowButton(lua_State* LuauState)
{
   const char* ID = luaL_checkstring(LuauState, 1);
   ImGuiDir Direction = (ImGuiDir)luaL_checkinteger(LuauState, 2);

   lua_pushboolean(LuauState, ImGui::ArrowButton(ID, Direction));

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

int Gui::IsItemHovered(lua_State* LuauState)
{
   ImGuiHoveredFlags Flags = luaL_optinteger(LuauState, 1, 0);

   lua_pushboolean(LuauState, ImGui::IsItemHovered());

   return 1;
}

int Gui::IsItemClicked(lua_State* LuauState)
{
   ImGuiMouseButton Button = luaL_optinteger(LuauState, 1, 0);

   lua_pushboolean(LuauState, ImGui::IsItemClicked(Button));

   return 1;
}

int Gui::Selectable(lua_State* LuauState)
{
   const char* Label = luaL_checkstring(LuauState, 1);
   bool Selected = luaL_optboolean(LuauState, 2, false);
   ImGuiSelectableFlags Flags = luaL_optinteger(LuauState, 3, 0);

   Vec2 Size(0.0f, 0.0f);
   Vec2::LuauOpt(LuauState, 4, &Size);

   lua_pushboolean(LuauState, ImGui::Selectable(Label, Selected, Flags, ImVec2(Size.X, Size.Y)));

   return 1;
}

int Gui::Combo(lua_State* LuauState)
{
   const char* Label = luaL_checkstring(LuauState, 1);
   int CurrentItem = luaL_checkinteger(LuauState, 2) - 1;

   luaL_checktype(LuauState, 3, LUA_TTABLE);
   int Length = lua_objlen(LuauState, 3);
   const char* Items[Length];

   for (int i = 1; i <= Length; i++)
   {
      lua_rawgeti(LuauState, 3, i);

      Items[i - 1] = luaL_checkstring(LuauState, -1);

      lua_pop(LuauState, 1);
   }

   int MaxPopupItems = luaL_optinteger(LuauState, 4, -1);

   bool Modified = ImGui::Combo(Label, &CurrentItem, Items, Length, MaxPopupItems);
   lua_pushinteger(LuauState, CurrentItem + 1);
   lua_pushboolean(LuauState, Modified);

   return 2;
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

int Gui::PlotLines(lua_State* LuauState)
{
   const char* Label = luaL_checkstring(LuauState, 1);

   luaL_checktype(LuauState, 2, LUA_TTABLE);

   lua_Integer Length = lua_objlen(LuauState, 2);
   float Values[Length];

   for (int i = 1; i <= Length; i++)
   {
      lua_rawgeti(LuauState, 2, i);

      Values[i - 1] = luaL_checknumber(LuauState, -1);

      lua_pop(LuauState, 1);
   }

   const char* OverlayText = luaL_optstring(LuauState, 3, nullptr);

   Vec2 Size;
   Vec2::LuauOpt(LuauState, 4, &Size);

   ImGui::PlotLines(Label, Values, Length, 0, OverlayText, FLT_MAX, FLT_MAX, ImVec2(Size.X, Size.Y));

   return 0;
}

int Gui::BeginDragDropSource(lua_State* LuauState)
{
   ImGuiDragDropFlags Flags = luaL_optinteger(LuauState, 1, 0);

   lua_pushboolean(LuauState, ImGui::BeginDragDropSource(Flags));

   return 1;
}

int Gui::SetDragDropPayload(lua_State* LuauState)
{
   const char* Type = luaL_checkstring(LuauState, 1);

   lua_pushvalue(LuauState, 2);
   lua_setglobal(LuauState, "__PAYLOAD_INTERNAL");

   ImGuiCond Cond = luaL_optinteger(LuauState, 3, 0);

   bool Success = ImGui::SetDragDropPayload(Type, (void*)0, 0, Cond);
   if (!Success)
   {
      lua_pushnil(LuauState);
      lua_setglobal(LuauState, "__PAYLOAD_INTERNAL");
   }

   lua_pushboolean(LuauState, Success);

   return 1;
}

int Gui::EndDragDropSource(lua_State* LuauState)
{
   ImGui::EndDragDropSource();

   return 0;
}

int Gui::BeginDragDropTarget(lua_State* LuauState)
{
   lua_pushboolean(LuauState, ImGui::BeginDragDropTarget());

   return 1;
}

int Gui::AcceptDragDropPayload(lua_State* LuauState)
{
   const char* Type = luaL_checkstring(LuauState, 1);
   ImGuiDragDropFlags Flags = luaL_optinteger(LuauState, 2, 0);

   const ImGuiPayload* Payload = ImGui::AcceptDragDropPayload(Type, Flags);
   if (!Payload)
   {
      lua_pushnil(LuauState);
      return 1;
   }

   lua_getglobal(LuauState, "__PAYLOAD_INTERNAL");

   return 1;
}

int Gui::EndDragDropTarget(lua_State* LuauState)
{
   ImGui::EndDragDropTarget();

   return 0;
}

int Gui::GetDragDropPayload(lua_State* LuauState)
{
   if (ImGui::GetDragDropPayload())
   {
      lua_getglobal(LuauState, "__PAYLOAD_INTERNAL");
   }
   else 
   {
      lua_pushnil(LuauState);
   }

   return 1;
}


void Gui::PushStyle(lua_State* LuauState, const ImGuiStyle& Style)
{
   lua_createtable(LuauState, 0, 2);

   lua_pushnumber(LuauState, Style.FontSizeBase);
   lua_setfield(LuauState, -2, "FontSizeBase");

   lua_pushnumber(LuauState, Style.FontScaleDpi);
   lua_setfield(LuauState, -2, "FontScaleDpi");

   Vec2(Style.WindowPadding.x, Style.WindowPadding.y).LuauPush(LuauState);
   lua_setfield(LuauState, -2, "WindowPadding");

   lua_pushnumber(LuauState, Style.WindowRounding);
   lua_setfield(LuauState, -2, "WindowRounding");

   lua_pushnumber(LuauState, Style.WindowBorderSize);
   lua_setfield(LuauState, -2, "WindowBorderSize");

   lua_pushnumber(LuauState, Style.ChildRounding);
   lua_setfield(LuauState, -2, "ChildRounding");

   lua_pushnumber(LuauState, Style.ChildBorderSize);
   lua_setfield(LuauState, -2, "ChildBorderSize");

   lua_pushnumber(LuauState, Style.PopupRounding);
   lua_setfield(LuauState, -2, "PopupRounding");

   lua_pushnumber(LuauState, Style.PopupBorderSize);
   lua_setfield(LuauState, -2, "PopupBorderSize");

   Vec2(Style.FramePadding.x, Style.FramePadding.y).LuauPush(LuauState);
   lua_setfield(LuauState, -2, "FramePadding");

   lua_pushnumber(LuauState, Style.FrameRounding);
   lua_setfield(LuauState, -2, "FrameRounding");

   lua_pushnumber(LuauState, Style.FrameBorderSize);
   lua_setfield(LuauState, -2, "FrameBorderSize");

   Vec2(Style.FramePadding.x, Style.FramePadding.y).LuauPush(LuauState);
   lua_setfield(LuauState, -2, "FramePadding");

   Vec2(Style.ItemSpacing.x, Style.ItemSpacing.y).LuauPush(LuauState);
   lua_setfield(LuauState, -2, "ItemSpacing");

   Vec2(Style.ItemInnerSpacing.x, Style.ItemInnerSpacing.y).LuauPush(LuauState);
   lua_setfield(LuauState, -2, "ItemInnerSpacing");

   lua_pushnumber(LuauState, Style.IndentSpacing);
   lua_setfield(LuauState, -2, "IndentSpacing");

   lua_pushnumber(LuauState, Style.ScrollbarRounding);
   lua_setfield(LuauState, -2, "ScrollbarRounding");

   lua_pushnumber(LuauState, Style.GrabRounding);
   lua_setfield(LuauState, -2, "GrabRounding");

   lua_pushnumber(LuauState, Style.ImageRounding);
   lua_setfield(LuauState, -2, "ImageRounding");

   lua_pushnumber(LuauState, Style.TabRounding);
   lua_setfield(LuauState, -2, "TabRounding");

   lua_pushnumber(LuauState, Style.TreeLinesRounding);
   lua_setfield(LuauState, -2, "TreeLinesRounding");

   lua_pushnumber(LuauState, Style.MenuItemRounding);
   lua_setfield(LuauState, -2, "MenuItemRounding");

   lua_pushnumber(LuauState, Style.SelectableRounding);
   lua_setfield(LuauState, -2, "SelectableRounding");

   lua_pushnumber(LuauState, Style.DragDropTargetRounding);
   lua_setfield(LuauState, -2, "DragDropTargetRounding");

   lua_createtable(LuauState, ImGuiCol_COUNT, 0);

   for (int i = 1; i <= ImGuiCol_COUNT; i++)
   {
      ImVec4 ColorVec = Style.Colors[i - 1];
      Color Color(ColorVec.x, ColorVec.y, ColorVec.z, ColorVec.w);
      Color.LuauPush(LuauState);
      lua_rawseti(LuauState, -2, i);
   }

   lua_setfield(LuauState, -2, "Colors");
}

ImGuiStyle Gui::CheckStyle(lua_State* LuauState, int Index)
{
   luaL_checktype(LuauState, Index, LUA_TTABLE);

   ImGuiStyle Style = ImGui::GetStyle();
   
   lua_getfield(LuauState, Index, "FontSizeBase");
   Style.FontSizeBase = luaL_checknumber(LuauState, -1);
   lua_pop(LuauState, 1);

   lua_getfield(LuauState, Index, "FontScaleDpi");
   Style.FontScaleDpi = luaL_checknumber(LuauState, -1);
   lua_pop(LuauState, 1);

   lua_getfield(LuauState, Index, "WindowPadding");
   Vec2 WindowPadding = Vec2::LuauCheck(LuauState, -1);
   Style.FramePadding = ImVec2(WindowPadding.X, WindowPadding.Y);
   lua_pop(LuauState, 1);

   lua_getfield(LuauState, Index, "WindowRounding");
   Style.WindowRounding = luaL_checknumber(LuauState, -1);
   lua_pop(LuauState, 1);

   lua_getfield(LuauState, Index, "WindowBorderSize");
   Style.WindowBorderSize = luaL_checknumber(LuauState, -1);
   lua_pop(LuauState, 1);

   lua_getfield(LuauState, Index, "ChildRounding");
   Style.ChildRounding = luaL_checknumber(LuauState, -1);
   lua_pop(LuauState, 1);

   lua_getfield(LuauState, Index, "ChildBorderSize");
   Style.ChildBorderSize = luaL_checknumber(LuauState, -1);
   lua_pop(LuauState, 1);

   lua_getfield(LuauState, Index, "PopupRounding");
   Style.PopupRounding = luaL_checknumber(LuauState, -1);
   lua_pop(LuauState, 1);

   lua_getfield(LuauState, Index, "PopupBorderSize");
   Style.PopupBorderSize = luaL_checknumber(LuauState, -1);
   lua_pop(LuauState, 1);

   lua_getfield(LuauState, Index, "FramePadding");
   Vec2 FramePadding = Vec2::LuauCheck(LuauState, -1);
   Style.FramePadding = ImVec2(FramePadding.X, FramePadding.Y);
   lua_pop(LuauState, 1);

   lua_getfield(LuauState, Index, "ItemSpacing");
   Vec2 ItemSpacing = Vec2::LuauCheck(LuauState, -1);
   Style.ItemSpacing = ImVec2(ItemSpacing.X, ItemSpacing.Y);
   lua_pop(LuauState, 1);

   lua_getfield(LuauState, Index, "ItemInnerSpacing");
   Vec2 ItemInnerSpacing = Vec2::LuauCheck(LuauState, -1);
   Style.ItemInnerSpacing = ImVec2(ItemInnerSpacing.X, ItemInnerSpacing.Y);
   lua_pop(LuauState, 1);

   lua_getfield(LuauState, Index, "IndentSpacing");
   Style.IndentSpacing = luaL_checknumber(LuauState, -1);
   lua_pop(LuauState, 1);

   lua_getfield(LuauState, Index, "FrameRounding");
   Style.FrameRounding = luaL_checknumber(LuauState, -1);
   lua_pop(LuauState, 1);

   lua_getfield(LuauState, Index, "FrameBorderSize");
   Style.FrameBorderSize = luaL_checknumber(LuauState, -1);
   lua_pop(LuauState, 1);

   lua_getfield(LuauState, Index, "ScrollbarRounding");
   Style.ScrollbarRounding= luaL_checknumber(LuauState, -1);
   lua_pop(LuauState, 1);

   lua_getfield(LuauState, Index, "GrabRounding");
   Style.GrabRounding = luaL_checknumber(LuauState, -1);
   lua_pop(LuauState, 1);

   lua_getfield(LuauState, Index, "ImageRounding");
   Style.ImageRounding = luaL_checknumber(LuauState, -1);
   lua_pop(LuauState, 1);

   lua_getfield(LuauState, Index, "TabRounding");
   Style.TabRounding = luaL_checknumber(LuauState, -1);
   lua_pop(LuauState, 1);

   lua_getfield(LuauState, Index, "TreeLinesRounding");
   Style.TreeLinesRounding = luaL_checknumber(LuauState, -1);
   lua_pop(LuauState, 1);

   lua_getfield(LuauState, Index, "MenuItemRounding");
   Style.MenuItemRounding = luaL_checknumber(LuauState, -1);
   lua_pop(LuauState, 1);

   lua_getfield(LuauState, Index, "SelectableRounding");
   Style.SelectableRounding = luaL_checknumber(LuauState, -1);
   lua_pop(LuauState, 1);

   lua_getfield(LuauState, Index, "DragDropTargetRounding");
   Style.DragDropTargetRounding = luaL_checknumber(LuauState, -1);
   lua_pop(LuauState, 1);

   lua_getfield(LuauState, Index, "Colors");

   for (int i = 1; i <= ImGuiCol_COUNT; i++)
   {
      lua_rawgeti(LuauState, -1, i);

      Color Color = Color::LuauCheck(LuauState, -1);
      Style.Colors[i - 1] = ImVec4(Color.R, Color.G, Color.B, Color.A);

      lua_pop(LuauState, 1);
   }

   lua_pop(LuauState, 1);

   return Style;
}

int Gui::GetCurrentFont(lua_State* LuauState)
{
   ImFont* Current = ImGui::GetFont();

   Font::LuauPush(LuauState, Current);

   return 1;
}

int Gui::SetFont(lua_State* LuauState)
{
   ImFont* NewFont = Font::LuauCheck(LuauState, 1);

   ImGuiIO& IO = ImGui::GetIO();
   IO.FontDefault = NewFont;

   return 0;
}

int Gui::PushFont(lua_State* LuauState)
{
   ImFont* NewFont = nullptr; 
   if (lua_istable(LuauState, 1))
      NewFont = Font::LuauCheck(LuauState, 1);

   float NewSize = luaL_optnumber(LuauState, 2, 0.0f);

   ImGui::PushFont(NewFont, NewSize);

   return 0;
}

int Gui::PopFont(lua_State* LuauState)
{
   ImGui::PopFont();

   return 0;
}

int Gui::GetCurrentStyle(lua_State* LuauState)
{
   PushStyle(LuauState, ImGui::GetStyle());

   return 1;
}

int Gui::GetDarkStyle(lua_State* LuauState)
{
   ImGuiStyle Style;
   ImGui::StyleColorsDark(&Style);
   PushStyle(LuauState, Style);

   return 1;
}

int Gui::GetLightStyle(lua_State* LuauState)
{
   ImGuiStyle Style;
   ImGui::StyleColorsLight(&Style);
   PushStyle(LuauState, Style);

   return 1;
}

int Gui::GetClassicStyle(lua_State* LuauState)
{
   ImGuiStyle Style;
   ImGui::StyleColorsClassic(&Style);
   PushStyle(LuauState, Style);

   return 1;
}

int Gui::SetStyle(lua_State* LuauState)
{
   ImGui::GetStyle() = CheckStyle(LuauState, 1);

   return 0;
}

int Gui::PushStyleColor(lua_State* LuauState)
{
   ImGuiCol Index = luaL_checkinteger(LuauState, 1) -1;
   Color Color = Color::LuauCheck(LuauState, 2);

   ImGui::PushStyleColor(Index, ImVec4(Color.R, Color.G, Color.B, Color.A));

   return 0;
}

int Gui::PopStyleColor(lua_State* LuauState)
{
   int Count = luaL_optinteger(LuauState, 1, 1);

   ImGui::PopStyleColor(Count);

   return 0;
}

int Gui::GetStyleColorName(lua_State* LuauState)
{
   ImGuiCol Index = luaL_checkinteger(LuauState, 1) - 1;

   lua_pushstring(LuauState, ImGui::GetStyleColorName(Index));

   return 1;
}

int Gui::GetStyleColorValue(lua_State* LuauState)
{
   ImGuiCol Index = luaL_checkinteger(LuauState, 1) - 1;
   
   ImVec4 OutColor = ImGui::GetStyleColorVec4(Index);

   Color(OutColor.x, OutColor.y, OutColor.z, OutColor.w).LuauPush(LuauState);
   
   return 1;
}

int Gui::PushStyleVar(lua_State* LuauState)
{
   ImGuiStyleVar Index = luaL_checkinteger(LuauState, 1);

   if (lua_isnumber(LuauState, 2))
   {
      float Value = luaL_checknumber(LuauState, 2);

      ImGui::PushStyleVar(Index, Value);
   }
   else if (lua_istable(LuauState, 2))
   {
      Vec2 Value = Vec2::LuauCheck(LuauState, 2);

      ImGui::PushStyleVar(Index, ImVec2(Value.X, Value.Y));
   }

   return 0;
}

int Gui::PopStyleVar(lua_State* LuauState)
{
   int Count = luaL_optinteger(LuauState, 1, 1);

   ImGui::PopStyleVar(Count);

   return 0;
}

int Gui::ShowDemoWindow(lua_State* LuauState)
{
   int IsOpen = luaL_optboolean(LuauState, 1, -1);

   ImGui::ShowDemoWindow(IsOpen == -1 ? nullptr : (bool*)&IsOpen);

   lua_pushboolean(LuauState, IsOpen == -1 ? true : IsOpen);

   return 1;
}

int Gui::ShowIDStackToolWindow(lua_State* LuauState)
{
   int IsOpen = luaL_optboolean(LuauState, 1, -1);

   ImGui::ShowIDStackToolWindow(IsOpen == -1 ? nullptr : (bool*)&IsOpen);

   lua_pushboolean(LuauState, IsOpen == -1 ? true : IsOpen);

   return 1;
}

int Gui::ShowFontSelector(lua_State* LuauState)
{
   const char* Label = luaL_checkstring(LuauState, 1);

   ImGui::ShowFontSelector(Label);

   return 0;
}

/*
 *    Gui class
 */

luaL_Reg Gui::Functions[] = {
   { "SetSaveFile", SetSaveFile },

   { "SetNextWindowSize", SetNextWindowSize },
   { "SetNextWindowPos", SetNextWindowPos },
   { "SetNextWindowFocus", SetNextWindowFocus },

   { "SetNextWindowSizeConstraints", SetNextWindowSizeConstraints },

   { "GetWindowSize", GetWindowSize },
   { "GetWindowPos", GetWindowPos },

   { "GetCursorScreenPos", GetCursorScreenPos },
   { "SetCursorScreenPos", SetCursorScreenPos },
   { "GetContentRegionAvail", GetContentRegionAvail },

   { "GetCursorPos", GetCursorPos },
   { "SetCursorPos", SetCursorPos },

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

   { "BeginTabBar", BeginTabBar },
   { "EndTabBar", EndTabBar },

   { "BeginTabItem", BeginTabItem },
   { "EndTabItem", EndTabItem },

   { "BeginTooltip", BeginTooltip },
   { "EndTooltip", EndTooltip },
   { "SetTooltip", SetTooltip },

   { "OpenPopup", OpenPopup },
   { "OpenPopupOnItemClick", OpenPopupOnItemClick },
   { "CloseCurrentPopup", CloseCurrentPopup },

   { "BeginPopup", BeginPopup },
   { "BeginPopupModal", BeginPopupModal },
   { "EndPopup", EndPopup },

   { "BeginTable", BeginTable },
   { "EndTable", EndTable },

   { "TableNextRow", TableNextRow },
   { "TableNextColumn", TableNextColumn },
   { "TableSetColumnIndex", TableSetColumnIndex },

   { "TableSetupColumn", TableSetupColumn },
   { "TableSetupScrollFreeze", TableSetupScrollFreeze },
   { "TableHeader", TableHeader },
   { "TableHeadersRow", TableHeadersRow },
   { "TableAngledHeadersRow", TableAngledHeadersRow },

   { "TableSetBgColor", TableSetBgColor },

   { "BeginDisabled", BeginDisabled },
   { "EndDisabled", EndDisabled },

   { "PushID", PushID },
   { "PopID", PopID },

   { "SameLine", SameLine },
   { "Spacing", Spacing },
   { "Indent", Indent },
   { "Unindent", Unindent },
   { "Separator", Separator },
   { "Bullet", Bullet },
   { "Dummy", Dummy },

   { "CollapsingHeader", CollapsingHeader },

   { "Image", Image },
   { "ImageWithBg", ImageWithBg },
   { "ImageButton", ImageButton },

   { "Text", Text },
   { "SeparatorText", SeparatorText },

   { "TextLink", TextLink },
   { "TextLinkOpenURL", TextLinkOpenURL },

   { "CalcTextSize", CalcTextSize },

   { "InputText", InputText },
   { "InputTextWithHint", InputTextWithHint },
   { "InputTextMultiline", InputTextMultiline },
   { "InputFloat", InputFloat },
   { "InputInt", InputInt },

   { "Button", Button },
   { "SmallButton", SmallButton },
   { "InvisibleButton", InvisibleButton },
   { "ArrowButton", ArrowButton },
   { "Checkbox", Checkbox },

   { "IsItemHovered", IsItemHovered },
   { "IsItemClicked", IsItemClicked },

   { "Selectable", Selectable },

   { "Combo", Combo },

   { "SliderFloat", SliderFloat },
   { "ColorEdit", ColorEdit },

   { "PlotLines", PlotLines },

   { "BeginDragDropSource", BeginDragDropSource },
   { "SetDragDropPayload", SetDragDropPayload },
   { "EndDragDropSource", EndDragDropSource },

   { "BeginDragDropTarget", BeginDragDropTarget },
   { "AcceptDragDropPayload", AcceptDragDropPayload },
   { "EndDragDropTarget", EndDragDropTarget },
   { "GetDragDropPayload", GetDragDropPayload },

   { "GetCurrentFont", GetCurrentFont },
   { "SetFont", SetFont },

   { "PushFont", PushFont },
   { "PopFont", PopFont },

   { "GetCurrentStyle", GetCurrentStyle },
   { "GetDarkStyle", GetDarkStyle },
   { "GetLightStyle", GetLightStyle },
   { "GetClassicStyle", GetClassicStyle },
   { "SetStyle", SetStyle },

   { "PushStyleColor", PushStyleColor },
   { "PopStyleColor", PopStyleColor },
   { "GetStyleColorName", GetStyleColorName },
   { "GetStyleColorValue", GetStyleColorValue },

   { "PushStyleVar", PushStyleVar },
   { "PopStyleVar", PopStyleVar },

   { "ShowDemoWindow", ShowDemoWindow },
   { "ShowIDStackToolWindow", ShowIDStackToolWindow },
   { "ShowFontSelector", ShowFontSelector },
};

std::pair<std::string, int> Gui::GuiColors[] = {
   { "Text", ImGuiCol_Text },
   { "TextDisabled", ImGuiCol_TextDisabled },
   { "WindowBg", ImGuiCol_WindowBg },
   { "ChildBg", ImGuiCol_ChildBg },
   { "PopupBg", ImGuiCol_PopupBg },
   { "Border", ImGuiCol_Border },
   { "BorderShadow", ImGuiCol_BorderShadow },
   { "FrameBg", ImGuiCol_FrameBg },
   { "FrameBgHovered", ImGuiCol_FrameBgHovered },
   { "FrameBgActive", ImGuiCol_FrameBgActive },
   { "TitleBg", ImGuiCol_TitleBg },
   { "TitleBgActive", ImGuiCol_TitleBgActive },
   { "TitleBgCollapsed", ImGuiCol_TitleBgCollapsed },
   { "MenuBarBg", ImGuiCol_MenuBarBg },
   { "ScrollbarBg", ImGuiCol_ScrollbarBg },
   { "ScrollbarGrab", ImGuiCol_ScrollbarGrab },
   { "ScrollbarGrabHovered", ImGuiCol_ScrollbarGrabHovered },
   { "ScrollbarGrabActive", ImGuiCol_ScrollbarGrabActive },
   { "CheckMark", ImGuiCol_CheckMark },
   { "SliderGrab", ImGuiCol_SliderGrab },
   { "SliderGrabActive", ImGuiCol_SliderGrabActive },
   { "Button", ImGuiCol_Button },
   { "ButtonHovered", ImGuiCol_ButtonHovered },
   { "ButtonActive", ImGuiCol_ButtonActive },
   { "Header", ImGuiCol_Header },
   { "HeaderHovered", ImGuiCol_HeaderHovered },
   { "HeaderActive", ImGuiCol_HeaderActive },
   { "Separator", ImGuiCol_Separator },
   { "SeparatorHovered", ImGuiCol_SeparatorHovered },
   { "SeparatorActive", ImGuiCol_SeparatorActive },
   { "ResizeGrip", ImGuiCol_ResizeGrip },
   { "ResizeGripHovered", ImGuiCol_ResizeGripHovered },
   { "ResizeGripActive", ImGuiCol_ResizeGripActive },
   { "InputTextCursor", ImGuiCol_InputTextCursor },
   { "TabHovered", ImGuiCol_TabHovered },
   { "Tab", ImGuiCol_Tab },
   { "TabSelected", ImGuiCol_TabSelected },
   { "TabSelectedOverline", ImGuiCol_TabSelectedOverline },
   { "TabDimmed", ImGuiCol_TabDimmed },
   { "TabDimmedSelected", ImGuiCol_TabDimmedSelected },
   { "TabDimmedSelectedOverline", ImGuiCol_TabDimmedSelectedOverline },
   { "PlotLines", ImGuiCol_PlotLines },
   { "PlotLinesHovered", ImGuiCol_PlotLinesHovered },
   { "PlotHistogram", ImGuiCol_PlotHistogram },
   { "PlotHistogramHovered", ImGuiCol_PlotHistogramHovered },
   { "TableHeaderBg", ImGuiCol_TableHeaderBg },
   { "TableBorderStrong", ImGuiCol_TableBorderStrong },
   { "TableBorderLight", ImGuiCol_TableBorderLight },
   { "TableRowBg", ImGuiCol_TableRowBg },
   { "TableRowBgAlt", ImGuiCol_TableRowBgAlt },
   { "TextLink", ImGuiCol_TextLink },
   { "TextSelectedBg", ImGuiCol_TextSelectedBg },
   { "TreeLines", ImGuiCol_TreeLines },
   { "DragDropTarget", ImGuiCol_DragDropTarget },
   { "DragDropTargetBg", ImGuiCol_DragDropTargetBg },
   { "UnsavedMarker", ImGuiCol_UnsavedMarker },
   { "NavCursor", ImGuiCol_NavCursor },
   { "NavWindowingHighlight", ImGuiCol_NavWindowingHighlight },
   { "NavWindowingDimBg", ImGuiCol_NavWindowingDimBg },
   { "ModalWindowDimBg", ImGuiCol_ModalWindowDimBg },
};

std::pair<std::string, int> Gui::StyleVars[] = {
   { "Alpha", ImGuiStyleVar_Alpha },
   { "DisabledAlpha", ImGuiStyleVar_DisabledAlpha },
   { "WindowPadding", ImGuiStyleVar_WindowPadding },
   { "WindowRounding", ImGuiStyleVar_WindowRounding },
   { "WindowBorderSize", ImGuiStyleVar_WindowBorderSize },
   { "WindowMinSize", ImGuiStyleVar_WindowMinSize },
   { "WindowTitleAlign", ImGuiStyleVar_WindowTitleAlign },
   { "ChildRounding", ImGuiStyleVar_ChildRounding },
   { "ChildBorderSize", ImGuiStyleVar_ChildBorderSize },
   { "PopupRounding", ImGuiStyleVar_PopupRounding },
   { "PopupBorderSize", ImGuiStyleVar_PopupBorderSize },
   { "FramePadding", ImGuiStyleVar_FramePadding },
   { "FrameRounding", ImGuiStyleVar_FrameRounding },
   { "FrameBorderSize", ImGuiStyleVar_FrameBorderSize },
   { "ItemSpacing", ImGuiStyleVar_ItemSpacing },
   { "ItemInnerSpacing", ImGuiStyleVar_ItemInnerSpacing },
   { "IndentSpacing", ImGuiStyleVar_IndentSpacing },
   { "CellPadding", ImGuiStyleVar_CellPadding },
   { "ScrollbarSize", ImGuiStyleVar_ScrollbarSize },
   { "ScrollbarRounding", ImGuiStyleVar_ScrollbarRounding },
   { "ScrollbarPadding", ImGuiStyleVar_ScrollbarPadding },
   { "GrabMinSize", ImGuiStyleVar_GrabMinSize },
   { "GrabRounding", ImGuiStyleVar_GrabRounding },
   { "ImageRounding", ImGuiStyleVar_ImageRounding },
   { "ImageBorderSize", ImGuiStyleVar_ImageBorderSize },
   { "TabRounding", ImGuiStyleVar_TabRounding },
   { "TabBorderSize", ImGuiStyleVar_TabBorderSize },
   { "TabMinWidthBase", ImGuiStyleVar_TabMinWidthBase },
   { "TabMinWidthShrink", ImGuiStyleVar_TabMinWidthShrink },
   { "TabBarBorderSize", ImGuiStyleVar_TabBarBorderSize },
   { "TabBarOverlineSize", ImGuiStyleVar_TabBarOverlineSize },
   { "TableAngledHeadersAngle", ImGuiStyleVar_TableAngledHeadersAngle },
   { "TableAngledHeadersTextAlign", ImGuiStyleVar_TableAngledHeadersTextAlign },
   { "TreeLinesSize", ImGuiStyleVar_TreeLinesSize },
   { "TreeLinesRounding", ImGuiStyleVar_TreeLinesRounding },
   { "MenuItemRounding", ImGuiStyleVar_MenuItemRounding },
   { "SelectableRounding", ImGuiStyleVar_SelectableRounding },
   { "DragDropTargetRounding", ImGuiStyleVar_DragDropTargetRounding },
   { "ButtonTextAlign", ImGuiStyleVar_ButtonTextAlign },
   { "SelectableTextAlign", ImGuiStyleVar_SelectableTextAlign },
   { "SeparatorSize", ImGuiStyleVar_SeparatorSize },
   { "SeparatorTextBorderSize", ImGuiStyleVar_SeparatorTextBorderSize },
   { "SeparatorTextAlign", ImGuiStyleVar_SeparatorTextAlign },
   { "SeparatorTextPadding", ImGuiStyleVar_SeparatorTextPadding },
};

std::pair<std::string, int> Gui::Directions[] = {
   { "None", ImGuiDir_None },
   { "Left", ImGuiDir_Left },
   { "Right", ImGuiDir_Right },
   { "Up", ImGuiDir_Up },
   { "Down", ImGuiDir_Down },
};

std::pair<std::string, int> Gui::MouseButtons[] = {
   { "Left", ImGuiMouseButton_Left },
   { "Right", ImGuiMouseButton_Right },
   { "Middle", ImGuiMouseButton_Middle },
};

std::pair<std::string, int> Gui::TableBgTargets[] = {
   { "None", ImGuiTableBgTarget_None },
   { "RowBg1", ImGuiTableBgTarget_RowBg0 },
   { "RowBg2", ImGuiTableBgTarget_RowBg1 },
   { "CellBg", ImGuiTableBgTarget_CellBg },
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

std::pair<std::string, int> Gui::ButtonFlags[] = {
   { "None", ImGuiButtonFlags_None },
   { "MouseButtonLeft", ImGuiButtonFlags_MouseButtonLeft },
   { "MouseButtonRight", ImGuiButtonFlags_MouseButtonRight },
   { "MouseButtonMiddle", ImGuiButtonFlags_MouseButtonMiddle },
   { "EnableNav", ImGuiButtonFlags_EnableNav },
   { "AllowOverlap", ImGuiButtonFlags_AllowOverlap },
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

std::pair<std::string, int> Gui::InputTextFlags[] = {
   { "None", ImGuiInputTextFlags_None },
   { "CharsDecimal", ImGuiInputTextFlags_CharsDecimal },
   { "CharsHexadecimal", ImGuiInputTextFlags_CharsHexadecimal },
   { "CharsScientific", ImGuiInputTextFlags_CharsScientific },
   { "CharsUppercase", ImGuiInputTextFlags_CharsUppercase },
   { "CharsNoBlank", ImGuiInputTextFlags_CharsNoBlank },
   { "AllowTabInput", ImGuiInputTextFlags_AllowTabInput },
   { "EnterReturnsTrue", ImGuiInputTextFlags_EnterReturnsTrue },
   { "EscapeClearsAll", ImGuiInputTextFlags_EscapeClearsAll },
   { "CtrlEnterForNewLine", ImGuiInputTextFlags_CtrlEnterForNewLine },
   { "ReadOnly", ImGuiInputTextFlags_ReadOnly },
   { "Password", ImGuiInputTextFlags_Password },
   { "AlwaysOverwrite", ImGuiInputTextFlags_AlwaysOverwrite },
   { "AutoSelectAll", ImGuiInputTextFlags_AutoSelectAll },
   { "ParseEmptyRefVal", ImGuiInputTextFlags_ParseEmptyRefVal },
   { "DisplayEmptyRefVal", ImGuiInputTextFlags_DisplayEmptyRefVal },
   { "NoHorizontalScroll", ImGuiInputTextFlags_NoHorizontalScroll },
   { "NoUndoRedo", ImGuiInputTextFlags_NoUndoRedo },
   { "ElideLeft", ImGuiInputTextFlags_ElideLeft },
   { "CallbackCompletion", ImGuiInputTextFlags_CallbackCompletion },
   { "CallbackHistory", ImGuiInputTextFlags_CallbackHistory },
   { "CallbackAlways", ImGuiInputTextFlags_CallbackAlways },
   { "CallbackCharFilter", ImGuiInputTextFlags_CallbackCharFilter },
   { "CallbackResize", ImGuiInputTextFlags_CallbackResize },
   { "CallbackEdit", ImGuiInputTextFlags_CallbackEdit },
   { "WordWrap", ImGuiInputTextFlags_WordWrap },
};

std::pair<std::string, int> Gui::TreeNodeFlags[] = {
   { "None", ImGuiTreeNodeFlags_None },
   { "Selected", ImGuiTreeNodeFlags_Selected },
   { "Framed", ImGuiTreeNodeFlags_Framed },
   { "AllowOverlap", ImGuiTreeNodeFlags_AllowOverlap },
   { "NoTreePushOnOpen", ImGuiTreeNodeFlags_NoTreePushOnOpen },
   { "NoAutoOpenOnLog", ImGuiTreeNodeFlags_NoAutoOpenOnLog },
   { "DefaultOpen", ImGuiTreeNodeFlags_DefaultOpen },
   { "OpenOnDoubleClick", ImGuiTreeNodeFlags_OpenOnDoubleClick },
   { "OpenOnArrow", ImGuiTreeNodeFlags_OpenOnArrow },
   { "Leaf", ImGuiTreeNodeFlags_Leaf },
   { "Bullet", ImGuiTreeNodeFlags_Bullet },
   { "FramePadding", ImGuiTreeNodeFlags_FramePadding },
   { "SpanAvailWidth", ImGuiTreeNodeFlags_SpanAvailWidth },
   { "SpanFullWidth", ImGuiTreeNodeFlags_SpanFullWidth },
   { "SpanLabelWidth", ImGuiTreeNodeFlags_SpanLabelWidth },
   { "SpanAllColumns", ImGuiTreeNodeFlags_SpanAllColumns },
   { "LabelSpanAllColumns", ImGuiTreeNodeFlags_LabelSpanAllColumns },
   { "NavLeftJumpsToParent", ImGuiTreeNodeFlags_NavLeftJumpsToParent },
   { "CollapsingHeader", ImGuiTreeNodeFlags_CollapsingHeader },
   { "DrawLinesNone", ImGuiTreeNodeFlags_DrawLinesNone },
   { "DrawLinesFull", ImGuiTreeNodeFlags_DrawLinesFull },
   { "DrawLinesToNodes", ImGuiTreeNodeFlags_DrawLinesToNodes },
};

std::pair<std::string, int> Gui::SelectableFlags[] = {
   { "None", ImGuiSelectableFlags_None },
   { "NoAutoClosePopups", ImGuiSelectableFlags_NoAutoClosePopups },
   { "SpanAllColumns", ImGuiSelectableFlags_SpanAllColumns },
   { "AllowDoubleClick", ImGuiSelectableFlags_AllowDoubleClick },
   { "Disabled", ImGuiSelectableFlags_Disabled },
   { "AllowOverlap", ImGuiSelectableFlags_AllowOverlap },
   { "Highlight", ImGuiSelectableFlags_Highlight },
   { "SelectOnNav", ImGuiSelectableFlags_SelectOnNav },
};

std::pair<std::string, int> Gui::TabBarFlags[] = {
   { "None", ImGuiTabBarFlags_None },
   { "Reorderable", ImGuiTabBarFlags_Reorderable },
   { "AutoSelectNewTabs", ImGuiTabBarFlags_AutoSelectNewTabs },
   { "TabListPopupButton", ImGuiTabBarFlags_TabListPopupButton },
   { "NoCloseWithMiddleMouseButton", ImGuiTabBarFlags_NoCloseWithMiddleMouseButton },
   { "NoTabListScrollingButtons", ImGuiTabBarFlags_NoTabListScrollingButtons },
   { "NoTooltip", ImGuiTabBarFlags_NoTooltip },
   { "DrawSelectedOverline", ImGuiTabBarFlags_DrawSelectedOverline },
   { "FittingPolicyMixed", ImGuiTabBarFlags_FittingPolicyMixed },
   { "FittingPolicyShrink", ImGuiTabBarFlags_FittingPolicyShrink },
   { "FittingPolicyScroll", ImGuiTabBarFlags_FittingPolicyScroll },
};

std::pair<std::string, int> Gui::TabItemFlags[] = {
   { "None", ImGuiTabItemFlags_None },
   { "UnsavedDocument", ImGuiTabItemFlags_UnsavedDocument },
   { "SetSelected", ImGuiTabItemFlags_SetSelected },
   { "NoCloseWithMiddleMouseButton", ImGuiTabItemFlags_NoCloseWithMiddleMouseButton },
   { "NoPushId", ImGuiTabItemFlags_NoPushId },
   { "NoTooltip", ImGuiTabItemFlags_NoTooltip },
   { "NoReorder", ImGuiTabItemFlags_NoReorder },
   { "Leading", ImGuiTabItemFlags_Leading },
   { "Trailing", ImGuiTabItemFlags_Trailing },
   { "NoAssumedClosure", ImGuiTabItemFlags_NoAssumedClosure },
};

std::pair<std::string, int> Gui::TableFlags[] = {
   { "None", ImGuiTableFlags_None },
   { "Resizable", ImGuiTableFlags_Resizable },
   { "Reorderable", ImGuiTableFlags_Reorderable },
   { "Hideable", ImGuiTableFlags_Hideable },
   { "Sortable", ImGuiTableFlags_Sortable },
   { "NoSavedSettings", ImGuiTableFlags_NoSavedSettings },
   { "ContextMenuInBody", ImGuiTableFlags_ContextMenuInBody },
   { "RowBg", ImGuiTableFlags_RowBg },
   { "BordersInnerH", ImGuiTableFlags_BordersInnerH },
   { "BordersOuterH", ImGuiTableFlags_BordersOuterH },
   { "BordersInnerV", ImGuiTableFlags_BordersInnerV },
   { "BordersOuterV", ImGuiTableFlags_BordersOuterV },
   { "BordersH", ImGuiTableFlags_BordersH },
   { "BordersV", ImGuiTableFlags_BordersV },
   { "BordersInner", ImGuiTableFlags_BordersInner },
   { "BordersOuter", ImGuiTableFlags_BordersOuter },
   { "Borders", ImGuiTableFlags_Borders },
   { "NoBordersInBody", ImGuiTableFlags_NoBordersInBody },
   { "NoBordersInBodyUntilResize", ImGuiTableFlags_NoBordersInBodyUntilResize },
   { "SizingFixedFit", ImGuiTableFlags_SizingFixedFit },
   { "SizingFixedSame", ImGuiTableFlags_SizingFixedSame },
   { "SizingStretchProp", ImGuiTableFlags_SizingStretchProp },
   { "SizingStretchSame", ImGuiTableFlags_SizingStretchSame },
   { "NoHostExtendX", ImGuiTableFlags_NoHostExtendX },
   { "NoHostExtendY", ImGuiTableFlags_NoHostExtendY },
   { "NoKeepColumnsVisible", ImGuiTableFlags_NoKeepColumnsVisible },
   { "PreciseWidths", ImGuiTableFlags_PreciseWidths },
   { "NoClip", ImGuiTableFlags_NoClip },
   { "PadOuterX", ImGuiTableFlags_PadOuterX },
   { "NoPadOuterX", ImGuiTableFlags_NoPadOuterX },
   { "NoPadInnerX", ImGuiTableFlags_NoPadInnerX },
   { "ScrollX", ImGuiTableFlags_ScrollX },
   { "ScrollY", ImGuiTableFlags_ScrollY },
   { "SortMulti", ImGuiTableFlags_SortMulti },
   { "SortTristate", ImGuiTableFlags_SortTristate },
   { "HighlightHoveredColumn", ImGuiTableFlags_HighlightHoveredColumn },
};
std::pair<std::string, int> Gui::TableColumnFlags[] = {
   { "None", ImGuiTableColumnFlags_None },
   { "Disabled", ImGuiTableColumnFlags_Disabled },
   { "DefaultHide", ImGuiTableColumnFlags_DefaultHide },
   { "DefaultSort", ImGuiTableColumnFlags_DefaultSort },
   { "WidthStretch", ImGuiTableColumnFlags_WidthStretch },
   { "WidthFixed", ImGuiTableColumnFlags_WidthFixed },
   { "NoResize", ImGuiTableColumnFlags_NoResize },
   { "NoReorder", ImGuiTableColumnFlags_NoReorder },
   { "NoHide", ImGuiTableColumnFlags_NoHide },
   { "NoClip", ImGuiTableColumnFlags_NoClip },
   { "NoSort", ImGuiTableColumnFlags_NoSort },
   { "NoSortAscending", ImGuiTableColumnFlags_NoSortAscending },
   { "NoSortDescending", ImGuiTableColumnFlags_NoSortDescending },
   { "NoHeaderLabel", ImGuiTableColumnFlags_NoHeaderLabel },
   { "NoHeaderWidth", ImGuiTableColumnFlags_NoHeaderWidth },
   { "PreferSortAscending", ImGuiTableColumnFlags_PreferSortAscending },
   { "PreferSortDescending", ImGuiTableColumnFlags_PreferSortDescending },
   { "IndentEnable", ImGuiTableColumnFlags_IndentEnable },
   { "IndentDisable", ImGuiTableColumnFlags_IndentDisable },
   { "AngledHeader", ImGuiTableColumnFlags_AngledHeader },
   { "IsEnabled", ImGuiTableColumnFlags_IsEnabled },
   { "IsVisible", ImGuiTableColumnFlags_IsVisible },
   { "IsSorted", ImGuiTableColumnFlags_IsSorted },
   { "IsHovered", ImGuiTableColumnFlags_IsHovered },
};

std::pair<std::string, int> Gui::TableRowFlags[] = {
   { "None", ImGuiTableRowFlags_None },
   { "Headers", ImGuiTableRowFlags_Headers },
};

void Gui::LoadGlobal(lua_State* LuauState)
{
   // Setup globals
   LuauHelp::SetupFunctionsGlobal(LuauState, Functions, std::size(Functions), "Gui");
   LuauHelp::SetupEnumGlobal(LuauState, GuiColors, std::size(GuiColors), "GuiColors", 1);
   LuauHelp::SetupEnumGlobal(LuauState, StyleVars, std::size(StyleVars), "GuiStyleVars");
   LuauHelp::SetupEnumGlobal(LuauState, Directions, std::size(Directions), "GuiDirections");
   LuauHelp::SetupEnumGlobal(LuauState, MouseButtons, std::size(MouseButtons), "GuiMouseButtons");
   LuauHelp::SetupEnumGlobal(LuauState, TableBgTargets, std::size(TableBgTargets), "GuiTableBgTarget");
   LuauHelp::SetupEnumGlobal(LuauState, WindowFlags, std::size(WindowFlags), "GuiWindowFlags");
   LuauHelp::SetupEnumGlobal(LuauState, ChildFlags, std::size(ChildFlags), "GuiChildFlags");
   LuauHelp::SetupEnumGlobal(LuauState, ButtonFlags, std::size(ButtonFlags), "GuiButtonFlags");
   LuauHelp::SetupEnumGlobal(LuauState, SliderFlags, std::size(SliderFlags), "GuiSliderFlags");
   LuauHelp::SetupEnumGlobal(LuauState, InputTextFlags, std::size(InputTextFlags), "GuiInputTextFlags");
   LuauHelp::SetupEnumGlobal(LuauState, TreeNodeFlags, std::size(TreeNodeFlags), "GuiTreeNodeFlags");
   LuauHelp::SetupEnumGlobal(LuauState, SelectableFlags, std::size(SelectableFlags), "GuiSelectableFlags");
   LuauHelp::SetupEnumGlobal(LuauState, TabBarFlags, std::size(TabBarFlags), "GuiTabBarFlags");
   LuauHelp::SetupEnumGlobal(LuauState, TabItemFlags, std::size(TabItemFlags), "GuiTabItemFlags");
   LuauHelp::SetupEnumGlobal(LuauState, TableFlags, std::size(TableFlags), "GuiTableFlags");
   LuauHelp::SetupEnumGlobal(LuauState, TableColumnFlags, std::size(TableColumnFlags), "GuiTableColumnFlags");
   LuauHelp::SetupEnumGlobal(LuauState, TableRowFlags, std::size(TableRowFlags), "GuiTableRowFlags");

   ImGuiIO& IO = ImGui::GetIO();
   IO.IniFilename = nullptr;
}

void Gui::HandleDragDrop(lua_State* LuauState)
{
   /*
   static int DataIndex = LUA_NOREF;
   static int WasPayload = false;

   if (WasPayload)
   {
      lua_unref(LuauState, DataIndex);
      DataIndex = LUA_NOREF;

      WasPayload = false;
      std::cout << "Ref cleared" << std::endl;
   }

   const ImGuiPayload* Payload = ImGui::GetDragDropPayload();
   if (Payload)
   {
      DataIndex = *static_cast<const int*>(Payload->Data);
      WasPayload = true;
   }
   */
}

}
