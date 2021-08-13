//
// Created by ChAoS-UnItY on 8/10/2021.
//

#include "syntax/Lexer.h"
#include "syntax/Token.h"

using namespace cascript;

std::vector<syntax::Token> syntax::Lexer::lex() {
    std::vector<Token> tokens;
    while (pos < source.length()) {
        switch (source[pos]) {
            case '(':
                tokens.emplace_back(TokenType::OpenParenthesis, source[pos++]);
                break;
            case ')':
                tokens.emplace_back(TokenType::CloseParenthesis, source[pos++]);
                break;
            case '?':
                tokens.emplace_back(TokenType::QuestionMark, source[pos++]);
                break;
            case ':':
                tokens.emplace_back(TokenType::Colon, source[pos++]);
                break;
            case '=':
                if (source[pos + 1] == '=') {
                    tokens.emplace_back(TokenType::DoubleEqual, source.substr(pos, pos + 2));
                    pos += 2;
                } else {
                    pos++;
                }
                break;
            case '!':
                if (source[pos + 1] == '=') {
                    tokens.emplace_back(TokenType::BangEqual, source.substr(pos, pos + 2));
                    pos += 2;
                } else {
                    tokens.emplace_back(TokenType::Bang, source[pos++]);
                }
                break;
            case '>':
                if (source[pos + 1] == '>') {
                    if (source[pos + 2] == '>') {
                        tokens.emplace_back(TokenType::TripleGreaterThan, source.substr(pos, pos + 3));
                        pos += 3;
                    } else {
                        tokens.emplace_back(TokenType::DoubleGreaterThan, source.substr(pos, pos + 2));
                        pos += 2;
                    }
                } else if (source[pos + 1] == '=') {
                    tokens.emplace_back(TokenType::GreaterEqualThan, source.substr(pos, pos + 2));
                } else {
                    tokens.emplace_back(TokenType::GreaterThan, source[pos++]);
                }
                break;
            case '<':
                if (source[pos + 1] == '<') {
                    tokens.emplace_back(TokenType::DoubleLessThan, source.substr(pos, pos + 2));
                    pos += 2;
                } else if (source[pos + 1] == '=') {
                    if (source[pos + 2] == '>') {
                        tokens.emplace_back(TokenType::LessEqualGreater, source.substr(pos, pos + 3));
                        pos += 3;
                    } else {
                        tokens.emplace_back(TokenType::LessEqualThan, source.substr(pos, pos + 2));
                        pos += 2;
                    }
                } else {
                    tokens.emplace_back(TokenType::LessThan, source[pos++]);
                }
                break;
            case '&':
                if (source[pos + 1] == '&') {
                    tokens.emplace_back(TokenType::DoubleAmpersand, source.substr(pos, pos + 2));
                    pos += 2;
                } else {
                    tokens.emplace_back(TokenType::Ampersand, source[pos++]);
                }
                break;
            case '^':
                tokens.emplace_back(TokenType::Caret, source[pos++]);
                break;
            case '|':
                if (source[pos + 1] == '|') {
                    tokens.emplace_back(TokenType::DoublePipe, source.substr(pos, pos + 2));
                    pos += 2;
                } else {
                    tokens.emplace_back(TokenType::Pipe, source[pos++]);
                }
                break;
            case '~':
                tokens.emplace_back(TokenType::Tilde, source[pos++]);
                break;
            case '+':
                tokens.emplace_back(TokenType::Plus, source[pos++]);
                break;
            case '-':
                tokens.emplace_back(TokenType::Minus, source[pos++]);
                break;
            case '*':
                if (source[pos + 1] == '*') {
                    tokens.emplace_back(TokenType::DoubleStar, source.substr(pos, pos + 2));
                    pos += 2;
                } else {
                    tokens.emplace_back(TokenType::Star, source[pos++]);
                }
                break;
            case '/':
                if (source[pos + 1] == '/') {
                    tokens.emplace_back(TokenType::DoubleSlash, source.substr(pos, pos + 2));
                    pos += 2;
                } else {
                    tokens.emplace_back(TokenType::Slash, source[pos++]);
                }
                break;
            case '%':
                tokens.emplace_back(TokenType::Percent, source[pos++]);
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
                    while (std::isalpha(source[pos])) {
                        pos++;
                    };

                    auto len = pos - start;
                    auto literal = source.substr(start, len);
                    tokens.emplace_back(
                            literal == "true" || literal == "false" ? TokenType::BoolLiteral : TokenType::Identifier,
                            literal);
                } else if (std::isdigit(source[pos])) {
                    auto start = pos;
                    while (std::isdigit(source[pos]) || source[pos] == '.') {
                        pos++;
                    }

                    auto len = pos - start;
                    auto number_literal = source.substr(start, len);
                    tokens.emplace_back(TokenType::NumberLiteral, number_literal);
                }
                break;
        }
    }
    return tokens;
}