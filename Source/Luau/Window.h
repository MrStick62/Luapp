#pragma once


class luaL_Reg;
class lua_State;
class GLFWwindow;

namespace Luau
{

class Window
{
private:
   static GLFWwindow* WindowRef;

   static luaL_Reg Functions[];

   static int GetSize(lua_State* LuauState);
   static int SetSize(lua_State* LuauState);
   static int SetSizeLimits(lua_State* LuauState);

   static int SetTitle(lua_State* LuauState);
   static int SetIcon(lua_State* LuauState);

   static int Close(lua_State* LuauState);

public:
   static void LoadGlobal(lua_State* LuauState);
   static void SetCurrentWindow(GLFWwindow* NewWindow);
};

}
