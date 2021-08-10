//
// Created by ChAoS-UnItY on 8/10/2021.
//

#ifndef COLLAGE_CPP_NUMBEREXPRESSION_H
#define COLLAGE_CPP_NUMBEREXPRESSION_H

#include "Token.h"
#include "ExpressionSyntax.h"

#include <utility>

namespace collage::syntax {
    class NumberExpression: public ExpressionSyntax {
    public:
        Token number_token;

        explicit NumberExpression(Token number_token): ExpressionSyntax(), number_token(std::move(number_token)) {}

        SyntaxType type() const {
            return SyntaxType::Number;
        }
    };

    inline std::ostream &operator<<(std::ostream &os, const NumberExpression &expression) {
        os << "<Expr: Number/Token: " << expression.number_token << ">";
        return os;
    }
}

#endif //COLLAGE_CPP_NUMBEREXPRESSION_H
