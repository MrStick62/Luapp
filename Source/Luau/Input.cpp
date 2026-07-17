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

int Input::Shortcut(lua_State* LuauState)
{
   ImGuiKey Mods = static_cast<ImGuiKey>(luaL_checkinteger(LuauState, 1));
   ImGuiKey Key = static_cast<ImGuiKey>(luaL_checkinteger(LuauState, 2));

   ImGuiInputFlags Flags = luaL_optinteger(LuauState, 3, 0);

   lua_pushboolean(LuauState, ImGui::Shortcut(Mods | Key, Flags));

   return 1;
}

int Input::SetNextItemShortcut(lua_State* LuauState)
{
   ImGuiKey Mods = static_cast<ImGuiKey>(luaL_checkinteger(LuauState, 1));
   ImGuiKey Key = static_cast<ImGuiKey>(luaL_checkinteger(LuauState, 2));

   ImGuiInputFlags Flags = luaL_optinteger(LuauState, 3, 0);

   ImGui::SetNextItemShortcut(Mods | Key, Flags);

   return 0;
}

int Input::GetClipboardText(lua_State* LuauState)
{
   lua_pushstring(LuauState, ImGui::GetClipboardText());

   return 1;
}
int Input::SetClipboardText(lua_State* LuauState)
{
   const char* Input = luaL_checkstring(LuauState, 1);

   ImGui::SetClipboardText(Input);

   return 0;
}

luaL_Reg Input::Functions[] = {
   { "IsKeyDown", IsKeyDown },
   { "IsKeyPressed", IsKeyPressed },
   { "IsKeyReleased", IsKeyReleased },

   { "Shortcut", Shortcut },
   { "SetNextItemShortcut", SetNextItemShortcut },

   { "GetClipboardText", GetClipboardText },
   { "SetClipboardText", SetClipboardText },
};

