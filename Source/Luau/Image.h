#pragma once

#include <cstdlib>

#include <glad/gl.h>

class luaL_Reg;
class lua_State;

namespace Luau
{

class Image
{
private:
   // Static members
   static int Load(lua_State* LuauState);

   static bool LoadTextureFromMemory(const void* Data, size_t DataSize, GLuint* OutTexture);

   static luaL_Reg Functions[];

public:
   static void LoadGlobal(lua_State* LuauState);

};

}
