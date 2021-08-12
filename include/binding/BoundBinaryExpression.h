//
// Created by ChAoS-UnItY on 8/12/2021.
//

#ifndef COLLAGE_CPP_BOUNDBINARYEXPRESSION_H
#define COLLAGE_CPP_BOUNDBINARYEXPRESSION_H

#include <memory>
#include "BoundExpression.h"

namespace collage::binding {
    class BoundBinaryExpression : public BoundExpression {
    public:
        std::unique_ptr<BoundExpression> left;
        BinaryOperatorType operator_type{};
        std::unique_ptr<BoundExpression> right;

        BoundBinaryExpression(std::unique_ptr<BoundExpression> left,
                              BinaryOperatorType operator_type,
                              std::unique_ptr<BoundExpression> right) :
                left(std::move(left)), operator_type(operator_type), right(std::move(right)) {};

        BoundType bound_type() const final {
            return BoundType::Binary;
        }

        Type type() const final {
            return left->type();
        }
    };

    enum class BinaryOperatorType {
        Addition,
        Subtraction,
        Multiplication,
        Division,
        Modulus
    };
}

#endif //COLLAGE_CPP_BOUNDBINARYEXPRESSION_H
