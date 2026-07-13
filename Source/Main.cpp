#include <iostream>

#include "glad/gl.h"
#include "GLFW/glfw3.h"

constexpr int WINDOW_WIDTH = 800;
constexpr int WINDOW_HEIGHT = 600;

const char* APP_NAME = "Luapp";

int main()
{
   glfwInit();

   glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
   glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
   glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

#ifdef __APPLE__
   glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif

   GLFWwindow* window = glfwCreateWindow(WINDOW_WIDTH, WINDOW_HEIGHT, APP_NAME, NULL, NULL);

   if (!window)
   {
      std::cerr << "Failed to create GLFW window!" << std::endl;

      glfwTerminate();
      return 1;
   }

   glfwMakeContextCurrent(window);

   int version = gladLoadGL(glfwGetProcAddress);

   while (!glfwWindowShouldClose(window))
   {
      glfwPollEvents();

      glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
      glClear(GL_COLOR_BUFFER_BIT);

      glfwSwapBuffers(window);
   }

   return 0;
}
