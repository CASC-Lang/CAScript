//
// Created by ChAoS-UnItY on 8/10/2021.
//

#include <Parser.h>
#include <BinaryExpression.h>
#include <LiteralExpression.h>
#include <memory>
#include <IdentifierExpression.h>

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
    auto left = parsePrimaryExpression();

    for (;;) {
        auto precedence = binary_precedence(Parser::current().type);

        if (precedence == 0 || precedence <= parent_precedence) break;

        const auto &operator_token = next();
        const auto &right = parseExpression(precedence);
        left = std::make_shared<syntax::BinaryExpression>(BinaryExpression(left, operator_token, right));
    }

    return left;
}

std::shared_ptr<syntax::ExpressionSyntax> syntax::Parser::parsePrimaryExpression() {
    switch (Parser::current().type) {
        case TokenType::NumberLiteral: {
            const auto number_token = match(TokenType::NumberLiteral);
            return std::make_shared<syntax::LiteralExpression>(LiteralExpression(number_token, LiteralType::Long));
        }
        case TokenType::BoolLiteral: {
            const auto bool_token = match(TokenType::BoolLiteral);
            return std::make_shared<syntax::LiteralExpression>(LiteralExpression(bool_token, LiteralType::Bool));
        }
        default: {
            const auto identifier_token = match(TokenType::Identifier);
            return std::make_shared<syntax::IdentifierExpression>(IdentifierExpression(identifier_token));
        }
    }
}
