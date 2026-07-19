#pragma once

#include <filesystem>

namespace FileHelp 
{

std::filesystem::path GetHomeDirectory();
std::filesystem::path GetProjectDirectory();
std::filesystem::path GetExecutableDirectory();

std::string ReadWholeFile(const std::string& Path);
bool WriteWholeFile(const std::string& Path, const std::string& Content);

}

