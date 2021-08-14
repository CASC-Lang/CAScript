//
// Created by ChAoS-UnItY on 8/11/2021.
//

#ifndef COLLAGE_CPP_PARENTHESIZEDEXPRESSION_H
#define COLLAGE_CPP_PARENTHESIZEDEXPRESSION_H

#include <memory>

#include "Token.h"
#include "ExpressionSyntax.h"

namespace cascript::syntax {
    class ParenthesizedExpression : public ExpressionSyntax {
    public:
        Token open_parenthesis;
        std::unique_ptr<syntax::ExpressionSyntax> expression;
        Token close_parenthesis;

        ParenthesizedExpression(Token open_parenthesis,
                                std::unique_ptr<syntax::ExpressionSyntax> expression,
                                Token close_parenthesis) :
                open_parenthesis(std::move(open_parenthesis)), expression(std::move(expression)),
                close_parenthesis(std::move(close_parenthesis)) {};

        SyntaxType syntax_type() const final {
            return SyntaxType::Parenthesized;
        }

        std::vector<SyntaxNode *> children() final {
            return std::vector<SyntaxNode *>{expression.get()};
        }
    };
}

#endif //COLLAGE_CPP_PARENTHESIZEDEXPRESSION_H
