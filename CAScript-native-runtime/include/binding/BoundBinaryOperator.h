//
// Created by ChAoS-UnItY on 8/12/2021.
//

#ifndef COLLAGE_CPP_BOUNDBINARYOPERATOR_H
#define COLLAGE_CPP_BOUNDBINARYOPERATOR_H

#include "syntax/TokenType.h"
#include "BinaryOperatorType.h"
#include "Type.h"

namespace cascript::binding {
    struct BoundBinaryOperator {
    public:
        syntax::TokenType type;
        BinaryOperatorType operator_type{};
        Type left_type;
        Type right_type;
        Type result_type;

        BoundBinaryOperator(syntax::TokenType type, BinaryOperatorType operator_type, Type io_type) :
                type(type), operator_type(operator_type), left_type(io_type),
                right_type(io_type), result_type(io_type) {};

        BoundBinaryOperator(syntax::TokenType type, BinaryOperatorType operator_type, Type io_type, Type result_type) :
                type(type), operator_type(operator_type), left_type(io_type),
                right_type(io_type), result_type(result_type) {};
    };

    static const BoundBinaryOperator binary_ops[] = {
            BoundBinaryOperator(syntax::TokenType::Plus, BinaryOperatorType::Addition, Type::Number),
            BoundBinaryOperator(syntax::TokenType::Minus, BinaryOperatorType::Minus, Type::Number),
            BoundBinaryOperator(syntax::TokenType::Star, BinaryOperatorType::Multiplication, Type::Number),
            BoundBinaryOperator(syntax::TokenType::DoubleStar, BinaryOperatorType::Exponent, Type::Number),
            BoundBinaryOperator(syntax::TokenType::Slash, BinaryOperatorType::Division, Type::Number),
            BoundBinaryOperator(syntax::TokenType::DoubleSlash, BinaryOperatorType::FloorDivision, Type::Number),
            BoundBinaryOperator(syntax::TokenType::Percent, BinaryOperatorType::Modulus, Type::Number),
            BoundBinaryOperator(syntax::TokenType::DoubleEqual, BinaryOperatorType::Equal, Type::Number, Type::Bool),
            BoundBinaryOperator(syntax::TokenType::DoubleEqual, BinaryOperatorType::Equal, Type::Bool),
            BoundBinaryOperator(syntax::TokenType::BangEqual, BinaryOperatorType::NotEqual, Type::Number, Type::Bool),
            BoundBinaryOperator(syntax::TokenType::BangEqual, BinaryOperatorType::NotEqual, Type::Bool),
            BoundBinaryOperator(syntax::TokenType::DoubleGreaterThan, BinaryOperatorType::RightShift, Type::Number),
            BoundBinaryOperator(syntax::TokenType::TripleGreaterThan, BinaryOperatorType::UnsignedRightShift, Type::Number),
            BoundBinaryOperator(syntax::TokenType::DoubleLessThan, BinaryOperatorType::LeftShift, Type::Number),
            BoundBinaryOperator(syntax::TokenType::Ampersand, BinaryOperatorType::BitwiseAnd, Type::Number),
            BoundBinaryOperator(syntax::TokenType::Caret, BinaryOperatorType::BitwiseExclusiveOr, Type::Number),
            BoundBinaryOperator(syntax::TokenType::Pipe, BinaryOperatorType::BitwiseInclusiveOr, Type::Number),
            BoundBinaryOperator(syntax::TokenType::DoubleAmpersand, BinaryOperatorType::LogicalAnd, Type::Bool),
            BoundBinaryOperator(syntax::TokenType::DoublePipe, BinaryOperatorType::LogicalOr, Type::Bool),
            BoundBinaryOperator(syntax::TokenType::GreaterThan, BinaryOperatorType::Greater, Type::Number, Type::Bool),
            BoundBinaryOperator(syntax::TokenType::GreaterEqualThan, BinaryOperatorType::GreaterEqual, Type::Number, Type::Bool),
            BoundBinaryOperator(syntax::TokenType::LessThan, BinaryOperatorType::Less, Type::Number, Type::Bool),
            BoundBinaryOperator(syntax::TokenType::LessEqualThan, BinaryOperatorType::LessEqual, Type::Number, Type::Bool),
            BoundBinaryOperator(syntax::TokenType::LessEqualGreater, BinaryOperatorType::ThreeWayComparison, Type::Number),
    };

    static const BoundBinaryOperator *bind(syntax::TokenType type, Type left_type, Type right_type) {
        for (const auto &op : binary_ops)
            if (op.type == type && op.left_type == left_type && op.right_type == right_type)
                return &op;

        return nullptr;
    }
}

#endif //COLLAGE_CPP_BOUNDBINARYOPERATOR_H
