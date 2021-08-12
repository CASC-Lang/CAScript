//
// Created by ChAoS_UnItY on 2021/8/11.
//

#ifndef COLLAGE_CPP_EVALUATOR_H
#define COLLAGE_CPP_EVALUATOR_H

#include <any>
#include <functional>
#include <binding/BoundUnaryExpression.h>
#include <binding/BoundBinaryExpression.h>
#include "binding/BoundExpression.h"

namespace collage::syntax {
    class Evaluator {
    public:
        binding::BoundExpression &root;

        explicit Evaluator(binding::BoundExpression &root) : root(root) {};

        std::any eval() const {
            return evalExpression(root);
        };

        std::any evalExpression(binding::BoundExpression &syntax) const;

    private:
        template<class E, class V>
        std::any evalUnary(binding::BoundUnaryExpression *unary, std::function<V(E)> func) const;

        template<class L, class R, class V>
        std::any evalBinary(binding::BoundBinaryExpression *binary, std::function<V(L, R)> func) const;
    };
}

#endif //COLLAGE_CPP_EVALUATOR_H
