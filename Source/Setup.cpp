#include "Setup.h"

#include <fstream>
#include <filesystem>

#include "FileHelp.h"

namespace Setup
{

void Run(const std::string& TargetPath)
{
   std::filesystem::path Path(TargetPath);
   std::filesystem::create_directories(Path / ".vscode");
   std::filesystem::create_directories(Path / "types");

   std::filesystem::path Project(FileHelp::GetProjectDirectory());
   std::string SettingsContent = FileHelp::ReadWholeFile((Project / "Definitions" / ".vscode" / "settings.json").string());
   std::string TypesContent = FileHelp::ReadWholeFile((Project / "Definitions" / "types" / "types.d.lua").string());

   FileHelp::WriteWholeFile((Path / ".vscode" / "settings.json").string(), SettingsContent);
   FileHelp::WriteWholeFile((Path / "types" / "types.d.lua").string(), TypesContent);
}

}
