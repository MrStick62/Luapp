#include "Draw.h"

#include <iostream>
#include <filesystem>

#include <lua.h>
#include <lualib.h>
#include <luacode.h>

#include <glad/gl.h>

#include "Vec3.h"
#include "Color.h"
#include "LuauHelp.h"

#include "../FileHelp.h"

namespace Luau
{

struct Line
{
   Vec3 V1;
   Color C1;

   Vec3 V2;
   Color C2;

   Line(Vec3 V1, Vec3 V2, Color Col): V1(V1), V2(V2), C1(Col), C2(Col) {};
   Line(Vec3 V1, Vec3 V2, Color C1, Color C2): V1(V1), V2(V2), C1(C1), C2(C2) {};
};

std::vector<Line> Draw::Lines = {};
unsigned int Draw::ShaderProgram = 0;

int Draw::DrawLine(lua_State* LuauState)
{
   Vec3 V1 = Vec3::LuauCheck(LuauState, 1);
   Vec3 V2 = Vec3::LuauCheck(LuauState, 2);
   Color C1 = Color::LuauCheck(LuauState, 3);
   Color C2 = C1;

   Color::LuauOpt(LuauState, 4, &C2);
   
   Lines.push_back(Line(V1, V2, C1, C2));

   return 0;
}

luaL_Reg Draw::Functions[] = {
   { "DrawLine", DrawLine },
};

void Draw::LoadGlobal(lua_State* LuauState)
{
   LuauHelp::SetupFunctionsGlobal(LuauState, Functions, std::size(Functions), "Draw");

   std::filesystem::path VertexPath = FileHelp::GetProjectDirectory() / "Assets" / "Shaders" / "Line.vert";
   std::filesystem::path FragmentPath = FileHelp::GetProjectDirectory() / "Assets" / "Shaders" / "Line.frag";

   std::string VertexString = FileHelp::ReadWholeFile(VertexPath.string());
   const char* VertexSource = VertexString.c_str();

   std::string FragmentString = FileHelp::ReadWholeFile(FragmentPath.string());
   const char* FragmentSource = FragmentString.c_str();

   unsigned int VertexShader = glCreateShader(GL_VERTEX_SHADER);
   glShaderSource(VertexShader, 1, &VertexSource, NULL);
   glCompileShader(VertexShader);

   int Success;
   char Log[512];
   glGetShaderiv(VertexShader, GL_COMPILE_STATUS, &Success);
   if (!Success)
   {
      glGetShaderInfoLog(VertexShader, 512, NULL, Log);
      std::cerr << "Failed to compile line vertex shader!" << std::endl;
   }

   unsigned int FragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
   glShaderSource(FragmentShader, 1, &FragmentSource, NULL);
   glCompileShader(FragmentShader);

   glGetShaderiv(FragmentShader, GL_COMPILE_STATUS, &Success);
   if (!Success)
   {
      glGetShaderInfoLog(FragmentShader, 512, NULL, Log);
      std::cerr << "Failed to compile line fragment shader!" << std::endl;
   }

   ShaderProgram = glCreateProgram();
   glAttachShader(ShaderProgram, VertexShader);
   glAttachShader(ShaderProgram, FragmentShader);
   glLinkProgram(ShaderProgram);


   glGetShaderiv(ShaderProgram, GL_COMPILE_STATUS, &Success);
   if (!Success)
   {
      glGetShaderInfoLog(ShaderProgram, 512, NULL, Log);
      std::cerr << "Failed to compile line shader program!" << std::endl;
   }

   glDeleteShader(VertexShader);
   glDeleteShader(FragmentShader);
}

void Draw::RenderDrawData()
{
   unsigned int VAO, VBO;
   glGenVertexArrays(1, &VAO);
   glGenBuffers(1, &VBO);

   glBindVertexArray(VAO);
   glBindBuffer(GL_ARRAY_BUFFER, VBO);
   glBufferData(GL_ARRAY_BUFFER, 14 * sizeof(float) * Lines.size(), Lines.data(), GL_STATIC_DRAW);

   glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 7 * sizeof(float), (void*)0);
   glEnableVertexAttribArray(0);
   glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, 7 * sizeof(float), (void*)(3 * sizeof(float)));
   glEnableVertexAttribArray(1);

   glUseProgram(ShaderProgram);
   glDrawArrays(GL_LINES, 0, Lines.size() * 2);

   glDeleteVertexArrays(1, &VAO);
   glDeleteBuffers(1, &VBO);

   Lines.clear();
}

}
