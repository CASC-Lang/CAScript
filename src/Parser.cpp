//
// Created by ChAoS-UnItY on 8/10/2021.
//

#include <Parser.h>
#include <BinaryExpression.h>
#include <LiteralExpression.h>
#include <memory>
#include <IdentifierExpression.h>
#include <UnaryExpression.h>
#include <ParenthesizedExpression.h>

using namespace collage;

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

std::shared_ptr<syntax::ExpressionSyntax> syntax::Parser::parse() {
    return parseExpression();
}

std::shared_ptr<syntax::ExpressionSyntax> syntax::Parser::parseExpression(unsigned parent_precedence) {
    std::shared_ptr<syntax::ExpressionSyntax> left;
    auto precedence = unary_precedence(Parser::current().type);
    if (precedence != 0 || precedence > parent_precedence) {
        const auto &operator_token = next();
        const auto expression = parseExpression();
        left = std::make_shared<syntax::UnaryExpression>(UnaryExpression(operator_token, expression));
    } else {
        left = parsePrimaryExpression();
    }

    for (;;) {
        precedence = binary_precedence(Parser::current().type);

        if (precedence == 0 || precedence <= parent_precedence) break;

        const auto &operator_token = next();
        const auto &right = parseExpression(precedence);
        left = std::make_shared<syntax::BinaryExpression>(BinaryExpression(left, operator_token, right));
    }

    return left;
}

std::shared_ptr<syntax::ExpressionSyntax> syntax::Parser::parsePrimaryExpression() {
    switch (Parser::current().type) {
        case TokenType::OpenParenthesis: {
            const auto &open_parenthesis_token = match(TokenType::OpenParenthesis);
            const auto &expression = parseExpression();
            const auto &close_parenthesis_token = match(TokenType::CloseParenthesis);
            return std::make_shared<syntax::ParenthesizedExpression>(ParenthesizedExpression(open_parenthesis_token, expression, close_parenthesis_token));
        }
        case TokenType::NumberLiteral: {
            const auto &number_token = match(TokenType::NumberLiteral);
            return std::make_shared<syntax::LiteralExpression>(LiteralExpression(number_token, LiteralType::Number));
        }
        case TokenType::BoolLiteral: {
            const auto &bool_token = match(TokenType::BoolLiteral);
            return std::make_shared<syntax::LiteralExpression>(LiteralExpression(bool_token, LiteralType::Bool));
        }
        default: {
            const auto &identifier_token = match(TokenType::Identifier);
            return std::make_shared<syntax::IdentifierExpression>(IdentifierExpression(identifier_token));
        }
    }
}
