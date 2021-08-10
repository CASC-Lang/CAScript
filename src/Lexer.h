//
// Created by User on 8/10/2021.
//
#include <string>
#include <utility>
#include "vector"
#include "Token.h"

#ifndef COLLAGE_CPP_LEXER_H
#define COLLAGE_CPP_LEXER_H

namespace collage::syntax {
    class Lexer {
    private:
        unsigned int pos = 0;
        std::string source;
    public:
        explicit Lexer(std::string source) : source(std::move(source)) {}

        std::vector<Token> lex() {
            std::vector<Token> tokens;

            while (pos < source.length()) {
                switch (source[pos]) {
                    case '+':
                        tokens.emplace_back(TokenType::Plus, std::string(1, source[pos++]));
                        break;
                    case ' ':
                    case '\t':
                    case '\n':
                    case '\r':
                        tokens.emplace_back(TokenType::WhiteSpace, std::string(1, source[pos++]));
                        break;
                    default:
                        if (isdigit(source[pos])) {
                            unsigned int start = pos;

                            while (isdigit(source[pos]))
                                pos++;

                            unsigned int len = pos - start;
                            std::string number_literal = source.substr(start, start + len);
                            tokens.emplace_back(TokenType::Number, number_literal);
                        }
                }
            }

            return tokens;
        }
    };
}

#endif //COLLAGE_CPP_LEXER_H
