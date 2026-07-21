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

int Window::SetSize(lua_State* LuauState)
{
   Vec2 Size = Vec2::LuauCheck(LuauState, 1);

   glfwSetWindowSize(WindowRef, Size.X, Size.Y);

   return 0;
}

int Window::SetSizeLimits(lua_State* LuauState)
{
   Vec2 Min(GLFW_DONT_CARE, GLFW_DONT_CARE);
   Vec2::LuauOpt(LuauState, 1, &Min);

   Vec2 Max(GLFW_DONT_CARE, GLFW_DONT_CARE);
   Vec2::LuauOpt(LuauState, 2, &Max);

   glfwSetWindowSizeLimits(WindowRef, Min.X, Min.Y, Max.X, Max.Y);

   return 0;
}

int Window::SetTitle(lua_State* LuauState)
{
   const char* Name = luaL_checkstring(LuauState, 1);

   glfwSetWindowTitle(WindowRef, Name);

   return 0;
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
   { "SetSize", SetSize },
   { "SetSizeLimits", SetSizeLimits },

   { "SetTitle", SetTitle },

   { "Close", Close },
};

void Window::LoadGlobal(lua_State *LuauState)
{
   LuauHelp::SetupFunctionsGlobal(LuauState, Functions, std::size(Functions), "Window");
}

}
