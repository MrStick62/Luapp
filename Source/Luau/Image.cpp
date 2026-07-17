#include "image.h"

#include <array>

#include <stb_image.h>

#include <lua.h>
#include <lualib.h>
#include <luacode.h>

#include "../FileHelp.h"

namespace Luau
{

int Image::Load(lua_State* LuauState)
{
   const char* FilePath = luaL_checkstring(LuauState, 1);

   std::string FileString = FileHelp::ReadWholeFile(std::string(FilePath));
   void* FileData = FileString.data();
   size_t FileSize = FileString.length();

   GLuint ID;

   if (!LoadTextureFromMemory(FileData, FileSize, &ID))
   {
      luaL_error(LuauState, "Failed to load image \"%s\"!", FilePath); 
      return 0;
   }

   lua_pushinteger(LuauState, ID);

   return 1;
}

bool Image::LoadTextureFromMemory(const void* Data, size_t DataSize, GLuint* OutTexture)
{
   int Width = 0;
   int Height = 0;

   unsigned char* ImageData = stbi_load_from_memory((const unsigned char*)Data, DataSize, &Width, &Height, nullptr, 4);
   if (ImageData == nullptr)
      return false;

   GLuint ImageTexture;
   glGenTextures(1, &ImageTexture);
   glBindTexture(GL_TEXTURE_2D, ImageTexture);

   glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
   glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

   glPixelStorei(GL_UNPACK_ROW_LENGTH, 0);
   glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, Width, Height, 0, GL_RGBA, GL_UNSIGNED_BYTE, ImageData);
   stbi_image_free(ImageData);

   *OutTexture = ImageTexture;

   return true;
}

luaL_Reg Image::Functions[] = {
   { "Load", Load },
};

void Image::LoadGlobal(lua_State *LuauState)
{
   lua_createtable(LuauState, 0, std::size(Functions));

   for (const luaL_Reg& Function : Functions)
   {
      lua_pushcfunction(LuauState, Function.func, Function.name);
      lua_setfield(LuauState, -2, Function.name);
   }

   lua_setglobal(LuauState, "Image");
}

}
