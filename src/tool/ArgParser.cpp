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

#include <cstring>
#include <iostream>

using namespace std;

ArgParser::MashArgs::MashArgs(string filename, bool scannerDebug, bool parserDebug)
    : filename(filename), scannerDebug(scannerDebug), parserDebug(parserDebug) {}

ArgParser::MashArgs::MashArgs(string filename)
    : filename(filename), scannerDebug(false), parserDebug(false) {}

optional<ArgParser::MashArgs> ArgParser::parseArgs(int argc, char* argv[]) {
    
    // If we didn't get any args
    if (argc < 2) {
        cout << ArgParser::info << endl;
        return nullopt;
    }

    if (argc == 2 && strlen(argv[1]) > 5) {
        // If we're trying to run a file
        return ArgParser::MashArgs(argv[1]);
    } else if (argc == 2 && !strcmp(argv[1], "-help")) {
        cout << ArgParser::helpMenu << endl;
        return nullopt;
    } else if (argc == 2) {
        cerr << "Unknown argument: " << argv[1] << endl;
        return nullopt;
    }
    // If we have more than two args, then we have some flags we need to deal with
    // There are only two flags but they can appear in any order

    bool scannerDebug = false;
    bool parserDebug = false;

    for (int i = 1; i < argc - 1; i++) {
        if (!strcmp(argv[i], "-s")) scannerDebug = true;
        else if (!strcmp(argv[i], "-p")) parserDebug = true;
        else {
            cerr << "Unknown argument: " << argv[i] << endl;
            cerr << "Halting Execution" << endl;
            return nullopt;
        }
    }

    return ArgParser::MashArgs(argv[argc - 1], scannerDebug, parserDebug);
}
