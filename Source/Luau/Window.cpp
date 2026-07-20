#include "Window.h"

#include <array>

#include <lua.h>
#include <lualib.h>
#include <luacode.h>

#include <GLFW/glfw3.h>

#include "Vec2.h"
#include "LuauHelp.h"

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

int Window::Close(lua_State* LuauState)
{
   glfwSetWindowShouldClose(WindowRef, true);

   return 0;
}

GLFWwindow* Window::WindowRef = nullptr;

void Window::SetCurrentWindow(GLFWwindow *NewWindow)
{
   WindowRef = NewWindow;
}

luaL_Reg Window::Functions[] = {
   { "GetSize", GetSize },
   { "Close", Close },
};

void Window::LoadGlobal(lua_State *LuauState)
{
   LuauHelp::SetupFunctionsGlobal(LuauState, Functions, std::size(Functions), "Window");
}

}
