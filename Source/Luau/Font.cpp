#include "Font.h"

#include <cstring>

#include <lua.h>
#include <lualib.h>
#include <luacode.h>

#include <imgui/imgui.h>

#include "LuauHelp.h"

#include "../App.h"
#include "../FileHelp.h"

namespace Luau
{

int Font::LoadNew(lua_State* LuauState)
{
   const char* FontPath = luaL_checkstring(LuauState, 1);
   const char* IconPath = luaL_optstring(LuauState, 2, "");

   ImGuiIO& IO = ImGui::GetIO();
   ImFont* NewFont = IO.Fonts->AddFontFromFileTTF((App::GetPath() / FontPath).string().data());

   if (strlen(IconPath))
   {
      ImFontConfig Config;
      Config.MergeMode = true;
      
      IO.Fonts->AddFontFromFileTTF((App::GetPath() / IconPath).string().data());
   }
   else 
   {
      AddDefaultIcons();
   }

   LuauPush(LuauState, NewFont);

   return 1;
}

int Font::GetAll(lua_State* LuauState)
{
   ImGuiIO& IO = ImGui::GetIO();

   lua_createtable(LuauState, IO.Fonts->Fonts.size(), 0);

   for (int i = 1; i <= IO.Fonts->Fonts.size(); i++)
   {
      LuauPush(LuauState, IO.Fonts->Fonts[i - 1]);
      lua_rawseti(LuauState, -2, i);
   }

   return 1;
}

luaL_Reg Font::Functions[] = {
   { "LoadNew", LoadNew },
   { "GetAll", GetAll },
};
luaL_Reg Font::MetaFunctions[] = {};

void Font::LuauPush(lua_State* LuauState, ImFont* Font)
{
   lua_createtable(LuauState, 0, 2);

   luaL_getmetatable(LuauState, "Font");
   lua_setmetatable(LuauState, -2);
   
   lua_pushinteger(LuauState, Font->FontId);
   lua_setfield(LuauState, -2, "ID");

   lua_pushstring(LuauState, Font->GetDebugName());
   lua_setfield(LuauState, -2, "Name");
}

ImFont* Font::LuauCheck(lua_State* LuauState, int Index)
{
   luaL_checktype(LuauState, Index, LUA_TTABLE);

   lua_getfield(LuauState, Index, "ID");
   ImGuiID ID = luaL_checknumber(LuauState, -1);
   lua_pop(LuauState, 1);

   ImGuiIO& IO = ImGui::GetIO();
   for (ImFont* Font : IO.Fonts->Fonts)
   {
      if (Font->FontId == ID)
         return Font;
   }

   luaL_error(LuauState, "Failed to find valid font!");

   return nullptr;
}

void Font::AddDefaultIcons()
{
   ImGuiIO& IO = ImGui::GetIO();

   ImFontConfig Config;
   Config.MergeMode = true;
   Config.GlyphMinAdvanceX = 13.0f;

   IO.Fonts->AddFontFromFileTTF((FileHelp::GetProjectDirectory() / "Assets" / "Fonts" / "Icons" / "fa-solid-900.ttf").string().data(), 13.0f, &Config);
}

void Font::LoadGlobal(lua_State* LuauState)
{  
   // Load default fonts
   ImGuiIO& IO = ImGui::GetIO();

   ImFont* DefaultFont = IO.Fonts->AddFontFromFileTTF((FileHelp::GetProjectDirectory() / "Assets" / "Fonts" / "ProggyClean.ttf").string().data());
   AddDefaultIcons();

   IO.Fonts->AddFontFromFileTTF((FileHelp::GetProjectDirectory() / "Assets" / "Fonts" / "Cousine-Regular.ttf").string().data());
   AddDefaultIcons();

   IO.Fonts->AddFontFromFileTTF((FileHelp::GetProjectDirectory() / "Assets" / "Fonts" / "DroidSans.ttf").string().data());
   AddDefaultIcons();
   
   IO.Fonts->AddFontFromFileTTF((FileHelp::GetProjectDirectory() / "Assets" / "Fonts" / "Karla-Regular.ttf").string().data());
   AddDefaultIcons();

   IO.Fonts->AddFontFromFileTTF((FileHelp::GetProjectDirectory() / "Assets" / "Fonts" / "ProggyTiny.ttf").string().data());
   AddDefaultIcons();

   IO.Fonts->AddFontFromFileTTF((FileHelp::GetProjectDirectory() / "Assets" / "Fonts" / "Roboto-Medium.ttf").string().data());
   AddDefaultIcons();

   IO.FontDefault = DefaultFont;

   // Image metatable
   luaL_newmetatable(LuauState, "Font");

   lua_pushvalue(LuauState, -1);
   lua_setfield(LuauState, -2, "__index");

   for (const luaL_Reg& Function : MetaFunctions)
   {
      lua_pushcfunction(LuauState, Function.func, Function.name);
      lua_setfield(LuauState, -2, Function.name);
   }

   lua_pop(LuauState, 1);

   // Image functions
   LuauHelp::SetupFunctionsGlobal(LuauState, Functions, std::size(Functions), "Font");
}

}
