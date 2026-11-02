#include "../apps/xApp.h"

#include <cassert>
#include <vector>

int main() {
    std::vector<std::string> args = {
        "QMIV",
        "-i0",
        "SA_ref.yuv",
        "-i1",
        "SA_test.yuv",
        "-nf",
        "20",
        "-r",
        "QMIV.txt",
        "-ml",
        "PSNR"
    };

    xApp::CommandLineOptions config;
    std::string error;
    const bool ok = xApp::parseCommandLine(args, config, error);

    assert(ok);
    assert(config.refFile == "SA_ref.yuv");
    assert(config.testFile == "SA_test.yuv");
    assert(config.numberOfFrames == 20);
    assert(config.outputFile == "QMIV.txt");
    assert(config.ListOfMetrics == "PSNR");
    return 0;
}
