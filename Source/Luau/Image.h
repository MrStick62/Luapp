#pragma once

#include <cstdlib>

class luaL_Reg;
class lua_State;

typedef unsigned int GLuint;

namespace Luau
{

class Image
{
private:
   // Global functions
   static int New(lua_State* LuauState);

   // Meta functions
   static int __gc(lua_State* LuauState);
   static int Destroy(lua_State* LuauState);
   static int GetSize(lua_State* LuauState);

   static bool LoadTextureFromMemory(const void* Data, size_t DataSize, GLuint* OutTexture);

   static luaL_Reg Functions[];
   static luaL_Reg MetaFunctions[];

public:
   static void LoadGlobal(lua_State* LuauState);

};

}
