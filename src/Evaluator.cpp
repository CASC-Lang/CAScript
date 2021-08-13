//
// Created by ChAoS_UnItY on 2021/8/11.
//

#include <cmath>
#include <binding/BoundLiteralExpression.h>
#include "runtime/Evaluator.h"

std::any collage::runtime::Evaluator::evalExpression(binding::BoundExpression &syntax) const {
    std::any result;

    if (auto *literal = dynamic_cast<binding::BoundLiteralExpression *>(&syntax)) {
        result = literal->value;
    } else if (auto *unary = dynamic_cast<binding::BoundUnaryExpression *>(&syntax)) {
        switch (unary->unary_operator.operator_type) {
            case binding::UnaryOperatorType::Identity:
                result = Evaluator::evalUnary<double, double>(unary, std::identity{});
                break;
            case binding::UnaryOperatorType::Negation:
                result = Evaluator::evalUnary<double, double>(unary, std::negate<>{});
                break;
            case binding::UnaryOperatorType::LogicalNot:
                result = Evaluator::evalUnary<bool, bool>(unary, std::logical_not<>{});
                break;
            case binding::UnaryOperatorType::Complement:
                result = Evaluator::evalUnary(unary, std::bit_not<>{});
            default:
                break;
        }
    } else if (auto *binary = dynamic_cast<binding::BoundBinaryExpression *>(&syntax)) {
        switch (binary->binary_operator.operator_type) {
            case binding::BinaryOperatorType::RightShift:
                result = evalBinary(binary, [&](long long ll1, long long ll2) { return ll1 >> ll2; });
                break;
            case binding::BinaryOperatorType::LeftShift:
                result = evalBinary(binary, [&](long long ll1, long long ll2) { return ll1 << ll2; });
                break;
            case binding::BinaryOperatorType::BitwiseAnd:
                result = evalBinary(binary, std::bit_and<>{});
                break;
            case binding::BinaryOperatorType::BitwiseExclusiveOr:
                result = evalBinary(binary, std::bit_xor<>{});
                break;
            case binding::BinaryOperatorType::BitwiseInclusiveOr:
                result = evalBinary(binary, std::bit_or<>{});
                break;
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
            case binding::BinaryOperatorType::Equal:
                if (binary->left->type() == binding::Type::Number) {
                    result = Evaluator::evalBinary<double, double, bool>(binary, std::equal_to<>{});
                } else if (binary->left->type() == binding::Type::Bool) {
                    result = Evaluator::evalBinary<bool, bool, bool>(binary, std::equal_to<>{});
                }
                break;
            case binding::BinaryOperatorType::NotEqual:
                if (binary->left->type() == binding::Type::Number) {
                    result = Evaluator::evalBinary<double, double, bool>(binary, std::not_equal_to<>{});
                } else if (binary->left->type() == binding::Type::Bool) {
                    result = Evaluator::evalBinary<bool, bool, bool>(binary, std::not_equal_to<>{});
                }
            default:
                break;
        }
    }

    return result;
}

template<class E, class V>
std::any
collage::runtime::Evaluator::evalUnary(binding::BoundUnaryExpression *unary, std::function<V(E)> func) const {
    return func(std::any_cast<E>(evalExpression(*unary->expression)));
}

template<class L, class R, class V>
std::any
collage::runtime::Evaluator::evalBinary(binding::BoundBinaryExpression *binary, std::function<V(L, R)> func) const {
    auto evaluated_left = any_cast<L>(evalExpression(*binary->left));
    auto evaluated_right = any_cast<R>(evalExpression(*binary->right));

    return func(evaluated_left, evaluated_right);
}
