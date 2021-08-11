//
// Created by ChAoS_UnItY on 2021/8/11.
//

#include <sstream>
#include <LiteralExpression.h>
#include <BinaryExpression.h>
#include "Evaluator.h"

std::any collage::syntax::Evaluator::evalExpression(ExpressionSyntax &syntax) const {
    std::any result;

    if (auto *literal = dynamic_cast<LiteralExpression *>(&syntax)) {
        switch (literal->type) {
            case LiteralType::Long:
                result = std::stoll(literal->literal_token.literal);
                break;
            case LiteralType::Double:
                break;
            case LiteralType::Bool:
                bool b;
                std::istringstream(literal->literal_token.literal) >> std::boolalpha >> b;
                result = b;
                break;
        }
    } else if (auto *binary = dynamic_cast<BinaryExpression *>(&syntax)) {
        auto left = any_cast<long long>(evalExpression(*binary->left));
        auto right = any_cast<long long>(evalExpression(*binary->right));

        switch (binary->operator_token.type) {
            case TokenType::Plus:
                result = left + right;
                break;
            case TokenType::Minus:
                result = left - right;
                break;
            case TokenType::Star:
                result = left * right;
                break;
            case TokenType::Slash:
                result = left / right;
                break;
            default:
                break;
        }
    }

    return result;
}
