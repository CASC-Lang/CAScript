//
// Created by ChAoS_UnItY on 2021/8/11.
//

#include <sstream>
#include <syntax/LiteralExpression.h>
#include <syntax/BinaryExpression.h>
#include <cmath>
#include <syntax/ParenthesizedExpression.h>
#include "Evaluator.h"

std::any collage::syntax::Evaluator::evalExpression(ExpressionSyntax &syntax) const {
    std::any result;

    if (auto *literal = dynamic_cast<LiteralExpression *>(&syntax)) {
        switch (literal->type) {
            case LiteralType::Number:
                result = std::stod(literal->literal_token.literal);
                break;
            case LiteralType::Bool:
                bool b;
                std::istringstream(literal->literal_token.literal) >> std::boolalpha >> b;
                result = b;
                break;
        }
    } else if (auto *parenthesized = dynamic_cast<ParenthesizedExpression *>(&syntax)) {
        result = evalExpression(*parenthesized->expression);
    } else if (auto *unary = dynamic_cast<UnaryExpression *>(&syntax)) {
        switch (unary->operator_token.type) {
            case TokenType::Plus:
                result = Evaluator::evalUnary<double, double>(unary,[&](double e) { return e; });
                break;
            case TokenType::Minus:
                result = Evaluator::evalUnary<double, double>(unary, std::negate<>{});
                break;
            default:
                break;
        }
    } else if (auto *binary = dynamic_cast<BinaryExpression *>(&syntax)) {
        switch (binary->operator_token.type) {
            case TokenType::Plus:
                result = Evaluator::evalBinary<double, double, double>(
                        binary, std::plus<>{}
                );
                break;
            case TokenType::Minus:
                result = Evaluator::evalBinary<double, double, double>(binary, std::minus<>{});
                break;
            case TokenType::Star:
                result = Evaluator::evalBinary<double, double, double>(binary, std::multiplies<>{});
                break;
            case TokenType::Slash:
                result = Evaluator::evalBinary<double, double, double>(binary, std::divides<>{});
                break;
            case TokenType::Percent:
                result = Evaluator::evalBinary<double, double, double>(binary, fmodf);
                break;
            default:
                break;
        }
    }

    return result;
}

template<class E, class V>
std::any collage::syntax::Evaluator::evalUnary(UnaryExpression *unary, std::function<V(E)> func) const {
    return func(std::any_cast<E>(evalExpression(*unary->expression)));
}

template<class L, class R, class V>
std::any collage::syntax::Evaluator::evalBinary(BinaryExpression *binary, std::function<V(L, R)> func) const {
    auto evaluated_left = any_cast<L>(evalExpression(*binary->left));
    auto evaluated_right = any_cast<R>(evalExpression(*binary->right));

    return func(evaluated_left, evaluated_right);
}
