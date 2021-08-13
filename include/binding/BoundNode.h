//
// Created by ChAoS-UnItY on 8/12/2021.
//

#ifndef COLLAGE_CPP_BOUNDNODE_H
#define COLLAGE_CPP_BOUNDNODE_H

#include "BoundType.h"

namespace cascript::binding {
    class BoundNode {
    public:
        BoundNode() = default;

        virtual BoundType bound_type() const = 0;
    };
}

#endif //COLLAGE_CPP_BOUNDNODE_H
