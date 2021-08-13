//
// Created by ChAoS-UnItY on 8/12/2021.
//

#include <sstream>
#include <binding/BoundBinaryOperator.h>
#include <binding/BoundBinaryExpression.h>
#include <binding/BoundLiteralExpression.h>
#include <binding/BoundUnaryExpression.h>
#include <binding/BoundTernaryExpression.h>
#include <syntax/ParenthesizedExpression.h>

#include "binding/Binder.h"


std::unique_ptr<cascript::binding::BoundExpression>
cascript::binding::Binder::bindExpression(std::unique_ptr<syntax::ExpressionSyntax> expression) {
    if (auto literal = dynamic_cast<syntax::LiteralExpression *>(expression.get())) {
        return bindLiteralExpression(*literal);
    } else if (auto unary = dynamic_cast<syntax::UnaryExpression *>(expression.get())) {
        return bindUnaryExpression(*unary);
    } else if (auto binary = dynamic_cast<syntax::BinaryExpression *>(expression.get())) {
        return bindBinaryExpression(*binary);
    } else if (auto ternary = dynamic_cast<syntax::TernaryExpression *>(expression.get())) {
        return bindTernaryExpression(*ternary);
    } else if (auto parenthesized = dynamic_cast<syntax::ParenthesizedExpression *>(expression.get())) {
        return bindExpression(std::move((*parenthesized).expression));
    } else {
        return std::make_unique<binding::BoundLiteralExpression>(nullptr, Type::Unidentified);
    }
}

std::unique_ptr<cascript::binding::BoundExpression>
cascript::binding::Binder::bindLiteralExpression(syntax::LiteralExpression &expression) {
    std::any value;
    switch (expression.type) {
        case Type::Unidentified:
            value = nullptr;
            break;
        case Type::Number:
            value = std::stod(expression.literal_token.literal);
            break;
        case Type::Bool:
            bool temp_value;
            std::istringstream(expression.literal_token.literal) >> std::boolalpha >> temp_value;
            value = temp_value;
            break;
    }

    return std::make_unique<binding::BoundLiteralExpression>(value, expression.type);
}


std::unique_ptr<cascript::binding::BoundExpression>
cascript::binding::Binder::bindUnaryExpression(cascript::syntax::UnaryExpression &expression) {
    auto operand = bindExpression(std::move(expression.expression));
    auto operator_type = bind(expression.operator_token.type, operand->type());

    if (operator_type == nullptr) {

    }

    return std::make_unique<BoundUnaryExpression>(*operator_type, std::move(operand));
}

std::unique_ptr<cascript::binding::BoundExpression>
cascript::binding::Binder::bindBinaryExpression(cascript::syntax::BinaryExpression &expression) {
    auto left = bindExpression(std::move(expression.left));
    auto right = bindExpression(std::move(expression.right));
    auto operator_type = bind(expression.operator_token.type, left->type(), right->type());

    return std::make_unique<BoundBinaryExpression>(*operator_type, std::move(left), std::move(right));
}

std::unique_ptr<cascript::binding::BoundExpression>
cascript::binding::Binder::bindTernaryExpression(syntax::TernaryExpression &expression) {
    auto left = bindExpression(std::move(expression.left));
    auto center = bindExpression(std::move(expression.center));
    auto right = bindExpression(std::move(expression.right));
    auto token_types = new syntax::TokenType[2]{expression.left_operator_token.type,
                                                expression.right_operator_token.type};
    auto operator_type = bind(token_types, left->type(),
                              center->type(), right->type());

    delete[] token_types;

    return std::make_unique<BoundTernaryExpression>(*operator_type, std::move(left), std::move(center), std::move(right));
}
