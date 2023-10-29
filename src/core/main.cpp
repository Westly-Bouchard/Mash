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
#include "../../include/tool/ArgParser.h"
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

    optional<ArgParser::MashArgs> args = ArgParser::parseArgs(argc, argv);

    if (args) {
        ifstream sourceFile;
        sourceFile.open(args.value().filename);

        if (sourceFile.fail()) {
            cerr << "Failed to open input file: " << args.value().filename << endl;
            return -1;
        }

        Scanner scanner(sourceFile);

        vector<Token> *tokens = scanner.scanTokens();

        if (args.value().scannerDebug) {
            cout << "Tokens Scanned:" << endl;
            for (auto t: *tokens) {
                cout << t.asString() << endl;
            }
        }

        Parser parser(*tokens);

        vector<unique_ptr<Stmt>> ast = parser.parse();

        if (args.value().parserDebug) {
            ASTWriter debug(ast, cout);

            debug.write();
        }

    } else {
        return 0;
    }
}
