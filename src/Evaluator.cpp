//
// Created by ChAoS_UnItY on 2021/8/11.
//

#include <cmath>
#include <binding/BoundLiteralExpression.h>
#include "Evaluator.h"

std::any collage::syntax::Evaluator::evalExpression(binding::BoundExpression &syntax) const {
    std::any result;

    if (auto *literal = dynamic_cast<binding::BoundLiteralExpression *>(&syntax)) {
        result = literal->value;
    } else if (auto *unary = dynamic_cast<binding::BoundUnaryExpression *>(&syntax)) {
        switch (unary->operator_type) {
            case binding::UnaryOperatorType::Identity:
                result = Evaluator::evalUnary<double, double>(unary, [&](double e) { return e; });
                break;
            case binding::UnaryOperatorType::Negation:
                result = Evaluator::evalUnary<double, double>(unary, std::negate<>{});
                break;
            default:
                break;
        }
    } else if (auto *binary = dynamic_cast<binding::BoundBinaryExpression *>(&syntax)) {
        switch (binary->operator_type) {
            case binding::BinaryOperatorType::Addition:
                result = Evaluator::evalBinary<double, double, double>(binary, std::plus<>{});
                break;
            case binding::BinaryOperatorType::Minus:
                result = Evaluator::evalBinary<double, double, double>(binary, std::minus<>{});
                break;
            case binding::BinaryOperatorType::Multiplication:
                result = Evaluator::evalBinary<double, double, double>(binary, std::multiplies<>{});
                break;
            case binding::BinaryOperatorType::Division:
                result = Evaluator::evalBinary<double, double, double>(binary, std::divides<>{});
                break;
            case binding::BinaryOperatorType::Modulus:
                result = Evaluator::evalBinary<double, double, double>(binary, fmodf);
                break;
            default:
                break;
        }
    }

    return result;
}

template<class E, class V>
std::any collage::syntax::Evaluator::evalUnary(binding::BoundUnaryExpression *unary, std::function<V(E)> func) const {
    return func(std::any_cast<E>(evalExpression(*unary->expression)));
}

template<class L, class R, class V>
std::any
collage::syntax::Evaluator::evalBinary(binding::BoundBinaryExpression *binary, std::function<V(L, R)> func) const {
    auto evaluated_left = any_cast<L>(evalExpression(*binary->left));
    auto evaluated_right = any_cast<R>(evalExpression(*binary->right));

    return func(evaluated_left, evaluated_right);
}
