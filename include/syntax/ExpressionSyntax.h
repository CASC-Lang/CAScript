//
// Created by ChAoS-UnItY on 8/10/2021.
//

#ifndef COLLAGE_CPP_EXPRESSIONSYNTAX_H
#define COLLAGE_CPP_EXPRESSIONSYNTAX_H

#include <memory>
#include "SyntaxNode.h"

namespace collage::syntax {
    class ExpressionSyntax : public SyntaxNode {
    public:
        ExpressionSyntax() = default;

        SyntaxType syntax_type() const override = 0;

        std::unique_ptr<SyntaxNode**> children() override = 0;
    };

    inline std::ostream &operator<<(std::ostream &os, const ExpressionSyntax &expression) {
        os << "<Node>";
        return os;
    }
}

#endif //COLLAGE_CPP_EXPRESSIONSYNTAX_H
