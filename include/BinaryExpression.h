//
// Created by ChAoS-UnItY on 8/10/2021.
//

#ifndef COLLAGE_CPP_BINARYEXPRESSION_H
#define COLLAGE_CPP_BINARYEXPRESSION_H

#include "Token.h"
#include "ExpressionSyntax.h"

#include <utility>
#include <memory>

namespace collage::syntax {
    class BinaryExpression : public ExpressionSyntax {
    public:
        std::shared_ptr<ExpressionSyntax> left;
        Token operator_token;
        std::shared_ptr<ExpressionSyntax> right;

        BinaryExpression(std::shared_ptr<ExpressionSyntax> left, Token operator_token,
                         std::shared_ptr<ExpressionSyntax> right) :
                left(left), operator_token(std::move(operator_token)), right(right) {}

        SyntaxType syntax_type() const final {
            return SyntaxType::Binary;
        }
    };

    inline std::ostream &operator<<(std::ostream &os, const BinaryExpression &expression) {
        os << "<Expr: Binary/left: " << expression.left << ", operator: " << expression.operator_token << ", right: "
           << expression.right << ">";
        return os;
    }
}

#endif //COLLAGE_CPP_BINARYEXPRESSION_H
