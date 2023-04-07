//  2006-2008 (c) Viva64.com Team
//  2008-2020 (c) OOO "Program Verification Systems"
//  2020-2023 (c) PVS-Studio LLC

#pragma once

#include <functional>
#include <memory>
#include <set>
#include <string>
#include <vector>

namespace PlogConverter
{

enum class SecurityCodeMapping
{
  CWE,
  MISRA,
  OWASP,
  AUTOSAR
};

enum class PathTransformationMode
{
  ToAbsolute,
  ToRelative,
  NoTransform
};

struct Analyzer;
class BaseFormatOutput;

struct ProgramOptions
{
  using AllocFunction = std::function<std::unique_ptr<BaseFormatOutput>(const ProgramOptions&)>;

  std::string                                 cmdLine;
  std::vector<std::string>                    inputFiles;
  std::string                                 output;
  std::string                                 configFile;
  std::vector<AllocFunction>                  formats;
  std::vector<SecurityCodeMapping>            codeMappings;
  std::set<std::string>                       disabledWarnings;
  std::vector<std::string>                    disabledPaths;
  std::vector<std::string>                    enabledPaths;
  std::set<std::string>                       disabledKeywords;
  std::vector<Analyzer>                       enabledAnalyzers;
  std::vector<std::string>                    enabledFiles;
  std::set<std::string>                       misraDivations;
  std::vector<uint32_t>                       enabledWarnings;
  std::string                                 projectRoot = ".";
  std::string                                 outputName;
  std::string                                 projectName;
  std::string                                 projectVersion;
  std::string                                 grp;
  PathTransformationMode                      pathTransformationMode { PathTransformationMode::NoTransform };
  bool                                        useStdout = false;
  bool                                        useStderr = false;
  bool                                        noHelp = false;
  bool                                        indicateWarnings = false;
  bool                                        separateNonCriticalToInfo = false;
};

}
