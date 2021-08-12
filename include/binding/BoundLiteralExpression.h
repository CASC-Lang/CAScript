//
// Created by ChAoS-UnItY on 8/12/2021.
//

#ifndef COLLAGE_CPP_BOUNDLITERALEXPRESSION_H
#define COLLAGE_CPP_BOUNDLITERALEXPRESSION_H

#include <any>
#include "BoundExpression.h"

namespace collage::binding {
    class BoundLiteralExpression: public BoundExpression {
    public:
        std::any value;

        explicit BoundLiteralExpression(std::any value): value(std::move(value)) {};

        BoundType bound_type() const final {
            return BoundType::Literal;
        }

        Type type() const final {
            if (auto number = dynamic_cast<double>(value)) {
                return Type::Number;
            } else if (auto boolean = dynamic_cast<bool>(value)) {
                return Type::Bool;
            } else {
                return Type::Unidentified;
            }
        }
    };
}

#endif //COLLAGE_CPP_BOUNDLITERALEXPRESSION_H
