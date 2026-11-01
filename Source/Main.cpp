#include <iostream>
#include <chrono>
#include <thread>

#include <glad/gl.h>
#include <GLFW/glfw3.h>

#include <imgui/imgui.h>
#include <imgui/imgui_impl_glfw.h>
#include <imgui/imgui_impl_opengl3.h>

#include "App.h"
#include "Setup.h"

constexpr int WINDOW_WIDTH = 800;
constexpr int WINDOW_HEIGHT = 600;

const char* APP_NAME = "Luapp";

void FramebufferSizeCallback(GLFWwindow* Window, int Width, int Height);
void DrawWindow(GLFWwindow* Window);

int main(int argc, char* argv[])
{
#ifdef LUAU_ENTRY_POINT
   std::string ProgramName = LUAU_ENTRY_POINT;
#else
   if (argc < 2)
   {
      std::cerr << "Path not specified!" << std::endl;
      return 1;
   }

   if (!strcmp(argv[1], "--setup"))
   {
      if (argc < 3)
      {
         std::cerr << "Path not specified!" << std::endl;
         return 1;
      }

      Setup::Run(argv[2]);
      return 0;
   }

   std::string ProgramName(argv[1]);
#endif

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
   glfwSetFramebufferSizeCallback(Window, FramebufferSizeCallback);

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

   App::Init(ProgramName, Window);
   App::Main();

   /**
    *    Main loop
    */

   float DeltaTime = 1.0f;

   glEnable(GL_DEPTH_TEST);

   while (!glfwWindowShouldClose(Window))
   {
      if (glfwGetWindowAttrib(Window, GLFW_FOCUSED))
      {
         glfwPollEvents();

         DrawWindow(Window);
      }
      else
      {
         glfwWaitEvents();
      }
   }

   App::OnExit();

   ImGui_ImplOpenGL3_Shutdown();
   ImGui_ImplGlfw_Shutdown();
   
   glfwTerminate();

   return 0;
}

void DrawWindow(GLFWwindow* Window)
{
   static auto LastFrameStart = std::chrono::steady_clock::now();

   auto FrameStart = std::chrono::steady_clock::now();
   double DeltaTime = std::chrono::duration<double>(FrameStart - LastFrameStart).count();
 
   App::Tick(DeltaTime);

   ImGui_ImplOpenGL3_NewFrame();
   ImGui_ImplGlfw_NewFrame();
   ImGui::NewFrame();

   App::OnGui(DeltaTime);

   ImGui::Render();

   glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
   glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

   App::Render(DeltaTime);
   ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

   glfwSwapBuffers(Window);

   LastFrameStart = FrameStart;
}

void FramebufferSizeCallback(GLFWwindow* Window, int Width, int Height)
{
   glViewport(0, 0, Width, Height);

   DrawWindow(Window);
}
