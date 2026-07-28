#include "File.h"

#include <array>
#include <thread>
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
   const char* ID = luaL_checkstring(LuauState, 1);

   if (OpenDialogs.contains(ID))
   {
      const char* Path = OpenDialogs[ID];
      if (Path == std::string("\\"))
      {
         lua_pushboolean(LuauState, true);
         lua_pushnil(LuauState);
         OpenDialogs.erase(ID);
      }
      else if (strlen(Path))
      {
         lua_pushboolean(LuauState, true);
         lua_pushstring(LuauState, Path);
         OpenDialogs.erase(ID);
      }
      else
      {
         lua_pushboolean(LuauState, false);
         lua_pushnil(LuauState);
      }

      return 2;
   }

   luaL_checktype(LuauState, 2, LUA_TTABLE);

   std::vector<std::pair<const char*, const char*>> Filters;

   lua_pushnil(LuauState);
   while (lua_next(LuauState, 2))
   {
      const char* Name = luaL_checkstring(LuauState, -2);
      const char* Extensions = luaL_checkstring(LuauState, -1);

      Filters.push_back({ Name, Extensions });

      lua_pop(LuauState, 1);
   }

   std::thread Dialog(DialogThread, std::string(ID), Filters);

   Dialog.detach();

   lua_pushboolean(LuauState, false);
   lua_pushnil(LuauState);
   return 2;
}

void File::DialogThread(std::string ID, std::vector<std::pair<const char*, const char*>> Filters)
{
   if (OpenDialogs.contains(ID))  
      return;

   OpenDialogs.emplace(ID, "");

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
      OpenDialogs[ID] = OutPath;
      break;
   case NFD_CANCEL:
      OpenDialogs[ID] = "\\";
      break;
   default: 
      std::cerr << "NFD Error: " << NFD_GetError();
      break;
   }
}

luaL_Reg File::Functions[] = {
   { "OpenDialog", OpenDialog },
};

std::unordered_map<std::string, const char*> File::OpenDialogs;

void File::LoadGlobal(lua_State* LuauState)
{
   NFD_Init();

   LuauHelp::SetupFunctionsGlobal(LuauState, Functions, std::size(Functions), "File");
}

}
