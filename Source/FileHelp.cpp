#include "FileHelp.h"

#include <ios>
#include <fstream>
#include <sstream>
#include <stdexcept>

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
