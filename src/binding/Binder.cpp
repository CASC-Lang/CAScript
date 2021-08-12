//
// Created by ChAoS-UnItY on 8/12/2021.
//

#include "binding/Binder.h"

std::unique_ptr<collage::binding::BoundExpression>
collage::binding::Binder::bindExpression(std::unique_ptr<syntax::ExpressionSyntax> expression) {
    return std::unique_ptr<BoundExpression>();
}

std::unique_ptr<collage::binding::BoundExpression>
collage::binding::Binder::bindLiteralExpression(syntax::LiteralExpression &expression) {
    return std::unique_ptr<BoundExpression>();
}
