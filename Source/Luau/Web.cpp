#include "Web.h"

#include <array>
#include <cctype>
#include <cstdlib>
#include <fstream>
#include <algorithm>

#include <lua.h>
#include <lualib.h>
#include <luacode.h>

#include <GLFW/glfw3.h>
#include <GLFW/glfw3native.h>

#include "LuauHelp.h"

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

int Web::ConnectToSystem(lua_State* LuauState)
{
   const char* Hostname = luaL_checkstring(LuauState, 1);
   int ScreenWidth = luaL_optinteger(LuauState, 2, 1920);
   int ScreenHeight = luaL_optinteger(LuauState, 3, 1080);
   const char* Username = luaL_optstring(LuauState, 4, "");

   std::ofstream File("AutogenTempLuapp.rdp");

   File << "screen mode id:i:2\n";
   File << "desktopwidth:i:" << ScreenWidth << "\n";
   File << "desktopheight:i:" << ScreenHeight << "\n";
   File << "session bpp:i:32\n";
   File << "full address:s:" << Hostname << "\n";
   File << "username:s:" << Username << "\n";

   File.close();

   std::string Command = std::string(OPEN_WEB_COMMAND) + " AutogenTempLuapp.rdp";
   std::system(Command.data());

   std::remove("AutogenTempLuapp.rdp");

   return 0;
}

luaL_Reg Web::Functions[] = {
   { "OpenPage", OpenPage },
   { "ConnectToSystem", ConnectToSystem },
};

void Web::LoadGlobal(lua_State *LuauState)
{
   LuauHelp::SetupFunctionsGlobal(LuauState, Functions, std::size(Functions), "Web");
}

}
