/**
 * @file ArgParser.cpp
 * @author Westly Bouchard (westly_bouchard@mines.edu)
 * @brief Implementation for arg parsing util
 * @version 0.1
 * @date 2023-10-27
 * 
 * @copyright Copyright (c) 2023
 * 
 */

#include "../../include/tool/ArgParser.h"

#include <iostream>

using namespace std;

ArgParser::MashArgs::MashArgs(string filename, bool scannerDebug, bool parserDebug)
    : filename(filename), scannerDebug(scannerDebug), parserDebug(parserDebug) {}

ArgParser::MashArgs::MashArgs(string filename)
    : filename(filename), scannerDebug(false), parserDebug(false) {}

optional<ArgParser::MashArgs> parseArgs(int argc, char* argv[]) {
    
    // If we didn't get any args
    if (argc < 2) {
        cout << ArgParser::info << endl;
        return nullopt;
    }

    if (argc == 2 && strlen(argv[1]) > 5) {
        // If we're trying to run a file
        return ArgParser::MashArgs(argv[1]);
    } else if (argc == 2 && strcmp(argv[1], "-help")) {
        cout << ArgParser::helpMenu << endl;
        return nullopt;
    }
}