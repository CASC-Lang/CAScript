//
// Created by ChAoS-UnItY on 8/12/2021.
//

#ifndef COLLAGE_CPP_BOUNDEXPRESSION_H
#define COLLAGE_CPP_BOUNDEXPRESSION_H

#include "Type.h"
#include "BoundNode.h"

namespace cascript::binding {
    class BoundExpression: public BoundNode {
    public:
        BoundExpression() = default;

        virtual Type type() const = 0;

        BoundType bound_type() const override = 0;
    };
}

#endif //COLLAGE_CPP_BOUNDEXPRESSION_H
