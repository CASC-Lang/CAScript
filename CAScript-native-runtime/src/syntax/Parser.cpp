//
// Created by ChAoS-UnItY on 8/10/2021.
//

#include <syntax/Parser.h>
#include <syntax/BinaryExpression.h>
#include <syntax/LiteralExpression.h>
#include <memory>
#include <syntax/IdentifierExpression.h>
#include <syntax/UnaryExpression.h>
#include <syntax/TernaryExpression.h>
#include <syntax/ParenthesizedExpression.h>

using namespace cascript;

syntax::Token syntax::Parser::peek(size_t offset) {
    auto index = pos + offset;
    if (index >= tokens.size()) {
        return tokens[tokens.size() - 1];
    }

    return tokens[pos + offset];
}

syntax::Token syntax::Parser::match(syntax::TokenType type) {
    if (current().type == type) {
        return next();
    } else {
        return {type, '\0'};
    }
}

syntax::Token syntax::Parser::next() {
    auto current = Parser::current();
    pos++;
    return current;
}

std::unique_ptr<syntax::ExpressionSyntax> syntax::Parser::parse() {
    return parseExpression();
}

std::unique_ptr<syntax::ExpressionSyntax> syntax::Parser::parseExpression(unsigned parent_precedence) {
    std::unique_ptr<syntax::ExpressionSyntax> left;
    auto precedence = unary_precedence(Parser::current().type);
    if (precedence != 0 || precedence > parent_precedence) {
        const auto &operator_token = next();
        auto expression = parseExpression(precedence);
        left = std::make_unique<syntax::UnaryExpression>(UnaryExpression(operator_token, std::move(expression)));
    } else {
        left = parsePrimaryExpression();
    }

    for (;;) {
        precedence = binary_precedence(Parser::current().type);

        if (precedence == 0 || precedence <= parent_precedence) break;

        if (precedence == 1) {
            const auto &question_mark_token = match(TokenType::QuestionMark);
            auto center = parseExpression();
            const auto &colon_token = match(TokenType::Colon);
            auto right = parseExpression();

            left = std::make_unique<syntax::TernaryExpression>(
                    TernaryExpression(std::move(left),
                                      question_mark_token,
                                      std::move(center),
                                      colon_token,
                                      std::move(right))
            );
            continue;
        }

        const auto &operator_token = next();
        auto right = parseExpression(precedence);
        left = std::make_unique<syntax::BinaryExpression>(
                BinaryExpression(std::move(left), operator_token, std::move(right))
        );
    }

    return left;
}

std::unique_ptr<syntax::ExpressionSyntax> syntax::Parser::parsePrimaryExpression() {
    switch (Parser::current().type) {
        case TokenType::OpenParenthesis: {
            const auto &open_parenthesis_token = match(TokenType::OpenParenthesis);
            auto expression = parseExpression();
            const auto &close_parenthesis_token = match(TokenType::CloseParenthesis);
            return std::make_unique<syntax::ParenthesizedExpression>(
                    ParenthesizedExpression(open_parenthesis_token, std::move(expression), close_parenthesis_token));
        }
        case TokenType::NumberLiteral: {
            const auto &number_token = match(TokenType::NumberLiteral);
            return std::make_unique<syntax::LiteralExpression>(LiteralExpression(number_token, binding::Type::Number));
        }
        case TokenType::BoolLiteral: {
            const auto &bool_token = match(TokenType::BoolLiteral);
            return std::make_unique<syntax::LiteralExpression>(LiteralExpression(bool_token, binding::Type::Bool));
        }
        default: {
            const auto &identifier_token = match(TokenType::Identifier);
            return std::make_unique<syntax::IdentifierExpression>(IdentifierExpression(identifier_token));
        }
    }
}
