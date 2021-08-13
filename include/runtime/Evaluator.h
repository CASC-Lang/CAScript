//
// Created by ChAoS_UnItY on 2021/8/11.
//

#ifndef COLLAGE_CPP_EVALUATOR_H
#define COLLAGE_CPP_EVALUATOR_H

#include <any>
#include <functional>
#include <binding/BoundUnaryExpression.h>
#include <binding/BoundBinaryExpression.h>
#include <binding/BoundExpression.h>

namespace cascript::runtime {
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

        std::any evalUnary(binding::BoundUnaryExpression *unary,
                                                 std::function<long long(long long)> func) const {
            return (double) func(static_cast<long long>(std::any_cast<double>(evalExpression(*unary->expression))));
        };

        template<class L, class R, class V>
        std::any evalBinary(binding::BoundBinaryExpression *binary, std::function<V(L, R)> func) const;

        std::any
        evalBinary(binding::BoundBinaryExpression *binary,
                                         std::function<long long(long long, long long)> func) const {
            auto evaluated_left = static_cast<long long>(any_cast<double>(evalExpression(*binary->left)));
            auto evaluated_right = static_cast<long long>(any_cast<double>(evalExpression(*binary->right)));

            return (double) func(evaluated_left, evaluated_right);
        };
    };
}

#endif //COLLAGE_CPP_EVALUATOR_H
