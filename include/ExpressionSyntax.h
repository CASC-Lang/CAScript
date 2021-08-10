//
// Created by ChAoS-UnItY on 8/10/2021.
//

#ifndef COLLAGE_CPP_EXPRESSIONSYNTAX_H
#define COLLAGE_CPP_EXPRESSIONSYNTAX_H

#include "SyntaxNode.h"

namespace collage::syntax {
    class ExpressionSyntax: public SyntaxNode {
    public:
        ExpressionSyntax() = default;

        SyntaxType type() const {
            return SyntaxType::Expr;
        }
    };

    inline std::ostream &operator<<(std::ostream &os, const ExpressionSyntax &expression) {
        os << "<Node>";
        return os;
    }
}

#endif //COLLAGE_CPP_EXPRESSIONSYNTAX_H
