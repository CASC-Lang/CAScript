//
// Created by ChAoS-UnItY on 8/12/2021.
//

#ifndef COLLAGE_CPP_BOUNDUNARYEXPRESSION_H
#define COLLAGE_CPP_BOUNDUNARYEXPRESSION_H

#include <memory>
#include "syntax/TokenType.h"
#include "BoundExpression.h"
#include "UnaryOperatorType.h"
#include "BoundUnaryOperator.h"

namespace collage::binding {
    class BoundUnaryExpression : public BoundExpression {
    public:
        UnaryOperatorType operator_type{};
        std::unique_ptr<BoundExpression> expression;

        BoundUnaryExpression(UnaryOperatorType operator_type, std::unique_ptr<BoundExpression> expression) :
                operator_type(operator_type), expression(std::move(expression)) {};

        Type type() const final {
            return expression->type();
        }

        BoundType bound_type() const final {
            return BoundType::Unary;
        }
    };
}

#endif //COLLAGE_CPP_BOUNDUNARYEXPRESSION_H