std::pair<std::string, int> Input::Keys[] = {
   { "None", ImGuiKey_None },
   { "Tab", ImGuiKey_Tab },
   { "LeftArrow", ImGuiKey_LeftArrow },
   { "RightArrow", ImGuiKey_RightArrow },
   { "UpArrow", ImGuiKey_UpArrow },
   { "DownArrow", ImGuiKey_DownArrow },
   { "PageUp", ImGuiKey_PageUp },
   { "PageDown", ImGuiKey_PageDown },
   { "Home", ImGuiKey_Home },
   { "End", ImGuiKey_End },
   { "Insert", ImGuiKey_Insert },
   { "Delete", ImGuiKey_Delete },
   { "Backspace", ImGuiKey_Backspace },
   { "Space", ImGuiKey_Space },
   { "Enter", ImGuiKey_Enter },
   { "Escape", ImGuiKey_Escape },
   { "LeftCtrl", ImGuiKey_LeftCtrl },
   { "LeftShift", ImGuiKey_LeftShift },
   { "LeftAlt", ImGuiKey_LeftAlt },
   { "LeftSuper", ImGuiKey_LeftSuper },
   { "RightCtrl", ImGuiKey_RightCtrl },
   { "RightShift", ImGuiKey_RightShift },
   { "RightAlt", ImGuiKey_RightAlt },
   { "RightSuper", ImGuiKey_RightSuper },
   { "Menu", ImGuiKey_Menu },
   { "Num0", ImGuiKey_0 },
   { "Num1", ImGuiKey_1 },
   { "Num2", ImGuiKey_2 },
   { "Num3", ImGuiKey_3 },
   { "Num4", ImGuiKey_4 },
   { "Num5", ImGuiKey_5 },
   { "Num6", ImGuiKey_6 },
   { "Num7", ImGuiKey_7 },
   { "Num8", ImGuiKey_8 },
   { "Num9", ImGuiKey_9 },
   { "A", ImGuiKey_A },
   { "B", ImGuiKey_B },
   { "C", ImGuiKey_C },
   { "D", ImGuiKey_D },
   { "E", ImGuiKey_E },
   { "F", ImGuiKey_F },
   { "G", ImGuiKey_G },
   { "H", ImGuiKey_H },
   { "I", ImGuiKey_I },
   { "J", ImGuiKey_J },
   { "K", ImGuiKey_K },
   { "L", ImGuiKey_L },
   { "M", ImGuiKey_M },
   { "N", ImGuiKey_N },
   { "O", ImGuiKey_O },
   { "P", ImGuiKey_P },
   { "Q", ImGuiKey_Q },
   { "R", ImGuiKey_R },
   { "S", ImGuiKey_S },
   { "T", ImGuiKey_T },
   { "U", ImGuiKey_U },
   { "V", ImGuiKey_V },
   { "W", ImGuiKey_W },
   { "X", ImGuiKey_X },
   { "Y", ImGuiKey_Y },
   { "Z", ImGuiKey_Z },
   { "F1", ImGuiKey_F1 },
   { "F2", ImGuiKey_F2 },
   { "F3", ImGuiKey_F3 },
   { "F5", ImGuiKey_F5 },
   { "F6", ImGuiKey_F6 },
   { "F7", ImGuiKey_F7 },
   { "F8", ImGuiKey_F8 },
   { "F9", ImGuiKey_F9 },
   { "F10", ImGuiKey_F10 },
   { "F11", ImGuiKey_F11 },
   { "F12", ImGuiKey_F12 },
   { "F13", ImGuiKey_F13 },
   { "F14", ImGuiKey_F14 },
   { "F15", ImGuiKey_F15 },
   { "F16", ImGuiKey_F16 },
   { "F17", ImGuiKey_F17 },
   { "F18", ImGuiKey_F18 },
   { "F19", ImGuiKey_F19 },
   { "F20", ImGuiKey_F20 },
   { "F21", ImGuiKey_F21 },
   { "F22", ImGuiKey_F22 },
   { "F23", ImGuiKey_F23 },
   { "F24", ImGuiKey_F24 },
   { "Apostrophe", ImGuiKey_Apostrophe },
   { "Comma", ImGuiKey_Comma },
   { "Minus", ImGuiKey_Minus },
   { "Period", ImGuiKey_Period },
   { "Slash", ImGuiKey_Slash },
   { "Semicolon", ImGuiKey_Semicolon },
   { "Equal", ImGuiKey_Equal },
   { "LeftBracket", ImGuiKey_LeftBracket },
   { "Backslash", ImGuiKey_Backslash },
   { "RightBracket", ImGuiKey_RightBracket },
   { "GraveAccent", ImGuiKey_GraveAccent },
   { "CapsLock", ImGuiKey_CapsLock },
   { "ScrollLock", ImGuiKey_ScrollLock },
   { "NumLock", ImGuiKey_NumLock },
   { "PrintScreen", ImGuiKey_PrintScreen },
   { "Pause", ImGuiKey_Pause },
   { "Keypad0", ImGuiKey_Keypad0 },
   { "Keypad1", ImGuiKey_Keypad1 },
   { "Keypad2", ImGuiKey_Keypad2 },
   { "Keypad3", ImGuiKey_Keypad3 },
   { "Keypad4", ImGuiKey_Keypad4 },
   { "Keypad5", ImGuiKey_Keypad5 },
   { "Keypad6", ImGuiKey_Keypad6 },
   { "Keypad7", ImGuiKey_Keypad7 },
   { "Keypad8", ImGuiKey_Keypad8 },
   { "Keypad9", ImGuiKey_Keypad9 },
   { "KeypadDecimal", ImGuiKey_KeypadDecimal },
   { "KeypadDivide", ImGuiKey_KeypadDivide },
   { "KeypadMultiply", ImGuiKey_KeypadMultiply },
   { "KeypadSubtract", ImGuiKey_KeypadSubtract },
   { "KeypadAdd", ImGuiKey_KeypadAdd },
   { "KeypadEnter", ImGuiKey_KeypadEnter },
   { "KeypadEqual", ImGuiKey_KeypadEqual },
   { "AppBack", ImGuiKey_AppBack },
   { "AppForward", ImGuiKey_AppForward },
   { "Oem102", ImGuiKey_Oem102 },
   // Gamepad controls would go here
   { "MouseLeft", ImGuiKey_MouseLeft },
   { "MouseRight", ImGuiKey_MouseRight },
   { "MouseMiddle", ImGuiKey_MouseMiddle },
   { "MouseX1", ImGuiKey_MouseX1 },
   { "MouseX2", ImGuiKey_MouseX2 },
   { "MouseWheelX", ImGuiKey_MouseWheelX },
   { "MouseWheelY", ImGuiKey_MouseWheelY },
   { "ReservedForModCtrl", ImGuiKey_ReservedForModCtrl },
   { "ReservedForModShift", ImGuiKey_ReservedForModShift },
   { "ReservedForModAlt", ImGuiKey_ReservedForModAlt },
   { "ReservedForModSuper", ImGuiKey_ReservedForModSuper },
};

std::pair<std::string, int> Input::Mods[] = {
   { "None", ImGuiMod_None },
   { "Ctrl", ImGuiMod_Ctrl },
   { "Shift", ImGuiMod_Shift },
   { "Alt", ImGuiMod_Alt },
   { "Super", ImGuiMod_Super },
};

std::pair<std::string, int> Input::Flags[] = {
   { "None", ImGuiInputFlags_None },
   { "Repeat", ImGuiInputFlags_Repeat },
   { "RouteActive", ImGuiInputFlags_RouteActive },
   { "RouteFocused", ImGuiInputFlags_RouteFocused },
   { "RouteGlobal", ImGuiInputFlags_RouteGlobal },
   { "RouteAlways", ImGuiInputFlags_RouteAlways },
   { "RouteOverFocused", ImGuiInputFlags_RouteOverFocused },
   { "RouteOverActive", ImGuiInputFlags_RouteOverActive },
   { "RouteUnlessBgFocused", ImGuiInputFlags_RouteUnlessBgFocused },
   { "RouteFromRootWindow", ImGuiInputFlags_RouteFromRootWindow },
   { "Tooltip", ImGuiInputFlags_Tooltip },
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
   
   // Init mod enum list
   lua_createtable(LuauState, 0, std::size(Mods));

   for (const auto& Key : Mods)
   {
      lua_pushinteger(LuauState, Key.second);
      lua_setfield(LuauState, -2, Key.first.data());
   }

   lua_setglobal(LuauState, "InputMod");

   // Init input flags
   lua_createtable(LuauState, 0, std::size(Flags));

   for (const auto& Flag : Flags)
   {
      lua_pushinteger(LuauState, Flag.second);
      lua_setfield(LuauState, -2, Flag.first.data());
   }

   lua_setglobal(LuauState, "InputFlags");
}

}
