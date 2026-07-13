#include <iostream>

#include <glad/gl.h>
#include <GLFW/glfw3.h>

#include <imgui/imgui.h>
#include <imgui/imgui_impl_glfw.h>
#include <imgui/imgui_impl_opengl3.h>

#include "App.h"

constexpr int WINDOW_WIDTH = 800;
constexpr int WINDOW_HEIGHT = 600;

const char* APP_NAME = "Luapp";

int main(int argc, char* argv[])
{
   if (argc < 2)
   {
      std::cerr << "Application not specified!" << std::endl;
      return 1;
   }

   std::string ProgramName(argv[1]);

   /**
    *    Initialize GLFW/WINDOW
    */

   glfwInit();

   glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
   glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
   glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

#ifdef __APPLE__
   glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif

   GLFWwindow* Window = glfwCreateWindow(WINDOW_WIDTH, WINDOW_HEIGHT, APP_NAME, NULL, NULL);

   if (!Window)
   {
      std::cerr << "Failed to create GLFW window!" << std::endl;
      glfwTerminate();
      return 1;
   }

   glfwMakeContextCurrent(Window);

   /**
    *    Initialize GLAD
    */

   int Version = gladLoadGL(glfwGetProcAddress);

   if (!Version)
   {
      std::cerr << "Failed to initialize GLAD!" << std::endl;
      glfwTerminate();
      return 1;
   }

   /**
    *    Initialize ImGui
    */

   ImGui::CreateContext();
   ImGui::StyleColorsDark();

   ImGuiStyle& Style = ImGui::GetStyle();
   float MainScale = ImGui_ImplGlfw_GetContentScaleForMonitor(glfwGetPrimaryMonitor());

   Style.ScaleAllSizes(MainScale);
   Style.FontScaleDpi = MainScale;

   ImGui_ImplGlfw_InitForOpenGL(Window, true);
   ImGui_ImplOpenGL3_Init("#version 330");

   /**
    *    Setup Luau app
    */

   App LuauApp(ProgramName, Window);
   LuauApp.Main();

   /**
    *    Main loop
    */

   while (!glfwWindowShouldClose(Window))
   {
      glfwPollEvents();

      LuauApp.Tick(0);

      ImGui_ImplOpenGL3_NewFrame();
      ImGui_ImplGlfw_NewFrame();
      ImGui::NewFrame();

      LuauApp.OnGui(0);

      ImGui::Render();

      int WindowWidth, WindowHeight;
      glfwGetFramebufferSize(Window, &WindowWidth, &WindowHeight);
      glViewport(0, 0, WindowWidth, WindowHeight);
      
      glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
      glClear(GL_COLOR_BUFFER_BIT);

      ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

      glfwSwapBuffers(Window);
   }
   
   glfwTerminate();

   return 0;
}
