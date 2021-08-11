//
// Created by ChAoS-UnItY on 8/10/2021.
//

#include "Lexer.h"
#include "Token.h"

using namespace collage;

std::vector<syntax::Token> syntax::Lexer::lex() {
    std::vector<Token> tokens;
    while (pos < source.length()) {
        switch (source[pos]) {
            case '+':
                tokens.emplace_back(TokenType::Plus, source[pos++]);
                break;
            case '-':
                tokens.emplace_back(TokenType::Minus, source[pos++]);
                break;
            case '*':
                tokens.emplace_back(TokenType::Star, source[pos++]);
                break;
            case '/':
                tokens.emplace_back(TokenType::Slash, source[pos++]);
                break;
            case ' ':
            case '\t':
            case '\n':
            case '\r':
                pos++;
                break;
            default:
                if (std::isalpha(source[pos])) {
                    auto start = pos;
                    while (std::isalpha(source[pos++]));

                    auto len = pos - start;
                    auto literal = source.substr(start, len);
                    tokens.emplace_back(literal == "true" || literal == "false" ? TokenType::BoolLiteral : TokenType::Identifier, literal);
                } else if (std::isdigit(source[pos])) {
                    auto start = pos;
                    while (std::isdigit(source[pos++]));

                    auto len = pos - start;
                    auto number_literal = source.substr(start, len);
                    tokens.emplace_back(TokenType::NumberLiteral, number_literal);
                }
                break;
        }
    }
    return tokens;
}