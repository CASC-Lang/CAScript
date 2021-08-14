//
// Created by ChAoS-UnItY on 8/11/2021.
//

#ifndef COLLAGE_CPP_IDENTIFIEREXPRESSION_H
#define COLLAGE_CPP_IDENTIFIEREXPRESSION_H

#include "ExpressionSyntax.h"
#include "SyntaxType.h"
#include "Token.h"

namespace cascript::syntax {
    class IdentifierExpression : public ExpressionSyntax {
    public:
        Token identifier_token;

        explicit IdentifierExpression(Token identifier_token) : identifier_token(std::move(identifier_token)) {};

        SyntaxType syntax_type() const override {
            return SyntaxType::Id;
        }

        std::vector<SyntaxNode*> children() final {
            return std::vector<SyntaxNode*> { &identifier_token };
        }
    };
}

#endif //COLLAGE_CPP_IDENTIFIEREXPRESSION_H
