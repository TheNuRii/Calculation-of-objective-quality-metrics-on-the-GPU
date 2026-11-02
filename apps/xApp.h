#pragma once

#include "CommonDef.h"
#include <string>
#include <vector>

class xApp {
public:
    struct CommandLineOptions {
        std::string refFile;
        std::string testFile;
        std::string outputFile = "QMIV.txt";
        int32 numberOfFrames = -1;
        std::string ListOfMetrics = "PSNR";
    };

    static void printUsage(const char* programName);
    static bool parseCommandLine(std::vector<std::string> args, CommandLineOptions& options, std::string& error);
};