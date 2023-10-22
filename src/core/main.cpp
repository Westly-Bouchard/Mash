/**
 * @file main.cpp
 * @author Westly Bouchard
 * @brief Contains the entry point for the Mash interpreter. Handles reading command line arguments,
 *        and passing data between different interpreter passes.
 * @version 0.1
 * @date 2023-10-06
 * 
 * @copyright Copyright (c) 2023
 * 
 */

#include <iostream>
#include <fstream>
#include <string>
#include <vector>

#include "../../include/core/Token.h"
#include "../../include/core/Scanner.h"

using namespace std;

int main(int argc, char *argv[]) {

    // If we didn't get an argument then we exit the program and notify the user
    if (argc < 2) {
        cout << "Usage: mash `filename`" << endl;
        return 0;
    }

    // Grab the path of the file the user wants to execute
    string sourcePath = argv[1];

    // Create an ifstream object to read from the file
    ifstream sourceFile;
    sourceFile.open(sourcePath, ios::in);

    // If for some reason we weren't able to open the file, 
    if (sourceFile.fail()) {
        cerr << "Failed to open input file: " + sourcePath << endl;
        return -1;
    }

    Scanner *scanner = new Scanner(sourceFile);

    vector<Token> *tokens = scanner->scanTokens();

    for (auto t : *tokens) {
        cout << t.asString() << endl;
    }
}