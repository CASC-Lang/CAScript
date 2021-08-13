//
// Created by ChAoS-UnItY on 8/13/2021.
//

#ifndef COLLAGE_CPP_TERNARYEXPRESSION_H
#define COLLAGE_CPP_TERNARYEXPRESSION_H

#include <memory>
#include "Token.h"
#include "ExpressionSyntax.h"

namespace cascript::syntax {
    class TernaryExpression : public ExpressionSyntax {
    public:
        std::unique_ptr<ExpressionSyntax> left;
        Token left_operator_token;
        std::unique_ptr<ExpressionSyntax> center;
        Token right_operator_token;
        std::unique_ptr<ExpressionSyntax> right;

        TernaryExpression(std::unique_ptr<ExpressionSyntax> left,
                          Token left_operator_token,
                          std::unique_ptr<ExpressionSyntax> center,
                          Token right_operator_token,
                          std::unique_ptr<ExpressionSyntax> right) :
                left(std::move(left)), left_operator_token(std::move(left_operator_token)), center(std::move(center)),
                right_operator_token(std::move(right_operator_token)), right(std::move(right)) {};

        SyntaxType syntax_type() const final {
            return SyntaxType::Ternary;
        }

        std::vector<SyntaxNode *> children() final {
            return std::vector<SyntaxNode *>{left.get(),
                                             &left_operator_token, center.get(),
                                             &right_operator_token,
                                             right.get()};
        }
    };
}

#endif //COLLAGE_CPP_TERNARYEXPRESSION_H
