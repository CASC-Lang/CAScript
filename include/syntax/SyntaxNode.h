//
// Created by ChAoS-UnItY on 8/10/2021.
//

#ifndef COLLAGE_CPP_SYNTAXNODE_H
#define COLLAGE_CPP_SYNTAXNODE_H

#include <vector>
#include "SyntaxType.h"

namespace cascript::syntax {
    class SyntaxNode {
    public:
        SyntaxNode() = default;

        virtual SyntaxType syntax_type() const = 0;

        virtual std::vector<SyntaxNode*> children() = 0;
    };
}

#endif //COLLAGE_CPP_SYNTAXNODE_H
