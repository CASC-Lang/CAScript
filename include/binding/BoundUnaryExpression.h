//
// Created by ChAoS-UnItY on 8/12/2021.
//

#ifndef COLLAGE_CPP_BOUNDUNARYEXPRESSION_H
#define COLLAGE_CPP_BOUNDUNARYEXPRESSION_H

#include <memory>
#include "BoundExpression.h"

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
    };

    enum class UnaryOperatorType {
        Identity,
        Negation
    };
}

#endif //COLLAGE_CPP_BOUNDUNARYEXPRESSION_H
