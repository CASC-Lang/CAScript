//
// Created by ChAoS-UnItY on 8/12/2021.
//

#ifndef COLLAGE_CPP_BOUNDBINARYEXPRESSION_H
#define COLLAGE_CPP_BOUNDBINARYEXPRESSION_H

#include <memory>
#include "BoundExpression.h"
#include "BoundBinaryOperator.h"

namespace cascript::binding {
    class BoundBinaryExpression : public BoundExpression {
    public:
        std::unique_ptr<BoundExpression> left;
        BoundBinaryOperator binary_operator;
        std::unique_ptr<BoundExpression> right;

        BoundBinaryExpression(BoundBinaryOperator binary_operator,
                              std::unique_ptr<BoundExpression> left,
                              std::unique_ptr<BoundExpression> right) :
                left(std::move(left)), binary_operator(binary_operator), right(std::move(right)) {};

        BoundType bound_type() const final {
            return BoundType::Binary;
        }

        Type type() const final {
            return binary_operator.result_type;
        }
    };
}

#endif //COLLAGE_CPP_BOUNDBINARYEXPRESSION_H
