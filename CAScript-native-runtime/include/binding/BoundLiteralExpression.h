//
// Created by ChAoS-UnItY on 8/12/2021.
//

#ifndef COLLAGE_CPP_BOUNDLITERALEXPRESSION_H
#define COLLAGE_CPP_BOUNDLITERALEXPRESSION_H

#include <any>
#include "BoundExpression.h"

namespace cascript::binding {
    class BoundLiteralExpression : public BoundExpression {
    public:
        std::any value;
        Type value_type;

        explicit BoundLiteralExpression(std::any value, Type value_type) : value(std::move(value)),
                                                                           value_type(value_type) {};

        BoundType bound_type() const final {
            return BoundType::Literal;
        }

        Type type() const final {
            if (auto *number = std::any_cast<double>(&value)) {
                return Type::Number;
            } else if (auto *boolean = std::any_cast<bool>(&value)) {
                return Type::Bool;
            } else {
                return Type::Unidentified;
            }
        }
    };
}

#endif //COLLAGE_CPP_BOUNDLITERALEXPRESSION_H
