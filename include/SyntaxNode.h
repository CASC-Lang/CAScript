//
// Created by ChAoS-UnItY on 8/10/2021.
//

#ifndef COLLAGE_CPP_SYNTAXNODE_H
#define COLLAGE_CPP_SYNTAXNODE_H

#include "SyntaxType.h"

namespace collage::syntax {
    class SyntaxNode {
    public:
        SyntaxNode();

        virtual SyntaxType type();
    };
}

#endif //COLLAGE_CPP_SYNTAXNODE_H
