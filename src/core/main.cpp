/**
 * @file main.cpp
 * @author Westly Bouchard (westly_bouchard@mines.edu)
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
#include <memory>
#include <string>
#include <vector>

#include "../../include/tool/ASTWriter.h"
#include "../../include/core/Parser.h"
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

    Scanner scanner(sourceFile);

    vector<Token> *tokens = scanner.scanTokens();

    for (auto t : *tokens) {
        cout << t.asString() << endl;
    }

    Parser parser(*tokens);

    vector<unique_ptr<Stmt>> ast = parser.parse();

    ASTWriter debug(ast, cout);

    debug.write();
}
