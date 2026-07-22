#pragma once

class luaL_Reg;
class lua_State;

#include <nlohmann/json_fwd.hpp>

namespace Luau
{

class Config
{
private:
   static luaL_Reg Functions[];

   static int Save(lua_State* LuauState);
   static int Load(lua_State* LuauState);

   static bool IsLuauArray(lua_State* LuauState, int Index);
   static nlohmann::json ToJsonValue(lua_State* LuauState, int Index);
   static void LuauToJson(lua_State* LuauState, int Index, nlohmann::json& Object, bool IsArray);

   static void PushData(lua_State* LuauState, const std::string& Path);

   static void PushJsonValue(lua_State* LuauState, const nlohmann::json& Value);
   static void JsonToLuau(lua_State* LuauState, const nlohmann::json& Object);

public:
   static void LoadGlobal(lua_State* LuauState);

};

}
