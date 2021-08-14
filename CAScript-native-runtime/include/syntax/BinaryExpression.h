//
// Created by ChAoS-UnItY on 8/10/2021.
//

#ifndef COLLAGE_CPP_BINARYEXPRESSION_H
#define COLLAGE_CPP_BINARYEXPRESSION_H

#include "Token.h"
#include "ExpressionSyntax.h"

#include <memory>

namespace cascript::syntax {
    class BinaryExpression : public ExpressionSyntax {
    public:
        std::unique_ptr<ExpressionSyntax> left;
        Token operator_token;
        std::unique_ptr<ExpressionSyntax> right;

        BinaryExpression(std::unique_ptr<ExpressionSyntax> left,
                         Token operator_token,
                         std::unique_ptr<ExpressionSyntax> right) :
                left(std::move(left)), operator_token(std::move(operator_token)), right(std::move(right)) {};

        SyntaxType syntax_type() const final {
            return SyntaxType::Binary;
        }

        std::vector<SyntaxNode *> children() final {
            return std::vector<SyntaxNode *>{left.get(), &operator_token, right.get()};
        }
    };

    inline std::ostream &operator<<(std::ostream &os, const BinaryExpression &expression) {
        os << "<Expr: Binary/left: " << expression.left << ", operator: " << expression.operator_token << ", right: "
           << expression.right << ">";
        return os;
    }
}

#endif //COLLAGE_CPP_BINARYEXPRESSION_H
