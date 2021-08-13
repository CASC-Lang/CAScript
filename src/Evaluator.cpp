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
                result = evalUnary<double, double>(unary, std::identity{});
                break;
            case binding::UnaryOperatorType::Negation:
                result = evalUnary<double, double>(unary, std::negate<>{});
                break;
            case binding::UnaryOperatorType::LogicalNot:
                result = evalUnary<bool, bool>(unary, std::logical_not<>{});
                break;
            case binding::UnaryOperatorType::Complement:
                result = evalUnary(unary, std::bit_not<>{});
            default:
                break;
        }
    } else if (auto *binary = dynamic_cast<binding::BoundBinaryExpression *>(&syntax)) {
        switch (binary->binary_operator.operator_type) {
            case binding::BinaryOperatorType::RightShift:
                result = evalBinary(binary, [&](long long ll1, long long ll2) { return ll1 >> ll2; });
                break;
            case binding::BinaryOperatorType::UnsignedRightShift:
                result = evalBinary(binary, [&](long long ll1, long long ll2) {
                    return ((unsigned long) ll1) >> ll2;
                });
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
            case binding::BinaryOperatorType::LogicalAnd:
                result = evalBinary<bool, bool, bool>(binary, std::logical_and{});
                break;
            case binding::BinaryOperatorType::LogicalOr:
                result = evalBinary<bool, bool, bool>(binary, std::logical_or{});
                break;
            case binding::BinaryOperatorType::Greater:
                result = evalBinary<double, double, bool>(binary, std::greater<>{});
                break;
            case binding::BinaryOperatorType::GreaterEqual:
                result = evalBinary<double, double, bool>(binary, std::greater_equal<>{});
                break;
            case binding::BinaryOperatorType::Less:
                result = evalBinary<double, double, bool>(binary, std::less<>{});
                break;
            case binding::BinaryOperatorType::LessEqual:
                result = evalBinary<double, double, bool>(binary, std::less_equal<>{});
                break;
            case binding::BinaryOperatorType::ThreeWayComparison:
                result = evalBinary<double, double, double>(binary, [&](double d1, double d2) {
                    if (d1 == d2) {
                        return 0;
                    } else if (d1 > d2) {
                        return 1;
                    } else {
                        return -1;
                    }
                });
                break;
            case binding::BinaryOperatorType::Addition:
                result = evalBinary<double, double, double>(binary, std::plus<>{});
                break;
            case binding::BinaryOperatorType::Minus:
                result = evalBinary<double, double, double>(binary, std::minus<>{});
                break;
            case binding::BinaryOperatorType::Multiplication:
                result = evalBinary<double, double, double>(binary, std::multiplies<>{});
                break;
            case binding::BinaryOperatorType::Exponent:
                result = evalBinary<double, double, double>(binary, pow);
                break;
            case binding::BinaryOperatorType::Division:
                result = evalBinary<double, double, double>(binary, std::divides<>{});
                break;
            case binding::BinaryOperatorType::FloorDivision:
                result = floor(std::any_cast<double>(evalBinary<double, double, double>(binary, fmod)));
                break;
            case binding::BinaryOperatorType::Modulus:
                result = evalBinary<double, double, double>(binary, fmodf);
                break;
            case binding::BinaryOperatorType::Equal:
                if (binary->left->type() == binding::Type::Number) {
                    result = evalBinary<double, double, bool>(binary, std::equal_to<>{});
                } else if (binary->left->type() == binding::Type::Bool) {
                    result = evalBinary<bool, bool, bool>(binary, std::equal_to<>{});
                }
                break;
            case binding::BinaryOperatorType::NotEqual:
                if (binary->left->type() == binding::Type::Number) {
                    result = evalBinary<double, double, bool>(binary, std::not_equal_to<>{});
                } else if (binary->left->type() == binding::Type::Bool) {
                    result = evalBinary<bool, bool, bool>(binary, std::not_equal_to<>{});
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
