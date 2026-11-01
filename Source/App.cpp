 #include "App.h"

#include <cstdlib>
#include <iostream>

#include <lua.h>
#include <luacode.h>
#include <lualib.h>

#include <GLFW/glfw3.h>

#include "FileHelp.h"

#include "Luau/Gui.h"
#include "Luau/Web.h"
#include "Luau/Vec2.h"
#include "Luau/Vec3.h"
#include "Luau/Font.h"
#include "Luau/File.h"
#include "Luau/Draw.h"
#include "Luau/Color.h"
#include "Luau/Flags.h"
#include "Luau/Input.h"
#include "Luau/Image.h"
#include "Luau/Icons.h"
#include "Luau/Config.h"
#include "Luau/Window.h"
#include "Luau/GlobalFuncs.h"

lua_State* App::LuauState;
std::filesystem::path App::Path;
std::string App::AppName;

const std::string App::EntryPointName = "Main.luau";
const std::string App::DirectoryName = "Luapp";

float App::MaxFrameRate = 60.0f;
float App::IdleFrameRate = 10.0f;

void App::Init(const std::string& Name, GLFWwindow* Window)
{
   // Set path
#ifdef LOCAL_APP_PATH
   AppName = std::filesystem::path(Name).filename().string();
   Path = std::filesystem::path(Name).parent_path();
#else
   AppName = Name;
   Path = FileHelp::GetHomeDirectory() / "Documents" / DirectoryName / Name;
#endif

   // Initialize Luau
   LuauState = luaL_newstate();
   luaL_openlibs(LuauState);

   Luau::GlobalFuncs::LoadGlobal(LuauState);
   
   Luau::Web::LoadGlobal(LuauState);
   Luau::Gui::LoadGlobal(LuauState);
   Luau::Vec2::LoadGlobal(LuauState);
   Luau::Vec3::LoadGlobal(LuauState);
   Luau::Font::LoadGlobal(LuauState);
   Luau::File::LoadGlobal(LuauState);
   Luau::Draw::LoadGlobal(LuauState);
   Luau::Color::LoadGlobal(LuauState);
   Luau::Flags::LoadGlobal(LuauState);
   Luau::Input::LoadGlobal(LuauState);
   Luau::Image::LoadGlobal(LuauState);
   Luau::Icons::LoadGlobal(LuauState);
   Luau::Window::SetCurrentWindow(Window);
   Luau::Window::LoadGlobal(LuauState);
   Luau::Config::LoadGlobal(LuauState);

#ifdef LOCAL_APP_PATH
   std::string MainContent = FileHelp::ReadWholeFile(Name);
#else
   std::string MainContent = FileHelp::ReadWholeFile((Path / EntryPointName).string());
#endif

   size_t BytecodeSize;
   char* Bytecode = luau_compile(MainContent.data(), MainContent.length(), NULL, &BytecodeSize);
   int result = luau_load(LuauState, Name.data(), Bytecode, BytecodeSize, 0);

   lua_pcall(LuauState, 0, 0, 0);

   free(Bytecode);
}

void App::Main()
{
   lua_getglobal(LuauState, "Main");

   if (!lua_isfunction(LuauState, -1))
   {
      lua_pop(LuauState, 1);
      return;
   }

   lua_pcall(LuauState, 0, 0, 0);
}

void App::Tick(float DeltaTime)
{
   lua_getglobal(LuauState, "Tick");

   if (!lua_isfunction(LuauState, -1))
   {
       lua_pop(LuauState, 1);
       return;
   }

   lua_pushnumber(LuauState, DeltaTime);
   lua_pcall(LuauState, 1, 0, 0);
}

void App::OnGui(float DeltaTime)
{
   lua_getglobal(LuauState, "OnGui");

   if (!lua_isfunction(LuauState, -1))
   {
       lua_pop(LuauState, 1);
       return;
   }

   lua_pushnumber(LuauState, DeltaTime);
   lua_pcall(LuauState, 1, 0, 0);

   Luau::Gui::HandleDragDrop(LuauState);
}

void App::Render(float DeltaTime)
{
   Luau::Draw::RenderDrawData();
}

void App::OnExit()
{
   lua_getglobal(LuauState, "OnExit");

   if (!lua_isfunction(LuauState, -1))
   {
       lua_pop(LuauState, 1);
       return;
   }

   lua_pcall(LuauState, 0, 0, 0);
}
