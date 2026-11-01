#pragma once

#include <vector>

class luaL_Reg;
class lua_State;

namespace Luau
{

struct Line;

class Draw 
{
private:
   static luaL_Reg Functions[];

   static int DrawLine(lua_State* LuauState);

   static std::vector<Line> Lines;

   static unsigned int ShaderProgram;

public:
   static void LoadGlobal(lua_State* LuauState);

   static void RenderDrawData();
};

}
