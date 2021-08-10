//
// Created by ChAoS-UnItY on 8/10/2021.
//

#ifndef COLLAGE_CPP_LEXER_H
#define COLLAGE_CPP_LEXER_H

#include <string>
#include <string_view>
#include <utility>
#include <vector>

#include "Token.h"

namespace collage::syntax {
    class Lexer {
    private:
        std::string source;
        std::string::size_type pos = 0;
    public:
        explicit Lexer(std::string source) : source(std::move(source)) {}

        std::vector<Token> lex() {
            std::vector<Token> tokens;
            while (pos < source.length()) {
                switch (source[pos]) {
                    case '+':
                        tokens.emplace_back(TokenType::Plus, source[pos++]);
                        break;
                    case ' ':
                    case '\t':
                    case '\n':
                    case '\r':
                        tokens.emplace_back(TokenType::WhiteSpace, source[pos++]);
                        break;
                    default:
                        if (std::isdigit(source[pos])) {
                            auto start = pos;

                            while (std::isdigit(source[pos]))
                                pos++;

                            auto len = pos - start;
                            auto number_literal = source.substr(start, start + len);
                            tokens.emplace_back(TokenType::Number, number_literal);
                        }
                }
            }
            return std::move(tokens);
        }
    };
}

#endif //COLLAGE_CPP_LEXER_H
