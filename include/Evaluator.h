//
// Created by ChAoS_UnItY on 2021/8/11.
//

#ifndef COLLAGE_CPP_EVALUATOR_H
#define COLLAGE_CPP_EVALUATOR_H

#include <any>
#include "ExpressionSyntax.h"

namespace collage::syntax {
    class Evaluator {
    public:
        ExpressionSyntax &root;

        explicit Evaluator(ExpressionSyntax &root) : root(root) {};

        std::any eval() const {
            return evalExpression(root);
        };

        std::any evalExpression(ExpressionSyntax &syntax) const;
    };
}

#endif //COLLAGE_CPP_EVALUATOR_H
