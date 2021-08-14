//
// Created by ChAoS-UnItY on 8/10/2021.
//

#ifndef COLLAGE_CPP_SYNTAXTYPE_H
#define COLLAGE_CPP_SYNTAXTYPE_H

namespace cascript::syntax {
    enum class SyntaxType {
        Token,
        Id,
        Number,
        Parenthesized,
        Unary,
        Binary,
        Ternary
    };
}

#endif //COLLAGE_CPP_SYNTAXTYPE_H
