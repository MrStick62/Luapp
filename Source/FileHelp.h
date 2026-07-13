#pragma once

#include <filesystem>

namespace FileHelp {
   std::filesystem::path GetHomeDirectory();

   std::string ReadWholeFile(const std::string& path);
}

