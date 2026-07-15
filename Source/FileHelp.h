#pragma once

#include <filesystem>

namespace FileHelp 
{

std::filesystem::path GetHomeDirectory();

std::string ReadWholeFile(const std::string& Path);
bool WriteWholeFile(const std::string& Path, const std::string& Content);

}

