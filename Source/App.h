#pragma once

#include <filesystem>

class lua_State;
class GLFWwindow;

class App 
{
private:
   lua_State* LuauState;

   std::filesystem::path Path;

   static const std::string EntryPointName;
   static const std::string DirectoryName;

public:
   App(const std::string& Name, GLFWwindow* Window);

   void Main();
   void Tick(float DeltaTime);
   void OnGui(float DeltaTime);

   std::filesystem::path GetPath() const { return Path; };
};
