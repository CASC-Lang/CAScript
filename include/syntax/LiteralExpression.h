//
// Created by ChAoS-UnItY on 8/10/2021.
//

#ifndef COLLAGE_CPP_LITERALEXPRESSION_H
#define COLLAGE_CPP_LITERALEXPRESSION_H

#include "Token.h"
#include "ExpressionSyntax.h"
#include "binding/Type.h"

#include <utility>

namespace cascript::syntax {
    class LiteralExpression : public ExpressionSyntax {
    public:
        Token literal_token;
        binding::Type type;

        explicit LiteralExpression(Token literal_token, binding::Type type) : ExpressionSyntax(),
                                                                            literal_token(std::move(literal_token)),
                                                                            type(type) {}

        SyntaxType syntax_type() const final {
            return SyntaxType::Number;
        }

        std::vector<SyntaxNode *> children() final {
            return std::vector<SyntaxNode *>{&literal_token};
        }
    };
}

#endif //COLLAGE_CPP_LITERALEXPRESSION_H
