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

#include "../../include/core/Interpreter.h"
#include "../../include/tool/ASTWriter.h"
#include "../../include/tool/ArgParser.h"
#include "../../include/tool/Error.hpp"
#include "../../include/core/Parser.h"
#include "../../include/core/Token.h"
#include "../../include/core/Scanner.h"

using namespace std;

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
    // Attempt to parse the arguments we got into an intermediate object
    // If we received a valid set of arguments from the user, we are good to attempt to run the script
    if (auto args = ArgParser::parseArgs(argc, argv)) {
        // Open the source file we're trying to run
        ifstream sourceFile;
        sourceFile.open(args.value().filename);

        // If we could not open the file, report the error to the user and terminate mash
        if (sourceFile.fail()) {
            cerr << "Failed to open input file: " << args.value().filename << endl;
            return -1;
        }

        // Create a scanner with the source stream
        Scanner scanner(sourceFile);

        // Set up variable for resulting token stream
        vector<Token> *tokens;

        // Attempt to scan the source file into a token stream
        try {
            tokens = scanner.scanTokens();
        } catch (mash::LexError& e) {
            // If we encountered a scanning error, report it to the user, and terminate mash
            cerr << e.what();
            cerr << "Error encountered during lexical analysis, terminating program" << endl;
            return -1;
        }

        // If the user requested debug output from the lexical analysis, print it now
        if (args.value().scannerDebug) {
            cout << "Tokens Scanned:" << endl;
            for (const auto& t: *tokens) {
                cout << t.asString() << endl;
            }
        }

        // Instantiate our parser, and provide it the token stream from our lexical analysis
        Parser parser(*tokens);

        /**
         * @brief Ask the parser to build our abstract syntax tree
         * 
         * Note that this code does not utilize exceptions like the lexical analysis stage does.
         * This is for a very important reason. We would like to try to catch as many syntax errors
         * as possible in one go. So if the parser simply threw an exception to its caller at the
         * first syntax error it found, we could only catch one error at a time. By having the parser
         * simply set a flag instead, we can allow the parser to synchronize itself and catch more
         * errors.
         * 
         */
        vector<unique_ptr<Stmt>> ast = parser.parse();

        if (parser.getErrorState()) {
            cerr << "Encountered error(s) during ast construction, terminating program" << endl;
            return -1;
        }

        // If the user requested debug output from the parsing stage, print it now
        if (args.value().parserDebug) {
            ASTWriter debug(ast, cout);

            debug.write();
        }

        Interpreter interpreter(ast);

        cout << "Walking" << endl;

        interpreter.walk();

    } else {
        return -1;
    }

    return 0;
}
