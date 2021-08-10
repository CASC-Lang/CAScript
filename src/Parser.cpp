//
// Created by ChAoS-UnItY on 8/10/2021.
//


#include <Parser.h>
#include <BinaryExpressionSyntax.h>
#include <NumberExpressionSyntax.h>

using namespace collage;

syntax::Token syntax::Parser::peek(size_t offset) {
    return tokens[offset];
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

syntax::ExpressionSyntax syntax::Parser::parse() {
    return parseExpression();
}

syntax::ExpressionSyntax syntax::Parser::parseExpression() {
    auto left = parsePrimaryExpression();

    while (Parser::current().type == TokenType::Plus) {
        auto operator_token = next();
        auto right = parseExpression();
        left = syntax::BinaryExpressionSyntax(left, operator_token, right);
    }

    return left;
}

syntax::ExpressionSyntax syntax::Parser::parsePrimaryExpression() {
    auto number_token = match(TokenType::Number);

    return NumberExpressionSyntax(number_token);
}
