//
// Created by ChAoS_UnItY on 2021/8/11.
//

#ifndef COLLAGE_CPP_EVALUATOR_H
#define COLLAGE_CPP_EVALUATOR_H

#include <any>
#include <functional>
#include "ExpressionSyntax.h"
#include "BinaryExpression.h"
#include "UnaryExpression.h"

namespace collage::syntax {
    class Evaluator {
    public:
        ExpressionSyntax &root;

        explicit Evaluator(ExpressionSyntax &root) : root(root) {};

        std::any eval() const {
            return evalExpression(root);
        };

        std::any evalExpression(ExpressionSyntax &syntax) const;

    private:
        template<class E, class V>
        std::any evalUnary(UnaryExpression *unary, V(*func)(E)) const;

        template<class L, class R, class V>
        std::any evalBinary(BinaryExpression *binary, V(*func)(L, R)) const;
    };
}

#endif //COLLAGE_CPP_EVALUATOR_H
