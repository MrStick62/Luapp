#include "Web.h"

#include <array>
#include <cctype>
#include <cstdlib>
#include <algorithm>

#include <lua.h>
#include <lualib.h>
#include <luacode.h>

#include <GLFW/glfw3.h>
#include <GLFW/glfw3native.h>

#ifdef _WIN32
#define OPEN_WEB_COMMAND "start"
#elif __APPLE__
#define OPEN_WEB_COMMAND "open"
#elif __linux__
#define OPEN_WEB_COMMAND "xdg-open"
#endif

namespace Luau
{

bool Web::IsURL(const std::string& URL)
{
   bool ContainsPrefix = URL.starts_with("https://") || URL.starts_with("http://");
   bool NoWhitespace = std::any_of(URL.begin(), URL.end(), [](unsigned char c) { return std::isspace(c); });
   return ContainsPrefix && NoWhitespace;
}

int Web::OpenPage(lua_State* LuauState)
{
   const char* URL = luaL_checkstring(LuauState, 1);

   if (!IsURL(URL))
   {
      lua_pushboolean(LuauState, false);
      return 1;
   }

   std::string Command = std::string(OPEN_WEB_COMMAND) + " " + URL;
   std::system(Command.data());

   lua_pushboolean(LuauState, true);

   return 1;
}

luaL_Reg Web::Functions[] = {
   { "OpenPage", OpenPage }
};

void Web::LoadGlobal(lua_State *LuauState)
{
   lua_createtable(LuauState, 0, std::size(Functions));

   for (const luaL_Reg& Function : Functions)
   {
      lua_pushcfunction(LuauState, Function.func, Function.name);
      lua_setfield(LuauState, -2, Function.name);
   }

   lua_setglobal(LuauState, "Web");
}

}
