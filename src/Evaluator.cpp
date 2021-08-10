//
// Created by ChAoS_UnItY on 2021/8/11.
//

#include <NumberExpression.h>
#include <BinaryExpression.h>
#include "Evaluator.h"

collage::syntax::EvaluationCallbackValue collage::syntax::Evaluator::evalExpression(ExpressionSyntax& syntax) const {
    collage::syntax::EvaluationCallbackValue result{};

    if (auto* number = dynamic_cast<NumberExpression*>(&syntax)) {
        result.i = std::stoll(number->number_token.literal);
    } else if (auto* binary = dynamic_cast<BinaryExpression*>(&syntax)) {
        result.i = evalExpression(binary->left).i + evalExpression(binary->right).i;
    }

    return result;
}
