#include "xApp.h"

#include <sstream>
#include <stdexcept>

namespace {

bool parseIntValue(const std::string& value, int32& out) {
    std::stringstream stream(value);
    stream >> out;
    return !stream.fail() && stream.eof();
}

}  // namespace

void xApp::printUsage(const char* programName) {
    const std::string name = programName ? programName : "GPULQ";
    fmt::print("Usage: {} [-i0 ref.yuv] [-i1 test.yuv] [-nf frames] [-r result.txt] [-ml \"PSNR,WSPSNR,IVPSNR,IVSSIM\"]\n", name);
}

bool xApp::parseCommandLine(std::vector<std::string> args, CommandLineOptions& options, std::string& error) {
    error.clear();

    size_t startIndex = 0;
    if (!args.empty() && args[0] != "-i0" && args[0] != "-i1" && args[0] != "-nf" &&
        args[0] != "-r" && args[0] != "-ml" && args[0] != "-h" && args[0] != "--help") {
        startIndex = 1;
    }

    for (size_t i = startIndex; i < args.size(); ++i) {
        const std::string& arg = args[i];

        if (arg == "-i0") {
            if (i + 1 >= args.size()) {
                error = "Missing value after '-i0'.";
                return false;
            }
            options.refFile = args[++i];
            continue;
        }

        if (arg == "-i1") {
            if (i + 1 >= args.size()) {
                error = "Missing value after '-i1'.";
                return false;
            }
            options.testFile = args[++i];
            continue;
        }

        if (arg == "-nf") {
            if (i + 1 >= args.size()) {
                error = "Missing value after '-nf'.";
                return false;
            }
            if (!parseIntValue(args[++i], options.numberOfFrames)) {
                error = "Invalid value for '-nf'. Expected integer.";
                return false;
            }
            continue;
        }

        if (arg == "-r") {
            if (i + 1 >= args.size()) {
                error = "Missing value after '-r'.";
                return false;
            }
            options.outputFile = args[++i];
            continue;
        }

        if (arg == "-ml") {
            if (i + 1 >= args.size()) {
                error = "Missing value after '-ml'.";
                return false;
            }
            options.ListOfMetrics = args[++i];
            continue;
        }

        if (arg == "-h" || arg == "--help") {
            printUsage(args.empty() ? "QMIV" : args[0].c_str());
            return false;
        }

        error = "Unknown argument: " + arg;
        return false;
    }

    if (options.refFile.empty()) {
        error = "Missing required argument '-i0'.";
        return false;
    }

    if (options.testFile.empty()) {
        error = "Missing required argument '-i1'.";
        return false;
    }

    return true;
};