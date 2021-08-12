//
// Created by ChAoS-UnItY on 8/12/2021.
//

#include <sstream>
#include <binding/BoundBinaryOperator.h>
#include <binding/BoundBinaryExpression.h>

#include "binding/BoundLiteralExpression.h"
#include "binding/BoundExpression.h"
#include "binding/BoundUnaryExpression.h"
#include "binding/BoundUnaryOperator.h"
#include "binding/Binder.h"

std::unique_ptr<collage::binding::BoundExpression>
collage::binding::Binder::bindExpression(std::unique_ptr<syntax::ExpressionSyntax> expression) {
    if (auto literal = dynamic_cast<syntax::LiteralExpression*>(expression.get())) {
        return bindLiteralExpression(*literal);
    } else if (auto unary = dynamic_cast<syntax::UnaryExpression*>(expression.get())) {
        return bindUnaryExpression(*unary);
    } else if (auto binary = dynamic_cast<syntax::BinaryExpression*>(expression.get())) {
        return bindBinaryExpression(*binary);
    } else {
        return std::make_unique<binding::BoundLiteralExpression>(nullptr, Type::Unidentified);
    }
}

std::unique_ptr<collage::binding::BoundExpression>
collage::binding::Binder::bindLiteralExpression(syntax::LiteralExpression &expression) {
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



std::unique_ptr<collage::binding::BoundExpression>
collage::binding::Binder::bindUnaryExpression(collage::syntax::UnaryExpression &expression) {
    auto operand = bindExpression(std::move(expression.expression));
    auto operator_type = bind(expression.operator_token.type, operand->type());

    if (operator_type == nullptr) {

    }

    return std::make_unique<BoundUnaryExpression>(operator_type->operator_type, std::move(operand));
}

std::unique_ptr<collage::binding::BoundExpression>
collage::binding::Binder::bindBinaryExpression(collage::syntax::BinaryExpression &expression) {
    auto left = bindExpression(std::move(expression.left));
    auto right = bindExpression(std::move(expression.right));
    auto operator_type = bind(expression.operator_token.type, left->type(), right->type());

    return std::make_unique<BoundBinaryExpression>(operator_type->operator_type, std::move(left), std::move(right));
}
