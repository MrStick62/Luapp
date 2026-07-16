#include "Config.h"

#include <array>
#include <fstream>
#include <iostream>
#include <filesystem>

#include <lua.h>
#include <lualib.h>
#include <luacode.h>

#include <nlohmann/json.hpp>

#include "../App.h"
#include "../FileHelp.h"

namespace Luau
{

bool Config::IsLuauArray(lua_State* LuauState, int Index)
{
   lua_pushnil(LuauState);
   if (!lua_next(LuauState, Index))
      return false;

   lua_pop(LuauState, Index);

   return lua_objlen(LuauState, Index);
}

nlohmann::json Config::ToJsonValue(lua_State* LuauState, int Index)
{
   nlohmann::json OutObject = nullptr;

   int type = lua_type(LuauState, Index);
   switch (type)
   {
      case LUA_TTABLE:
      {
         OutObject = IsLuauArray(LuauState, Index) ? nlohmann::json::array() : nlohmann::json::object();
         LuauToJson(LuauState, Index, OutObject);
         break;
      }
      case LUA_TNUMBER:
      {
         OutObject = lua_tonumber(LuauState, Index);
         break;
      }
      case LUA_TSTRING:
      {
         OutObject = lua_tostring(LuauState, Index);
         break;
      }
      case LUA_TBOOLEAN:
      {
         OutObject = lua_toboolean(LuauState, Index);
         break;
      }
   }

   return OutObject;
}

void Config::LuauToJson(lua_State* LuauState, int Index, nlohmann::json& Object)
{
   if (Object.is_null())
      return;

   Index = lua_absindex(LuauState, Index);
   luaL_checktype(LuauState, Index, LUA_TTABLE);

   if (Object.is_object())
   {
      lua_pushnil(LuauState);
      while (lua_next(LuauState, Index))
      {
         Object[lua_tostring(LuauState, -2)] = ToJsonValue(LuauState, -1);
         lua_pop(LuauState, 1);
      }
   }
   else if (Object.is_array())
   {
      int Length = lua_objlen(LuauState, Index);
      for (int i = 1; i <= Length; i++)
      {
         lua_rawgeti(LuauState, Index, i);
         Object[i - 1] = ToJsonValue(LuauState, -1);
         lua_pop(LuauState, 1);
      }
   }
}

int Config::Save(lua_State* LuauState)
{
   luaL_checktype(LuauState, 1, LUA_TTABLE);
   
   nlohmann::json Object = ToJsonValue(LuauState, 1);
   std::string Content = Object.dump(2);

   const char* Path = luaL_checkstring(LuauState, 2);
   FileHelp::WriteWholeFile((App::GetPath() / Path).string(), Content);

   return 0;
}


void Config::PushJsonValue(lua_State* LuauState, const nlohmann::json& Value)
{
   if (Value.is_object())
   {
      lua_createtable(LuauState, 0, Value.size());
      JsonToLuau(LuauState, Value);
   }
   else if (Value.is_array())
   {
      lua_createtable(LuauState, Value.size(), 0);
      JsonToLuau(LuauState, Value);
   }
   else if (Value.is_number())
   {
      lua_pushnumber(LuauState, Value.get<double>());
   }
   else if (Value.is_string())
   {
      lua_pushstring(LuauState, Value.get<std::string>().data());
   }
   else if (Value.is_boolean())
   {
      lua_pushboolean(LuauState, Value.get<bool>());
   }
   else
   {
      lua_pushnil(LuauState);
   }
}

void Config::JsonToLuau(lua_State* LuauState, const nlohmann::json& Object)
{
   if (Object.is_object())
   {
      for (const auto& [Key, Value] : Object.items())
      {
         PushJsonValue(LuauState, Value);

         lua_setfield(LuauState, -2, Key.data());
      }
   }
   else if (Object.is_array())
   {
      for (int i = 1; i <= Object.size(); i++)
      {
         PushJsonValue(LuauState, Object[i]);

         lua_rawseti(LuauState, -2, i);
      }
   }
}

void Config::PushData(lua_State* LuauState, const std::string& Path)
{
   if (!std::filesystem::exists(App::GetPath() / Path))
   {
      lua_createtable(LuauState, 0, 0);
      return;
   }

   std::ifstream ConfigFile(App::GetPath() / Path);
   nlohmann::json Object = nlohmann::json::parse(ConfigFile);

   lua_createtable(LuauState, (Object.is_array()) ? Object.size() : 0, Object.is_object() ? Object.size() : 0);
   JsonToLuau(LuauState, Object);
}

int Config::Load(lua_State* LuauState)
{
   const char* Path = luaL_checkstring(LuauState, 1);

   PushData(LuauState, Path);

   return 1;
}

luaL_Reg Config::Functions[] = {
   { "Save", Save },
   { "Load", Load },
};

void Config::LoadGlobal(lua_State* LuauState)
{
   lua_createtable(LuauState, 0, std::size(Functions));
   
   for (const luaL_Reg& Function : Functions)
   {
      lua_pushcfunction(LuauState, Function.func, Function.name);
      lua_setfield(LuauState, -2, Function.name);
   }

   lua_setglobal(LuauState, "Config");
}

}
