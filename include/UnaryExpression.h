//
// Created by ChAoS-UnItY on 8/11/2021.
//

#ifndef COLLAGE_CPP_UNARYEXPRESSION_H
#define COLLAGE_CPP_UNARYEXPRESSION_H

#include <memory>
#include <utility>

#include "Token.h"
#include "ExpressionSyntax.h"

namespace collage::syntax {
    class UnaryExpression : public ExpressionSyntax {
    public:
        Token operator_token;
        std::shared_ptr<ExpressionSyntax> expression;

        UnaryExpression(Token operator_token, std::shared_ptr<ExpressionSyntax> expression) : operator_token(std::move(operator_token)),
                expression(std::move(expression)) {};

        SyntaxType syntax_type() const final {
            return SyntaxType::Unary;
        }
    };
}


#endif //COLLAGE_CPP_UNARYEXPRESSION_H
