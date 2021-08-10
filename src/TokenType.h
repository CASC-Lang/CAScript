//
// Created by User on 8/10/2021.
//

#ifndef COLLAGE_CPP_TOKENTYPE_H
#define COLLAGE_CPP_TOKENTYPE_H

namespace collage::syntax {
    enum TokenType {
        WhiteSpace,
        Number,
        Plus,
        Minus,
        Star,
        Slash
    };

    static unsigned int precedence(enum TokenType token) {
        switch (token) {
            case Plus:
            case Minus:
                return 1;
            case Star:
            case Slash:
                return 2;
            default:
                return 0;
        };
    }
}

#endif //COLLAGE_CPP_TOKENTYPE_H
