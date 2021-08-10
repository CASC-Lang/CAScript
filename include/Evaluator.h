//
// Created by ChAoS_UnItY on 2021/8/11.
//

#ifndef COLLAGE_CPP_EVALUATOR_H
#define COLLAGE_CPP_EVALUATOR_H

#include "ExpressionSyntax.h"

namespace collage::syntax {
    union EvaluationCallbackValue {
        bool b;
        long long i;
    };

    class Evaluator {
    public:
        ExpressionSyntax &root;

        explicit Evaluator(ExpressionSyntax &root) : root(root) {};

        EvaluationCallbackValue eval() const {
            return evalExpression(root);
        };

        EvaluationCallbackValue evalExpression(ExpressionSyntax& syntax) const;
    };
}

#endif //COLLAGE_CPP_EVALUATOR_H
