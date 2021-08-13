//
// Created by ChAoS-UnItY on 8/12/2021.
//

#ifndef COLLAGE_CPP_BINDER_H
#define COLLAGE_CPP_BINDER_H

#include <memory>
#include <syntax/BinaryExpression.h>
#include <syntax/UnaryExpression.h>
#include <syntax/ExpressionSyntax.h>
#include <syntax/LiteralExpression.h>
#include <syntax/TernaryExpression.h>
#include "BoundExpression.h"

namespace cascript::binding {
    class Binder {
    public:
        std::unique_ptr<BoundExpression> bindExpression(std::unique_ptr<syntax::ExpressionSyntax> expression);

        std::unique_ptr<BoundExpression> bindLiteralExpression(syntax::LiteralExpression& expression);

        std::unique_ptr<BoundExpression> bindUnaryExpression(syntax::UnaryExpression& expression);

        std::unique_ptr<BoundExpression> bindBinaryExpression(syntax::BinaryExpression& expression);

        std::unique_ptr<BoundExpression> bindTernaryExpression(syntax::TernaryExpression& expression);
    };
}

#endif //COLLAGE_CPP_BINDER_H
