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

void displayHelpMenu();

/**
 * Mash Command Line Arguments
 * 
 * Basic usage: $ mash <args> `filename`
 * 
 * `-s` DEBUG: Print token stream from scanner
 * `-p` DEBUG: Print AST generated from parser
 * 
 * `-help` Display help menu
 */
int main(int argc, char *argv[]) {

    // If we didn't get an argument then we exit the program and notify the user
    if (argc < 2) {
        cout << "Usage: mash `filename`.mash" << endl;
        cout << "Run `mash -help for full argument list" << endl;
        return 0;
    } else if (argc == 2) {
        // If we received two arguments, we either want to run the file or display the help menu

        // If we have a file the length of the argument will be greater than 5 characters because
        // it will have to be some string + `.mash`
        if (strlen(argv[1]) > 5) {

        } else if (strcmp(argv[1]))
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

    // for (auto t : *tokens) {
    //     cout << t.asString() << endl;
    // }

    Parser parser(*tokens);

    vector<unique_ptr<Stmt>> ast = parser.parse();

    ASTWriter debug(ast, cout);

    debug.write();
}
