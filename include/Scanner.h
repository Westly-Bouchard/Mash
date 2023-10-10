/**
 * @file scanner.h
 * @author Westly Bouchard
 * @brief header for the Tokenizer component of the interpreter
 * @version 0.1
 * @date 2023-10-06
 * 
 * @copyright Copyright (c) 2023
 * 
 */

#ifndef SCANNER_H
#define SCANNER_H

#include <fstream>
#include <map>
#include <vector>

#include "../include/Token.h"

class Scanner {
    private:
        std::ifstream * const source;
        std::vector<Token> tokens;

        /**
         * @brief Map keyword strings to their corresponding token type, for matching keyword tokens
         *        in `scanTokens()`
         * 
         */
        static std::map<std::string, TokenType::Type> keywords;

        /**
         * @brief Looks ahead 2 characters from the current location in the stream
         * 
         * @return char the character 2 characters ahead of the current in the stream
         */
        char peekNext();
        
        /**
         * @brief Advances the stream one character forwards and returns the character that was
         *        consumed
         * 
         * @return char the character that was consumed
         */
        char advance();

    public:
        /**
         * @brief Construct a new Scanner object
         * 
         * @param source the source text to be scanned
         */
        Scanner(std::ifstream *source);

        /**
         * @brief Scan the source text and tokenize
         * 
         * @return std::vector<Token*>* the resulting tokens from the source text
         */
        std::vector<Token>* scanTokens();
};

#endif