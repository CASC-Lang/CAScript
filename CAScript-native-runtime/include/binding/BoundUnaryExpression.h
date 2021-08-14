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

namespace cascript::binding {
    class BoundUnaryExpression : public BoundExpression {
    public:
        BoundUnaryOperator unary_operator;
        std::unique_ptr<BoundExpression> expression;

        BoundUnaryExpression(BoundUnaryOperator unary_operator, std::unique_ptr<BoundExpression> expression) :
                unary_operator(unary_operator), expression(std::move(expression)) {};

        Type type() const final {
            return unary_operator.result_type;
        }

        BoundType bound_type() const final {
            return BoundType::Unary;
        }
    };
}

#endif //COLLAGE_CPP_BOUNDUNARYEXPRESSION_H
