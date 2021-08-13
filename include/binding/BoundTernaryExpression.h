//
// Created by ChAoS-UnItY on 8/13/2021.
//

#ifndef COLLAGE_CPP_BOUNDTERNARYEXPRESSION_H
#define COLLAGE_CPP_BOUNDTERNARYEXPRESSION_H

#include <memory>

#include "BoundExpression.h"
#include "BoundTernaryOperator.h"

namespace cascript::binding {
    class BoundTernaryExpression : public BoundExpression {
    public:
        BoundTernaryOperator operators;
        std::unique_ptr<BoundExpression> left;
        std::unique_ptr<BoundExpression> center;
        std::unique_ptr<BoundExpression> right;

        BoundTernaryExpression(BoundTernaryOperator operators,
                               std::unique_ptr<BoundExpression> left,
                               std::unique_ptr<BoundExpression> center,
                               std::unique_ptr<BoundExpression> right) :
                operators(operators), left(std::move(left)), center(std::move(center)), right(std::move(right)) {};

        BoundType bound_type() const final {
            return BoundType::Ternary;
        }

        Type type() const final {
            if (operators.operator_type == TernaryOperatorType::Conditional) {
                return center->type();
            } else {
                return Type::Unidentified;
            }
        }
    };
}

#endif //COLLAGE_CPP_BOUNDTERNARYEXPRESSION_H
