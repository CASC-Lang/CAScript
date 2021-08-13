//
// Created by ChAoS-UnItY on 8/12/2021.
//

#ifndef COLLAGE_CPP_BOUNDUNARYOPERATOR_H
#define COLLAGE_CPP_BOUNDUNARYOPERATOR_H

#include "syntax/TokenType.h"
#include "UnaryOperatorType.h"
#include "Type.h"

namespace cascript::binding {
    struct BoundUnaryOperator {
    public:
        syntax::TokenType type;
        UnaryOperatorType operator_type{};
        Type operand_type;
        Type result_type;

        BoundUnaryOperator(syntax::TokenType type, UnaryOperatorType operator_type, Type io_type) :
                type(type), operator_type(operator_type), operand_type(io_type), result_type(io_type) {};
    };

    static const BoundUnaryOperator unary_ops[] = {
            BoundUnaryOperator(syntax::TokenType::Plus, UnaryOperatorType::Identity, Type::Number),
            BoundUnaryOperator(syntax::TokenType::Minus, UnaryOperatorType::Negation, Type::Number),
            BoundUnaryOperator(syntax::TokenType::Bang, UnaryOperatorType::LogicalNot, Type::Bool),
            BoundUnaryOperator(syntax::TokenType::Tilde, UnaryOperatorType::Complement, Type::Number),
    };

    static const BoundUnaryOperator *bind(syntax::TokenType type, Type operand_type) {
        for (const auto &op : unary_ops)
            if (op.type == type && op.operand_type == operand_type)
                return &op;

        return nullptr;
    }
}

#endif //COLLAGE_CPP_BOUNDUNARYOPERATOR_H
