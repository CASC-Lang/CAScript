//
// Created by ChAoS-UnItY on 8/10/2021.
//

#ifndef COLLAGE_CPP_NUMBEREXPRESSIONSYNTAX_H
#define COLLAGE_CPP_NUMBEREXPRESSIONSYNTAX_H

#include "Token.h"
#include "ExpressionSyntax.h"

#include <utility>

namespace collage::syntax {
    class NumberExpressionSyntax: public ExpressionSyntax {
    public:
        Token number_token;

        explicit NumberExpressionSyntax(Token number_token): number_token(std::move(number_token)) {}

        SyntaxType type() override {
            return SyntaxType::Number;
        }
    };
}

#endif //COLLAGE_CPP_NUMBEREXPRESSIONSYNTAX_H
