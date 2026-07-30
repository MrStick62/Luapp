#include "Image.h"

#include <array>
#include <filesystem>

#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>
#define STB_IMAGE_WRITE_IMPLEMENTATION
#include <stb_image_write.h>
#include <avir.h>
#include <glad/gl.h>

#include <lua.h>
#include <lualib.h>
#include <luacode.h>

#include "Vec2.h"
#include "LuauHelp.h"

#include "../App.h"
#include "../FileHelp.h"


namespace Luau
{

int Image::New(lua_State* LuauState)
{
   std::filesystem::path FilePath = luaL_checkstring(LuauState, 1);
   std::filesystem::path OutPath = luaL_optstring(LuauState, 2, "");
   float OutScale = luaL_optnumber(LuauState, 3, 1.0f);

   if (FilePath.is_relative())
      FilePath = App::GetPath() / FilePath;

   if (OutPath.string().length() > 0 && OutPath.is_relative())
      OutPath = App::GetPath() / OutPath;

   if (!std::filesystem::exists(FilePath))
   {
      lua_pushnil(LuauState);
      return 1;
   }

   std::string FileString = FileHelp::ReadWholeFile(FilePath.string());
   void* FileData = FileString.data();
   size_t FileSize = FileString.length();

   GLuint ID;

   int Width = 0;
   int Height = 0;

   unsigned char* ImageData = stbi_load_from_memory((const unsigned char*)FileData, FileSize, &Width, &Height, nullptr, 4);

   if (ImageData == nullptr)
      return false;


   if (OutPath.string().length() > 0)
   {
      int NewWidth = Width * OutScale;
      int NewHeight = Height * OutScale;

      std::vector<uint8_t> Output(NewWidth * NewHeight * 4);

      avir::CImageResizer<> Resizer(8);
      Resizer.resizeImage(ImageData, Width, Height, 0, Output.data(), NewWidth, NewHeight, 4, 0);

      std::string FinalPath = OutPath.replace_extension(".png").string();
      if (!stbi_write_png(FinalPath.c_str(), NewWidth, NewHeight, 4, Output.data(), NewWidth * 4))
      {
         stbi_image_free(ImageData);
         lua_pushnil(LuauState);
         return 1;
      }
   
      if (!LoadTextureFromMemory(Output.data(), NewWidth, NewHeight, NewWidth * NewHeight * 4, &ID))
      {
         stbi_image_free(ImageData);
         lua_pushnil(LuauState);
         return 1;
      }
   }
   else 
   {
      if (!LoadTextureFromMemory(ImageData, Width, Height, FileSize, &ID))
      {
         stbi_image_free(ImageData);
         lua_pushnil(LuauState);
         return 1;
      }
   }

   stbi_image_free(ImageData);

   lua_createtable(LuauState, 0, 1);

   luaL_getmetatable(LuauState, "Image");
   lua_setmetatable(LuauState, -2);

   lua_pushinteger(LuauState, ID);
   lua_setfield(LuauState, -2, "ID");

   return 1;
}

int Image::Destroy(lua_State* LuauState)
{   
   luaL_checktype(LuauState, 1, LUA_TTABLE);

   lua_getfield(LuauState, 1, "ID");
   GLuint ImageID = luaL_checkinteger(LuauState, -1);
   lua_pop(LuauState, 1);

   if (ImageID)
   {
      glDeleteTextures(1, &ImageID);
   }

   return 0;
}

int Image::GetSize(lua_State* LuauState)
{
   luaL_checktype(LuauState, 1, LUA_TTABLE);
   lua_getfield(LuauState, 1, "ID");
   GLuint ImageID = luaL_checkinteger(LuauState, -1);

   glBindTexture(GL_TEXTURE_2D, ImageID);

   int Width, Height;
   glGetTexLevelParameteriv(GL_TEXTURE_2D, 0, GL_TEXTURE_WIDTH, &Width);
   glGetTexLevelParameteriv(GL_TEXTURE_2D, 0, GL_TEXTURE_HEIGHT, &Height);

   Vec2 Size(Width, Height);
   Size.LuauPush(LuauState);

   return 1;
}

bool Image::LoadTextureFromMemory(unsigned char* ImageData, int Width, int Height, size_t DataSize, GLuint* OutTexture)
{
   GLuint ImageTexture;
   glGenTextures(1, &ImageTexture);
   glBindTexture(GL_TEXTURE_2D, ImageTexture);

   glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
   glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

   glPixelStorei(GL_UNPACK_ROW_LENGTH, 0);
   glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, Width, Height, 0, GL_RGBA, GL_UNSIGNED_BYTE, ImageData);

   *OutTexture = ImageTexture;

   return true;
}

luaL_Reg Image::Functions[] = {
   { "New", New },
};

luaL_Reg Image::MetaFunctions[] = {
   { "Destroy", Destroy },
   { "GetSize", GetSize },
};

void Image::LoadGlobal(lua_State *LuauState)
{
   LuauHelp::SetupFunctionsGlobal(LuauState, Functions, std::size(Functions), "Image");

   // Image metatable
   luaL_newmetatable(LuauState, "Image");

   lua_pushvalue(LuauState, -1);
   lua_setfield(LuauState, -2, "__index");

   for (const luaL_Reg& Function : MetaFunctions)
   {
      lua_pushcfunction(LuauState, Function.func, Function.name);
      lua_setfield(LuauState, -2, Function.name);
   }

   lua_pop(LuauState, 1);
}

}
