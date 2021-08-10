//
// Created by ChAoS-UnItY on 8/10/2021.
//

#include <Parser.h>
#include <BinaryExpression.h>
#include <NumberExpression.h>
#include <memory>

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

std::shared_ptr<syntax::ExpressionSyntax> syntax::Parser::parseExpression() {
    auto left = parsePrimaryExpression();

    while (Parser::current().type == TokenType::Plus) {
        const auto &operator_token = next();
        const auto &right = parseExpression();
        left = std::make_shared<syntax::BinaryExpression>(BinaryExpression(left, operator_token, right));
    }

    return left;
}

std::shared_ptr<syntax::ExpressionSyntax> syntax::Parser::parsePrimaryExpression() {
    auto number_token = match(TokenType::Number);

    return std::make_shared<syntax::NumberExpression>(NumberExpression(number_token));
}
