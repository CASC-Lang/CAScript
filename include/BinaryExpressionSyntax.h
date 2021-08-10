//
// Created by ChAoS-UnItY on 8/10/2021.
//

#ifndef COLLAGE_CPP_BINARYEXPRESSIONSYNTAX_H
#define COLLAGE_CPP_BINARYEXPRESSIONSYNTAX_H

#include "Token.h"
#include "ExpressionSyntax.h"

#include <utility>

namespace collage::syntax {
    class BinaryExpressionSyntax : public ExpressionSyntax {
    public:
        ExpressionSyntax left;
        Token operator_token;
        ExpressionSyntax right;

        BinaryExpressionSyntax(ExpressionSyntax left, Token operator_token, ExpressionSyntax right) :
                left(std::move(left)), operator_token(std::move(operator_token)), right(std::move(right)) {}

        SyntaxType type() override {
            return SyntaxType::Binary;
        }
    };
}

#endif //COLLAGE_CPP_BINARYEXPRESSIONSYNTAX_H
