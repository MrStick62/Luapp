#include "File.h"

#include <array>
#include <cstring>
#include <iostream>

#include <lua.h>
#include <lualib.h>
#include <luacode.h>

#include <nfd.h>

#include "LuauHelp.h"

namespace Luau
{


int File::OpenDialog(lua_State* LuauState)
{
   luaL_checktype(LuauState, 1, LUA_TTABLE);

   std::vector<std::pair<const char*, const char*>> Filters;

   lua_pushnil(LuauState);
   while (lua_next(LuauState, 1))
   {
      const char* Name = luaL_checkstring(LuauState, -2);
      const char* Extensions = luaL_checkstring(LuauState, -1);

      Filters.push_back({ Name, Extensions });

      lua_pop(LuauState, 1);
   }

   size_t FiltersSize = Filters.size();

   nfdu8char_t* OutPath;
   nfdu8filteritem_t FiltersArray[FiltersSize];
   
   for (int i = 0; i < FiltersSize; i++)
   {
      auto Filter = Filters[i];

      FiltersArray[i] = { Filter.first, Filter.second };
   }

   nfdopendialogu8args_t Args = {0};
   Args.filterList = FiltersArray;
   Args.filterCount = FiltersSize;

   nfdresult_t Result = NFD_OpenDialogU8_With(&OutPath, &Args);
   switch (Result)
   {
   case NFD_OKAY:
      lua_pushstring(LuauState, OutPath);
      break;
   case NFD_CANCEL:
      lua_pushnil(LuauState);
      break;
   default: 
      std::cerr << "NFD Error: " << NFD_GetError();
      break;
   }

   return 1;
}

luaL_Reg File::Functions[] = {
   { "OpenDialog", OpenDialog },
};

void File::LoadGlobal(lua_State* LuauState)
{
   NFD_Init();

   LuauHelp::SetupFunctionsGlobal(LuauState, Functions, std::size(Functions), "File");
}

}
