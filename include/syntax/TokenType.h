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
        OpenParenthesis,
        CloseParenthesis,
        Plus,
        Minus,
        Star,
        Slash,
        Percent,
    };

    constexpr unsigned unary_precedence(TokenType token) {
        switch (token) {
            case TokenType::Plus:
            case TokenType::Minus:
                return 3;
            default:
                return 0;
        }
    }

    constexpr unsigned binary_precedence(TokenType token) {
        switch (token) {
            case TokenType::Plus:
            case TokenType::Minus:
                return 1;
            case TokenType::Star:
            case TokenType::Slash:
            case TokenType::Percent:
                return 2;
            default:
                return 0;
        };
    }
}

#endif //COLLAGE_CPP_TOKENTYPE_H