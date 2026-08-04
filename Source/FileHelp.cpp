#include "FileHelp.h"

#include <ios>
#include <fstream>
#include <sstream>
#include <stdexcept>

#ifdef _WIN32
#include <windows.h>
#elif __APPLE__
#include <mach-o/dyld.h>
#elif __linux__
#include <unistd.h>
#endif

namespace FileHelp 
{

std::filesystem::path GetHomeDirectory()
{   
#ifdef _WIN32
   if (const char* Home = std::getenv("USERPROFILE"))
#else
   if (const char* Home = std::getenv("HOME"))
#endif
   {
      return Home;
   }

   return {};
}

std::filesystem::path GetProjectDirectory()
{
   return std::filesystem::path(SOURCE_DIR);
}

std::filesystem::path GetExecutableDirectory()
{
#ifdef _WIN32
   wchar_t Buffer[1024];
   if (GetModuleFileNameW(nullptr, Buffer, 1024))
   {
      return std::filesystem::path(Buffer).parent_path();
   }
#elif __APPLE__
   uint32_t Size = 0;
   _NSGetExecutablePath(nullptr, &Size);
   std::vector<char> Buffer(Size);
   if (!_NSGetExecutablePath(Buffer.data(), &Size))
   {
      char OutPath[1024];
      if (realpath(Buffer.data(), OutPath))
      {
         return std::filesystem::path(OutPath).parent_path();
      }
   }
#elif __linux__
   char Buffer[1024];
   if (readlink("/proc/self/exe", Buffer, sizeof(Buffer)))
   {
      return std::filesystem::path(Buffer).parent_path();
   }
#endif
   return {};
}

std::string ReadWholeFile(const std::string& Path)
{
   std::ifstream File(Path, std::ios::binary);

   if (!File)
   {
      std::stringstream ErrorMsg;
      ErrorMsg << "Failed to open file " << Path << "!";
      throw std::runtime_error(ErrorMsg.str());
   }

   File.seekg(0, std::ios::end);
   std::streamsize Size = File.tellg();
   File.seekg(0, std::ios::beg);

   std::string Content(Size, '\0');

   if (!File.read(Content.data(), Size))
   {
      std::stringstream ErrorMsg;
      ErrorMsg << "Failed to read file " << Path << "!";
      throw std::runtime_error(ErrorMsg.str());
   }

   return Content;
}

bool WriteWholeFile(const std::string& Path, const std::string& Content)
{
   std::ofstream File(Path, std::ios::binary);

   if (!File)
   {
      std::stringstream ErrorMsg;
      ErrorMsg << "Failed to open file " << Path << "!";
      throw std::runtime_error(ErrorMsg.str());
   }

   File << Content.data();

   return true;
}

}
