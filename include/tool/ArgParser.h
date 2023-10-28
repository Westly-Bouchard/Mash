/**
 * @file ArgParser.h
 * @author Westly Bouchard (westly_bouchard@mines.edu)
 * @brief Utility for parsing command line arguments
 * @version 0.1
 * @date 2023-10-27
 * 
 * @copyright Copyright (c) 2023
 * 
 */

#ifndef ARG_PARSER_H
#define ARG_PARSER_H

#include <optional>
#include <string>

namespace ArgParser {

    const string info = "Mash (Mini-Bash): A small language for automating tasks around your computer\
                        \nVersion: 0.1";

    const string helpMenu;

    class MashArgs {
        public:
            bool scannerDebug;
            bool parserDebug;
            std::string filename;

            MashArgs(std::string filename, bool scannerDebug, bool parserDebug);
            MashArgs(std::string filename);
    };

    std::optional<MashArgs> parseArgs(int argc, char* argv[]);

}

#endif