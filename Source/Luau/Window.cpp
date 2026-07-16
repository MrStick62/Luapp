#include "Window.h"

#include <array>

#include <lua.h>
#include <lualib.h>
#include <luacode.h>

#include <GLFW/glfw3.h>

#include "Vec2.h"

namespace Luau
{

int Window::GetSize(lua_State* LuauState)
{
   int Width, Height;
   glfwGetWindowSize(WindowRef, &Width, &Height);

   Vec2 Size(Width, Height);
   Size.LuauPush(LuauState);

   return 1;
}

GLFWwindow* Window::WindowRef = nullptr;

void Window::SetCurrentWindow(GLFWwindow *NewWindow)
{
   WindowRef = NewWindow;
}

luaL_Reg Window::Functions[] = {
   { "GetSize", GetSize },
};

void Window::LoadGlobal(lua_State *LuauState)
{
   lua_createtable(LuauState, 0, std::size(Functions));

   for (const luaL_Reg& Function : Functions)
   {
      lua_pushcfunction(LuauState, Function.func, Function.name);
      lua_setfield(LuauState, -2, Function.name);
   }

   lua_setglobal(LuauState, "Window");
}

}
