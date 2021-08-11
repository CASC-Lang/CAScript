//
// Created by ChAoS-UnItY on 8/10/2021.
//

#ifndef COLLAGE_CPP_LITERALEXPRESSION_H
#define COLLAGE_CPP_LITERALEXPRESSION_H

#include "Token.h"
#include "ExpressionSyntax.h"
#include "LiteralType.h"

#include <utility>

namespace collage::syntax {
    class LiteralExpression : public ExpressionSyntax {
    public:
        Token literal_token;
        LiteralType type;

        explicit LiteralExpression(Token literal_token, LiteralType type) : ExpressionSyntax(),
                                                                            literal_token(std::move(literal_token)),
                                                                            type(type) {}

        SyntaxType syntax_type() const final {
            return SyntaxType::Number;
        }
    };

    inline std::ostream &operator<<(std::ostream &os, const LiteralExpression &expression) {
        os << "<Expr: NumberLiteral/Token: " << expression.literal_token << ">";
        return os;
    }
}

#endif //COLLAGE_CPP_LITERALEXPRESSION_H
