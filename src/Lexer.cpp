#include "Lexer.h"

#include "Token.h"

std::vector<collage::syntax::Token> collage::syntax::Lexer::lex() {
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
                    while (std::isdigit(source[pos++]));

                    auto len = pos - start;
                    auto number_literal = source.substr(start, len);
                    tokens.emplace_back(TokenType::Number, number_literal);
                }
                break;
        }
    }
    return std::move(tokens);
}