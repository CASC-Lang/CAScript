//
// Created by ChAoS-UnItY on 8/13/2021.
//

#ifndef COLLAGE_CPP_BOUNDTERNARYOPERATOR_H
#define COLLAGE_CPP_BOUNDTERNARYOPERATOR_H

#include <array>

#include "syntax/TokenType.h"
#include "TernaryOperatorType.h"

namespace cascript::binding {
    struct BoundTernaryOperator {
    public:
        syntax::TokenType types[2];
        TernaryOperatorType operator_type{};
        Type left_type;
        Type center_type;
        Type right_type;

        BoundTernaryOperator(std::array<syntax::TokenType, 2> types, TernaryOperatorType operator_type, Type left_type,
                             Type center_type, Type right_type) :
                operator_type(operator_type), left_type(left_type), center_type(center_type),
                right_type(right_type) {
            std::copy(std::begin(types), std::end(types), std::begin(this->types));
        };
    };

    static const BoundTernaryOperator ternary_ops[] = {
            BoundTernaryOperator({syntax::TokenType::QuestionMark, syntax::TokenType::Colon},
                                 TernaryOperatorType::Conditional,
                                 Type::Bool,
                                 Type::Unidentified,
                                 Type::Unidentified
            ),
    };

    static const BoundTernaryOperator *
    bind(syntax::TokenType types[2], Type left_type, Type center_type, Type right_type) {
        for (const auto &op : ternary_ops)
            if (op.types[0] == types[0] && op.types[1] == types[1] && is_or_unspecified(op.left_type, left_type) &&
                is_or_unspecified(op.center_type, center_type) && is_or_unspecified(op.right_type, right_type))
                return &op;

        return nullptr;
    }
}

#endif //COLLAGE_CPP_BOUNDTERNARYOPERATOR_H
