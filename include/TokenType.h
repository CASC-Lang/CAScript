//
// Created by ChAoS-UnItY on 8/10/2021.
//

#ifndef COLLAGE_CPP_TOKENTYPE_H
#define COLLAGE_CPP_TOKENTYPE_H

namespace collage::syntax {
    enum class TokenType {
        Identifier,
        BoolLiteral,
        NumberLiteral,
        Plus,
        Minus,
        Star,
        Slash
    };

    constexpr unsigned precedence(TokenType token) {
        switch (token) {
            case TokenType::Plus:
            case TokenType::Minus:
                return 1;
            case TokenType::Star:
            case TokenType::Slash:
                return 2;
            default:
                return 0;
        };
    }
}

#endif //COLLAGE_CPP_TOKENTYPE_H
