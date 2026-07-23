#pragma once

#include <filesystem>

class lua_State;
class GLFWwindow;

class App 
{
private:
   static lua_State* LuauState;

   static std::string AppName;
   static std::filesystem::path Path;

   static const std::string EntryPointName;
   static const std::string DirectoryName;

   static float MaxFrameRate;
   static float IdleFrameRate;

public:
   static void Init(const std::string& Name, GLFWwindow* Window);

   static void Main();
   static void Tick(float DeltaTime);
   static void OnGui(float DeltaTime);
   static void OnExit();

   static std::string GetName() { return AppName; }
   static std::filesystem::path GetPath() { return Path; }

   static float GetMaxFrameRate() { return MaxFrameRate; };
   static float GetIdleFrameRate() { return IdleFrameRate; };
};
